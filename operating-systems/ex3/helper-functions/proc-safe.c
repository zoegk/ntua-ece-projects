#include <stdio.h>
#include <stdlib.h>

int safe_atoi(char *s, int *val)
{
	long l;
	char *endp;

	l=strtol(s, &endp, 10);
	if(s!=endp && *endp=='\0') {
		*val=l;
		return 0;
	} else
		return -1;
}

void *safe_malloc(size_t size)
{
	void *p;

	if((p=malloc(size))==NULL) {
		fprintf(stderr, "Out of memory, failed to allocate %zd bytes\n",
			size);
		exit(1);
	}

	return p;
}
