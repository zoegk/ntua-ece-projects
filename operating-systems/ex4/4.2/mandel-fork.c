/*
 * A program to draw the Mandelbrot set on a 256-color xterm.
 */

#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/wait.h>

#include "mandel-lib.h"

#define MANDEL_MAX_ITERATION 100000

int **buffer; // 2D Mandelbrot set output

// Output at the terminal is x_chars wide by y_chars long.
int y_chars = 50;
int x_chars = 90;

// The part of the complex plane to be drawn:
// upper left corner is (xmin, ymax), lower right corner is (xmax, ymin).
double xmin = -1.8, xmax = 1.0;
double ymin = -1.0, ymax = 1.0;

// Every character in the final output is xstep x ystep units wide on the complex plane.
double xstep;
double ystep;

// Helping function to safely convert string to integer
int safe_atoi(char *s, int *val)
{
    long l;
    char *endp;

    l = strtol(s, &endp, 10);
    if (s != endp && *endp == '\0') {
        *val = l;
        return 0;
    } else
        return -1;
}

/*
 * This function computes a line of output as an array of x_char color values.
 */
void compute_mandel_line(int line, int color_val[])
{
    // x and y traverse the complex plane.
    double x, y;

    int n;
    int val;

    // Find out the y value corresponding to this line
    y = ymax - ystep * line;

    // Iterate for all points on this line
    for (x = xmin, n = 0; n < x_chars; x += xstep, n++) {
        // Compute the point's color value
        val = mandel_iterations_at_point(x, y, MANDEL_MAX_ITERATION);
        if (val > 255)
            val = 255;

        // Store the color value in the color_val[] array
        val = xterm_color(val);
        color_val[n] = val;
    }
}

/*
 * This function outputs an array of x_char color values to a 256-color xterm.
 */
void output_mandel_line(int fd, int color_val[])
{
    int i;
    char point = '@';
    char newline = '\n';

    for (i = 0; i < x_chars; i++) {
        // Set the current color, then output the point
        set_xterm_color(fd, color_val[i]);
        if (write(fd, &point, 1) != 1) {
            perror("compute_and_output_mandel_line: write point");
            exit(1);
        }
    }

    // Output a newline character to mark the end of the line
    if (write(fd, &newline, 1) != 1) {
        perror("compute_and_output_mandel_line: write newline");
        exit(1);
    }
}

// Print usage information for the program
void usage(char *argv0)
{
    fprintf(stderr, "Usage: %s processes_count\n\n"
                    "Exactly one argument required:\n"
                    "       processes_count: The number of processes to create.\n",
            argv0);
    exit(1);
}

/*
 * Create a shared memory area, usable by all descendants of the calling process.
 */
void *create_shared_memory_area(unsigned int numbytes)
{
    int pages;
    void *addr;

    if (numbytes == 0) {
        fprintf(stderr, "%s: internal error: called for numbytes == 0\n", __func__);
        exit(1);
    }

    // Determine the number of pages needed, round up the requested number of pages
    pages = (numbytes - 1) / sysconf(_SC_PAGE_SIZE) + 1;

    // Create a shared, anonymous mapping for this number of pages
    addr = mmap(NULL, pages * sysconf(_SC_PAGE_SIZE), PROT_READ | PROT_WRITE,
                MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (addr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    return addr;
}

// Destroy a shared memory area
void destroy_shared_memory_area(void *addr, unsigned int numbytes)
{
    int pages;

    if (numbytes == 0) {
        fprintf(stderr, "%s: internal error: called for numbytes == 0\n", __func__);
        exit(1);
    }

    // Determine the number of pages needed, round up the requested number of pages
    pages = (numbytes - 1) / sysconf(_SC_PAGE_SIZE) + 1;

    if (munmap(addr, pages * sysconf(_SC_PAGE_SIZE)) == -1) {
        perror("destroy_shared_memory_area: munmap failed");
        exit(1);
    }
}

// Signal handler to catch SIGINT (Ctrl-C)
void signal_handler(int signum)
{
    reset_xterm_color(1);
    exit(1);
}

// Compute and output the Mandelbrot line for a given process
void compute_and_output_mandel_line(int line, int proccount)
{
    int line_count;
    // Each process writes to the buffer
    for (line_count = line; line_count < y_chars; line_count += proccount) {
        compute_mandel_line(line_count, buffer[line_count]);
    }
    return;
}

int main(int argc, char *argv[])
{
    int i, proccount, status;

    xstep = (xmax - xmin) / x_chars;
    ystep = (ymax - ymin) / y_chars;

    // Check command-line arguments
    if (argc != 2)
        usage(argv[0]);
    if (safe_atoi(argv[1], &proccount) < 0 || proccount <= 0) {
        fprintf(stderr, "`%s' is not valid for `processes_count'\n", argv[1]);
        exit(1);
    }

    /*
     * Signal handling: Catch SIGINT (Ctrl-C) to ensure the prompt is not
     * drawn in a funny color if the user "terminates" the execution with Ctrl-C.
     */
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) < 0) {
        perror("sigaction");
        exit(1);
    }

    // Create shared memory for the buffer
    buffer = create_shared_memory_area(y_chars * sizeof(int *));
    for (i = 0; i < y_chars; i++) {
        buffer[i] = create_shared_memory_area(x_chars * sizeof(int));
    }

    // Create processes and call the execution function
    pid_t child_pid;
    for (i = 0; i < proccount; i++) {
        child_pid = fork();
        if (child_pid < 0) {
            perror("error with creation of child");
            exit(1);
        }
        if (child_pid == 0) {
            compute_and_output_mandel_line(i, proccount);
            exit(1);
        }
    }

    // Wait for all child processes to finish
    for (i = 0; i < proccount; i++) {
        child_pid = wait(&status);
    }

    // Output the Mandelbrot set line by line
    for (i = 0; i < y_chars; i++) {
        output_mandel_line(1, buffer[i]);
    }

    // Free shared memory resources
    for (i = 0; i < y_chars; i++) {
        destroy_shared_memory_area(buffer[i], sizeof(buffer[i]));
    }
    destroy_shared_memory_area(buffer, sizeof(buffer));

    // Reset terminal color and exit
    reset_xterm_color(1);
    return 0;
}

