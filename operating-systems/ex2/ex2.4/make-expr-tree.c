#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// Required headers for the project
#include "proc-common.h"
#include "tree.h"

#define SLEEP_PROC_SEC 1

// Recursive function that spawns child processes and computes the values
void fork_procs(struct tree_node *parent, int fdw){
    pid_t child_pid;
    int wstatus, i;

    // Changes the name of the process to the name of the current node
    change_pname(parent->name);

    // Prints a message indicating that the current node is starting
    printf("%s: Starting...\n", parent->name);

    if(parent->nr_children==0){ // If the node has no children, it's a leaf and its value is written to the pipe
        int value=atoi(parent->name);  // Converts the string value of the leaf node to an integer
        if(write(fdw, &value, sizeof(value))!=sizeof(value)){  // Writes the value to the pipe and checks for errors
            perror("write to pipe");
            exit(1);
        }
        close(fdw);  // Closes the write end of the pipe
        sleep(SLEEP_PROC_SEC);  // Sleeps for a while
        exit(13);  // Exits with status code 13
    }
    else {  // If the node has children, it's an operator and its children are recursively evaluated
        int pipefd[2];
        if(pipe(pipefd)==-1){  // Creates a pipe for inter-process communication and checks for errors
            perror("pipe");
            exit(1);
        }
        for(i=0; i<parent->nr_children; i++){  // Spawns a child process for each child of the current node
            child_pid=fork();  // Forks a new process and stores the returned PID in child_pid
            if(child_pid<0) {  // If forking fails, prints an error message and exits
                perror("fork");
                exit(1);
            }
            if(child_pid==0) {  // If child_pid is 0, this is the child process and it evaluates the i-th child
                close(pipefd[0]);  // Closes the read end of the pipe
                fork_procs(parent->children+i, pipefd[1]);  // Recursively evaluates the i-th child
            }
        }
        close(pipefd[1]);  // Closes the write end of the pipe in the parent process
        int value[2];
        for(i=0; i<parent->nr_children; i++){  // Reads the values computed by the children from the pipe
            if(read(pipefd[0], &value[i], sizeof(value[i]))!=sizeof(value[i])) { 
	    	perror("read from pipe");
		exit(1);
	    }
	}
	close(pipefd[0]);
    	// Computes the result of the operation according to the operator in the parent node
   	int result;
    	if(!strcmp(parent->name, "+")){
        	result = value[0]+value[1];
    	}
    	if(!strcmp(parent->name, "*")){
        	result=value[0]*value[1];
    	}
    
    	// Prints the value computed by the current process
    	printf("Me: %ld, i have computed: %i %s %i = %i\n", (long)getpid(), value[0], parent->name, value[1], result);

    	// Writes the result to the pipe
    	if(write(fdw, &result, sizeof(result))!=sizeof(result)){
        	perror("write to pipe");
        	exit(1);
    	}
    	close(fdw);
    
    	// Waits for the termination of all the children and prints their exit status
    	for(i=0; i<parent->nr_children; i++){
        	if(wait(&wstatus)==-1){
            		perror("wait");
            		exit(1);
        	}
        	explain_wait_status(child_pid, wstatus);
    	}

    	// Exits the process with exit status 7
   	exit(7);
    }
}
int main(int argc, char **argv){
    int wstatus, result;
    struct tree_node *root;
    int pipefd[2];
    pid_t pid_root;

	
    // Checks if the command is entered correctly, and prints usage message if it is not
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_tree_file>\n\n", argv[0]);  // Prints usage message if the command is not entered correctly
        exit(1);
    }

    // Reads the expression tree from the input file and prints it
    root = get_tree_from_file(argv[1]);
    print_tree(root);  // Prints the expression tree read from the input file


    // Creates a pipe for inter-process communication
    if(pipe(pipefd)==-1) {
        perror("main: pipe");  // Prints an error message if pipe creation fails
        exit(1);
    }


    // Forks a process to evaluate the expression tree and creates a process tree
    pid_root=fork();
    if(pid_root<0) {
        perror("main: fork");  // Prints an error message if forking fails
        exit(1);
    }

    if(pid_root==0){
        close(pipefd[0]);
        fork_procs(root, pipefd[1]);  // Starts the recursion to evaluate the expression tree
    }
    close(pipefd[1]);


    // Reads the result of the evaluation from the pipe and prints it
    if(read(pipefd[0], &result, sizeof(result))!=sizeof(result)){
        perror("main: read from pipe");  // Prints an error message if read from pipe fails
        exit(1);
    }

    close(pipefd[0]);

    show_pstree(pid_root);  // Shows the process tree

    // Waits for the termination of the root process and prints its exit status
    if(wait(&wstatus)==-1){
        perror("main: wait");  // Prints an error message if the wait for the process fails
        exit(1);
    }

    explain_wait_status(pid_root, wstatus);  // Explains the status of the root process that has been waited for

    printf("The result of the expression is: %i\n", result);  // Prints the result of the evaluated expression

    return 0;


}

