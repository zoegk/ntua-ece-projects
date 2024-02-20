#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "proc-common.h"
#include "tree.h"

#define LEAF_EXIT_STATUS 13
#define NON_LEAF_EXIT_STATUS 7
#define SLEEP_CHILD_SEC 10
#define SLEEP_TREE_SEC 3

void fork_procs(struct tree_node *parent) {
    pid_t pidChild;
    int i, wstatus;

    change_pname(parent->name); //change the name of the process to the name of the node in the tree
    printf("%s: Starting...\n", parent->name);//process has started

    if (parent->nr_children == 0) { //if the node has no children, sleep for a designated amount of time and exit
        printf("%s: Sleeping...\n", parent->name);
        sleep(SLEEP_CHILD_SEC);
        printf("%s: Exiting...\n", parent->name);
        exit(LEAF_EXIT_STATUS);
    } 
    else { //if the node has children, create a new child process for each child node in the tree
        for (i = 0; i < parent->nr_children; i++) {
            pidChild = fork();
            if (pidChild < 0) { //if the fork failed, exit code 1
                perror("fork");
                exit(1);
            } 
            else if (pidChild == 0) { //if the fork was successful, call fork_procs() using the child node as an argument
                fork_procs(parent->children + i);
            }
        }

        printf("%s: Waiting...\n", parent->name);
        for (i = 0; i < parent->nr_children; i++) { //wait for all child processes to terminate 
            pidChild = wait(&wstatus);
            if (pidChild == -1) { //if the wait fails, exit code 1
                perror("wait");
                exit(1);
            }
            explain_wait_status(pidChild, wstatus); //exit status of each child process
        }

        printf("%s: Exiting...\n", parent->name);
        exit(NON_LEAF_EXIT_STATUS);
    }
}

int main(int argc, char **argv) //read input file name {
    pid_t pid_root, pid_wait;
    int wstatus;
    struct tree_node *root;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_tree_file>\n\n", argv[0]);
        exit(1);
    }

    root = get_tree_from_file(argv[1]);
    print_tree(root); //print tree

    /* Fork root of process tree */
    pid_root = fork();
    if (pid_root < 0) {
        perror("main: fork");
        exit(1);
    } 
    else if (pid_root == 0) {
        fork_procs(root);
    }

    /* Wait for the process tree to be created */
    sleep(SLEEP_TREE_SEC);

    /* Print the process tree with root_pid */
    show_pstree(pid_root);

    /* Wait for the root of the process tree to terminate */
    printf("Initial process: Waiting...\n");
    pid_wait = wait(&wstatus);
    if (pid_wait == -1) { //if the wait fails, exit code 1
        perror("main: wait");
        exit(1);
    }
    explain_wait_status(pid_wait, wstatus);

    printf("Initial process: All done, exiting...\n");

    return 0;
}

