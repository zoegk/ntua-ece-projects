
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <errno.h>

#include "mandel-lib.h"

#define MANDEL_MAX_ITERATION 100000

#define perror_pthread(ret, msg) \				//macro is defined to handle errors related to pthread functions.
	do{ errno=ret; perror(msg); } while(0)

int safe_atoi(char *s, int *val){					//The safe_atoi function converts a string to an integer.

	long l;
	char *endp;
	
	// Convert string to long
	l = strtol(s, &endp, 10);

	// Check if conversion was successful and there is no extra characters
	if (s != endp && *endp == '\0') {
		*val = l;
		return 0;	// Success
	} 
	else
		return -1;	// Error
}


void *safe_malloc(size_t size){					//The safe_malloc function is a wrapper for the malloc function. It allocates memory of the specified size and checks if the allocation was successful.

	void *p;

	// Allocate memory
	if ((p = malloc(size)) == NULL) {
		fprintf(stderr, "Out of memory, failed to allocate %zd bytes\n",
			size);
		exit(1);
	}

	return p;
}

//Output at the terminal is is x_chars wide by y_chars long.

int y_chars = 50;
int x_chars = 90;

/*
 * The part of the complex plane to be drawn:
 * upper left corner is (xmin, ymax), lower right corner is (xmax, ymin).
*/

double xmin = -1.8, xmax = 1.0;
double ymin = -1.0, ymax = 1.0;

/*
 * Every character in the final output is
 * xstep x ystep units wide on the complex plane.
 */

double xstep;
double ystep;


/*
 * This function computes a line of output
 * as an array of x_char color values.
 */

void compute_mandel_line(int line, int color_val[]){

	/*
	 * x and y traverse the complex plane.
	 */

	double x, y;

	int n;
	int val;

	// Find out the y value corresponding to this line 
	y = ymax - ystep * line;

	// and iterate for all points on this line
	for (x = xmin, n = 0; n < x_chars; x+= xstep, n++) {

		//Compute the point's color value

		val = mandel_iterations_at_point(x, y, MANDEL_MAX_ITERATION);
		if (val > 255){
			val = 255;
		}

		//And store it in the color_val[] array

		val = xterm_color(val);
		color_val[n] = val;
	}
}

/*
 * This function outputs an array of x_char color values
 * to a 256-color xterm.
 */

void output_mandel_line(int fd, int color_val[]){

	int i;

	char point ='@';		// Character representing a point in the Mandelbrot set
	char newline='\n';		// Newline character


	for (i = 0; i < x_chars; i++) {

		//Set the current color, then output the point

		set_xterm_color(fd, color_val[i]);	// Set the color for the current point

		if (write(fd, &point, 1) != 1) {	// Write the point to the file descriptor
			perror("compute_and_output_mandel_line: write point");
			exit(1);
		}
	}

	//Now that the line is done, output a newline character

	if (write(fd, &newline, 1) != 1) {		// Write the newline character to the file descriptor
		perror("compute_and_output_mandel_line: write newline");
		exit(1);
	}
}


/*
 * Catch SIGINT (Ctrl-C) with the sigint_handler to ensure the prompt is not
 * drawn in a funny colour if the user "terminates" the execution with Ctrl-C.
 */

void signal_handler(int sign){

	reset_xterm_color(1); // Reset the color of the xterm
	exit(1);
}


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;	// Initialize mutex variable
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;		// Initialize condition variable
int thread_count;					// Total number of threads
int next_thread = 0;					// Index of the next thread to execute

void *compute_and_output_mandel_line(void *current_thread){

    int line, color_val[x_chars];	// Array to store color values for each pixel in a line


    for (line = (int)current_thread; line < y_chars; line += thread_count) {

        compute_mandel_line(line, color_val); 	// Compute the Mandelbrot line for the current thread

        pthread_mutex_lock(&mutex);		// Acquire the lock on the mutex


	// Wait until it's the turn of the current thread to execute
        while ((int)current_thread != next_thread) {
            pthread_cond_wait(&cond, &mutex);	// Release the lock and wait for a signal
        }

        output_mandel_line(1, color_val);			// Output the computed Mandelbrot line
        next_thread = (next_thread + 1) % thread_count;	// Update the index of the next thread
        pthread_cond_broadcast(&cond);				// Signal all threads that they can check the condition again
        pthread_mutex_unlock(&mutex);				// Release the lock on the mutex
    }

    return NULL;	// Exit the thread
}


int main(int argc, char **argv){

    int line, ret;

    xstep = (xmax - xmin) / x_chars;		// Calculate the step size for the x-axis
    ystep = (ymax - ymin) / y_chars;		// Calculate the step size for the y-axis


    // Check command-line arguments and thread count
    if((argc!=2)||(safe_atoi(argv[1], &thread_count)<0)||(thread_count<=0)) {
        fprintf(stderr, "Usage: %s thread_count\n\n"
            "Exactly one argument required:\n"
            "    thread_count: The number of threads to create.\n",
            argv[0]);
            exit(1);
    }

    struct sigaction sa;
    sa.sa_handler=signal_handler;		// Set the signal handler function
    sa.sa_flags=0;
    sigemptyset(&sa.sa_mask);
    if(sigaction(SIGINT, &sa, NULL)<0) {		// Set up the signal handler for SIGINT (Ctrl+C)
        perror("sigaction");
        exit(1);
    }

    pthread_t thread[thread_count];		// Array to hold thread identifiers

    for(line=0; line<thread_count; line++) {
        ret=pthread_create(&thread[line], NULL, compute_and_output_mandel_line, (void*)line);
        if(ret) {
            perror_pthread(ret, "pthread_create");	// Print an error message if thread creation fails
            exit(1);
        }
    }

    for(line=0; line<thread_count; line++) {
        ret=pthread_join(thread[line], NULL);		// Wait for each thread to finish its execution
        if(ret)
            perror_pthread(ret, "pthread_join");		// Print an error message if thread joining fails
    }

    pthread_mutex_destroy(&mutex);		// Destroy the mutex variable
    pthread_cond_destroy(&cond);			// Destroy the condition variable


    reset_xterm_color(1);	// Reset the xterm color settings
    return 0;
}

