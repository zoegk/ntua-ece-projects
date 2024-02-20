#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "proc-common.h"

#define SLEEP_PROC_SEC  10
#define SLEEP_TREE_SEC  3

/*
 * create this process tree:
 * A-+-B---D
 *   `-C
 */
void fork_procs(void) {
    pid_t pidB, pidC, pidD, killed_child_pid; //creating a pid  
    int status;                              //variable for each node

    change_pname("A"); //change the name of the current process
                       //change_pname() is defined in proc-common.h
    printf("A: Starting...\n");
    pidB = fork();   //fork for child B
    if (pidB < 0) { //if fork() fails, return exit code 1
        perror("fork");
        exit(1);
    } 
    else if (pidB == 0) { //if fork() succeeds, the current process is a child process and its behavior is defined by the if and elif processes
        // I'm B         
        change_pname("B");
        printf("B: Starting...\n");
        pidD = fork();
        if (pidD < 0) {
            perror("fork");
            exit(1);
        } 
        else if (pidD == 0) { //if fork() succeeds the current process is the parent process
            // I'm D
            change_pname("D");
            printf("D: Starting...\n");
            printf("D: Sleeping...\n");//process D sleeps for a designated amount of time
            sleep(SLEEP_PROC_SEC);
            printf("D: Exiting...\n");
            exit(13);//exits with exit code 13
        }
        printf("B: Waiting...\n");
        killed_child_pid = wait(&status); //process B waits for its child process D to terminate
        explain_wait_status(killed_child_pid, status);//once D terminates, B prints a message explaining the exit status of D
//explain_wait_status() is defined in proc-common.h
        printf("B: Exiting...\n");
        exit(19);//exits with exit code 19
    }

    pidC = fork();
    if (pidC < 0) {
        perror("fork");
        exit(1);
    } else if (pidC == 0) {
        // I'm C
        change_pname("C");
        printf("C: Starting...\n");
        printf("C: Sleeping...\n");//process C sleeps for a designated amount of time
        sleep(SLEEP_PROC_SEC);
        printf("C: Exiting...\n");
        exit(17);//exits with exit code 17
    }

    printf("A: Waiting...\n");
    int i;
    for (i = 0; i < 2; i++) {
        killed_child_pid = wait(&status);//process A waits for its children B and C to terminate
        explain_wait_status(killed_child_pid, status);
    }
    printf("A: Exiting...\n");//both children have terminated, exit status 0
}

/*
 * The initial process (our program) forks the root of the process tree (A),
 * waits for the process tree to be completely created (with sleep()),
 * then takes a photo of it using show_pstree() and waits for A to die.
 *
 * How to wait for the process tree to be ready?
 *  -> sleep for a few seconds and hope for the best.
 *
 * Also, the children leaf processes stay active (they sleep()) for a few seconds
 * (longer than the sleep time of the initial process), so the user can see the whole
 * process tree created.
 *
 * The parent processes wait until all of their children die.
*/
int main(void) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0) {
        perror("main: fork");
        exit(1);
    } 
    else if (pid == 0) {
        // I'm the child
        fork_procs();
        exit(0);
    }

    // I'm the parent
    sleep(SLEEP_TREE_SEC);
    show_pstree(pid);

    pid = wait(&status);
    explain_wait_status(pid, status);
    return 0;
}

