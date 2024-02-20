#include <stdio.h>
#include <unistd.h>
void zing(void) {
	printf("Welcome back, %s\n", getlogin() ) ; }

