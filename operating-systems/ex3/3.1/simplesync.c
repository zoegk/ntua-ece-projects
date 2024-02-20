/*
 * simplesync.c
 *
 * A simple synchronization exercise.
 *
 * Vangelis Koukis <vkoukis@cslab.ece.ntua.gr>
 * Operating Systems course, ECE, NTUA
 *
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/* 
 * POSIX thread functions do not return error numbers in errno,
 * but in the actual return value of the function call instead.
 * This macro helps with error reporting in this case.
 */
#define perror_pthread(ret, msg) \
	do { errno = ret; perror(msg); } while (0)

#define N 10000000

/* Dots indicate lines where you are free to insert code at will */
/* ... */
#if defined(SYNC_ATOMIC) ^ defined(SYNC_MUTEX) == 0
# error You must #define exactly one of SYNC_ATOMIC or SYNC_MUTEX.
#endif

#if defined(SYNC_ATOMIC)
# define USE_ATOMIC_OPS 1
#else
# define USE_ATOMIC_OPS 0
#endif

pthread_mutex_t lock;

void *increase_fn(void *arg) {
    int i, ret;
    volatile int *ip = arg; // declare a volatile integer pointer and initialize 
                            // it with the argument passed to the function
	
    fprintf(stderr, "About to increase variable %d times\n", N); 
    // print a message to stderr indicating the number of times the variable will 
    be increased
    for (i = 0; i < N; i++) { // loop N times
        if (USE_ATOMIC_OPS) { // if the USE_ATOMIC_OPS flag is defined, use an 
                              // atomic operation to increment the variable
            __sync_fetch_and_add(&ip, 1); // sync with gcc atomic operations 
		} 
        else { // otherwise, use a mutex to synchronize access to the variable
            ret = pthread_mutex_lock(&lock); // acquire the lock
            if (ret) { // if the lock cannot be acquired, print an error message
                       // and exit
                perror_pthread(ret, "pthread_mutex_lock");
                exit(1);
            }
            ++(*ip); // increment the variable
            ret = pthread_mutex_unlock(&lock); // release the lock
            if (ret) { // if the lock cannot be released, print an error message 
                       // and exit
                perror_pthread(ret, "pthread_mutex_unlock");
                exit(1);
            }
        }
    }
    fprintf(stderr, "Done increasing variable.\n"); 
    // print a message to stderr indicating that the variable has been
    // incremented N times

    return NULL;
}

void *decrease_fn(void *arg) {
    int i, ret;
    volatile int *ip = arg; // declare a volatile integer pointer and initialize 
                            // it with the argument passed to the function

    fprintf(stderr, "About to decrease variable %d times\n", N);
    // print a message to stderr indicating the number of times the variable will 
    // be increased
    for (i = 0; i < N; i++) { // loop N times
        if (USE_ATOMIC_OPS) { // if the USE_ATOMIC_OPS flag is defined, use an
                              // atomic operation to increment the variable
            __sync_fetch_and_sub(&ip, 1); // sync with gcc atomic operations
        } 
        else { // otherwise, use a mutex to synchronize access to the variable
            ret = pthread_mutex_lock(&lock); // acquire the lock
            if (ret) { // if the lock cannot be acquired, print anerror message
                       //and exit
                perror_pthread(ret, "pthread_mutex_lock");
                exit(1);
            }
            --(*ip); // decrement the variable
            ret = pthread_mutex_unlock(&lock); // release the lock
            if (ret) { // if the lock cannot be released, print an error message
                       // and exit
                perror_pthread(ret, "pthread_mutex_unlock");
                exit(1);
            }
        }
    }
    fprintf(stderr, "Done decreasing variable.\n");
    // print a message to stderr indicating that the variable has been decreased
    // N times

    return NULL;
}

int main(int argc, char *argv[]) {
    int val, ret, ok;
    pthread_t t1, t2;

    // Initialize mutex   
    pthread_mutex_init(&lock, NULL);

    /*
    * Initial value
    */
    val = 0;

    /*
    * Create threads
    */
    ret = pthread_create(&t1, NULL, increase_fn, &val);
    if (ret) {
        perror_pthread(ret, "pthread_create");
        exit(1);
    }
    ret = pthread_create(&t2, NULL, decrease_fn, &val);
    if (ret) {
        perror_pthread(ret, "pthread_create");
        exit(1);
    }

    /*
    * Wait for threads to terminate
    */
    ret = pthread_join(t1, NULL);
    if (ret)
        perror_pthread(ret, "pthread_join");
    ret = pthread_join(t2, NULL);
    if (ret)
        perror_pthread(ret, "pthread_join");

    /*
    * Is everything OK?
    */
    ok = (val == 0);

    // Destroy mutex
    ret = pthread_mutex_destroy(&lock);
    if(ret) {
        perror_pthread(ret, "pthread_mutex_destroy");
    }

    printf("%sOK, val = %d.\n", ok ? "" : "NOT ", val);

    return ok;
}

