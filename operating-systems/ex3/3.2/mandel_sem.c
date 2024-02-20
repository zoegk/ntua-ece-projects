
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

sem_t *mySem; //globalize the address so it can be visible from all threads
int thread_count; //globalize the thread_count so it can be visible from all threads

void *compute_and_output_mandel_line(void *current_thread){

	int line, color_val[x_chars]; 		//color_val is not shared among threads

	for(line=(int)current_thread; line<y_chars; line+=thread_count) {

		compute_mandel_line(line, color_val);  				// Perform the computation for the current line (parallel computation)
		if(sem_wait(&mySem[(int)current_thread])<0) { 			// Wait for my turn to output by waiting on my semaphore
			perror("sem_wait");              
			exit(1);                        
		}

		output_mandel_line(1, color_val); 				// Critical section: Output the computed line
		if(sem_post(&mySem[((int)current_thread+1)%thread_count])<0) { // Unlock the next thread to output (circularly)
			perror("sem_post");                             
			exit(1);
		}
	}

	return NULL;
}

int main(int argc, char **argv){ //Main thread
	
	int line, ret;

	// compute the step size for each pixel

	xstep = (xmax - xmin) / x_chars;
	ystep = (ymax - ymin) / y_chars;


	//Check if arguments are OK 

	if((argc!=2)||(safe_atoi(argv[1], &thread_count)<0)||(thread_count<=0)) {
		fprintf(stderr, "Usage: %s thread_count\n\n"
			"Exactly one argument required:\n"
			"	thread_count: The number of threads to create.\n",
			argv[0]);
			exit(1);
	}

	//signal handling

	struct sigaction sa;
	sa.sa_handler=signal_handler;	//set the function to call when a signal is received
	sa.sa_flags=0;
	sigemptyset(&sa.sa_mask);
	if(sigaction(SIGINT, &sa, NULL)<0) {	//register the signal handler for SIGINT
		perror("sigaction");
		exit(1);
	}

	mySem=(sem_t*)safe_malloc(thread_count*sizeof(sem_t)); //allocate memory for the semaphores
							 	//we use one semaphore per thread


	if(sem_init(&mySem[0], 0, 1)<0) { 	//initialize first semaphore to value 1 (unlocked)
		perror("sem_init");     	//(thread[0] outputs first the 0 line)
		exit(1);
	}
	for(line=1; line<thread_count; line++) { //initialize the other semaphores to value 0 (locked)
		if(sem_init(&mySem[line], 0, 0)<0) {
			perror("sem_init");
			exit(1);
		}
	}

	
	//create threads
	
	pthread_t thread[thread_count];
	for(line=0; line<thread_count; line++) {	//create the threads and pass the thread index as an argument
		ret=pthread_create(&thread[line], NULL, compute_and_output_mandel_line, (void*)line);
		if(ret) {
			perror_pthread(ret, "pthread_create");
			exit(1);
		}
	}

	/*
	 * wait for all threads to terminate
	 */

	for(line=0; line<thread_count; line++) {	
		ret=pthread_join(thread[line], NULL);
		if(ret)
			perror_pthread(ret, "pthread_join");
	}

	/*
	 * destroy the semaphores
	 */
	for(line=0; line<thread_count; line++) {	//destroy all the semaphores
		if(sem_destroy(&mySem[line])<0) {
			perror("sem_destroy");
			exit(1);
		}
	}

	free(mySem);		//free the semaphore memory

	reset_xterm_color(1);	//reset the terminal color
	return 0;
}

