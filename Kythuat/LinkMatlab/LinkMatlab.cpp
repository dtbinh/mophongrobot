#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "engine.h"
#define  BUFSIZE 256

#pragma comment(lib, "libeng.lib")
#pragma comment(lib, "libmx.lib")

int main()
{
	Engine *ep;
	mxArray *T = NULL, *result = NULL;
	char buffer[BUFSIZE+1];

	if (!(ep = engOpen("\0"))) {
		fprintf(stderr, "\nCan't start MATLAB engine\n");
		return EXIT_FAILURE;
	}

	buffer[BUFSIZE] = '\0';
	engOutputBuffer(ep, buffer, BUFSIZE);

	char s[] = "X = 1:5";

	printf("Evaluating: %s!\n", s);
	
	engEvalString(ep, s);

	printf("%s", buffer);

	printf("Done!\n");

	engClose(ep);
	
	return EXIT_SUCCESS;
}








