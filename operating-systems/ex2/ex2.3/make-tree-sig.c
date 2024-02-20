#include <unistd.h> 
#include <stdio.h>  
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/wait.h>  

#include "proc-common.h" 
#include "tree.h"         

/* This function forks the child processes recursively for each node in the tree */

void fork_procs(struct tree_node *parent) {
   int i, wstatus;
   change_pname(parent->name);    // Changes the process name to the name of the parent node
   printf("%s: Starting...\n", parent->name);  // Prints a message indicating that the parent node is starting

   if (parent->nr_children == 0) {
       if (raise(SIGSTOP) != 0) {  // Stops the process and waits for a signal to be sent to it
           perror("raise");  // Prints an error message if there was an error with the raise() call
           exit(1);  // Exits the process with an error code
       }
       printf("%s is awake!\n", parent->name);  // Prints a message indicating that the parent node has woken up
       exit(13);  // Exits the process with a specific exit code
   } 
   else {
       pid_t pid[parent->nr_children];
       for (i = 0; i < parent->nr_children; i++) {
           pid[i] = fork();  // Forks the process to create a child process
           if (pid[i] < 0) {
               perror("fork");  // Prints an error message if there was an error with the fork() call
               exit(1);  // Exits the process with an error code
           } 
           else if (pid[i] == 0) {
               fork_procs(parent->children+i);  // Recursively calls fork_procs() to fork the child processes for the current node's children
               exit(0);  // Exits the child process with a success exit code
           } 
           else {
               change_pname(parent->name);  // Changes the process name to the name of the parent node
           }
       }
       wait_for_ready_children(parent->nr_children);  // Waits for all child processes to be ready
       if (raise(SIGSTOP) != 0) {  // Stops the process and waits for a signal to be sent to it
           perror("raise");  // Prints an error message if there was an error with the raise() call
           exit(1);  // Exits the process with an error code
       }
       printf("%s is awake!\n", parent->name);  // Prints a message indicating that the parent node has woken up
       for (i = 0; i < parent->nr_children; i++) {
           if (kill(pid[i], SIGCONT) < 0) {  // Sends a signal to the child process to wake it up
               perror("kill");  // Prints an error message if there was an error with the kill() call
               exit(1);  // Exits the process with an error code
           } 
           else if (wait(&wstatus) == -1) {  // Waits for the child process to exit
               perror("wait");  // Prints an error message if there was an error with wait() function
               exit(1); // Exits the program with a failure status
           } 
           else {
               explain_wait_status(pid[i], wstatus); // Prints information about the status of the child process
           }
       }
       exit(7); // Exits the child process with status 7
   }
}

int main(int argc, char **argv) {
   pid_t pid_root, pid_wait;
   int wstatus;
   struct tree_node *root;

   if (argc != 2) {  // Checks if the program was called with the correct number of arguments
       fprintf(stderr, "Usage: %s <input_tree_file>\n\n", argv[0]);  // Prints an error message to stderr if the program was not called correctly
       exit(1);  // Exits the program with a failure status
   }

   root = get_tree_from_file(argv[1]);  // Read in the tree structure from the input file
   print_tree(root);  // Print the tree structure to the console

/* Fork root of process tree */
   pid_root = fork();  // Fork the initial process to create the root of the process tree
   if (pid_root < 0) {
       perror("main: fork");  // Prints an error message to stderr if the fork() function fails
       exit(1);  // Exits the program with a failure status
   } 
   else if (pid_root == 0) {  // If this is the child process
       fork_procs(root);  // Fork the child processes for the tree
       exit(1);  // Exits the child process with a failure status
   }

/* Father (initial process) */
   wait_for_ready_children(1);  // Wait for the root of the process tree to be ready

/* Print the process tree with root_pid */
   show_pstree(pid_root);  // Print a visualization of the process tree to the console

/* Wake up the root of the process tree */
   if (kill(pid_root, SIGCONT) < 0) {
       perror("main: kill");  // Prints an error message to stderr if the kill() function fails
       exit(1);  // Exits the program with a failure status
   }

/* Wait for the root of the process tree to terminate */
   pid_wait = wait(&wstatus);  // Waits for the root of the process tree to terminate
   if (pid_wait == -1) {
       perror("main: wait");  // Prints an error message to stderr if the wait() function fails
       exit(1);  // Exits the program with a failure status
   }

/* Print the exit status of the root process */
   explain_wait_status(pid_wait, wstatus);  // Prints information about the status of the root process

   return 0;  // Exits the program with a success status

}

