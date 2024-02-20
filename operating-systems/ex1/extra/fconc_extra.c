#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// Set buffer size to 1024
#define BUFFSIZE 1024

// Helper function to write to file
void doWrite(int fd, const char *buff, int len) {
    int bytes_written = 0;
    while (bytes_written < len) {
        // Write data to file descriptor
        int result = write(fd, buff + bytes_written, len - bytes_written);
        // Check for error in write
        if (result < 0) {
            perror("write error");
            exit(EXIT_FAILURE);
        }
        bytes_written += result;
    }
}

// Helper function to write data from file to file descriptor
void write_file(int fd, const char *infile) {
    // Open input file
    int infile_fd = open(infile, O_RDONLY);
    if (infile_fd < 0) {
        // Check for error in opening input file
        perror("open error");
        exit(EXIT_FAILURE);
    }
    // Read data from input file and write it to file descriptor
    char buffer[BUFFSIZE];
    int bytes_read;
    while ((bytes_read = read(infile_fd, buffer, BUFFSIZE)) > 0) {
        doWrite(fd, buffer, bytes_read);
    }
    // Close input file
    close(infile_fd);
}

// Main function
int main(int argc, char *argv[]) {
    const char *outfile;
    int outfile_fd, i;

    // Check for correct number of arguments
    if (argc < 3) {
        printf("Usage: %s infile1 infile2 ... outfile\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Set output file name
    outfile = argv[argc - 1];

    // Check if input and output files are the same
    for (i = 1; i < argc - 1; i++) {
        if (strcmp(argv[i], outfile) == 0) {
            printf("Error: Input and output files must be different.\n");
            exit(EXIT_FAILURE);
        }
    }

    // Open output file
    outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (outfile_fd < 0) {
        // Check for error in opening output file
        perror("open error");
        exit(EXIT_FAILURE);
    }

    // Write data from input files to output file
    for (i = 1; i < argc - 1; i++) {
        write_file(outfile_fd, argv[i]);
    }

    // Close output file
    close(outfile_fd);

    // Exit program with success status
    exit(EXIT_SUCCESS);
}

