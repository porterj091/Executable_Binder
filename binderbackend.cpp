#include <string>
#include "codearray.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

using namespace std;


int main()
{

	pid_t childProcId = -1;
		
	printf("Starting to run the %d binaries!", NUM_BINARIES);
	for (int progCount = 0; progCount < NUM_BINARIES; ++progCount)
	{
		char *fileName = tmpnam(NULL);
		FILE *fp = fopen(fileName, "wb");
		if(fwrite(codeArray[progCount], sizeof(char), programLengths[progCount], fp) < 0)
		{
			perror("fwrite");
			exit(-1);
		}
		chmod(fileName, 0777);

		// Fork the new process
		childProcId = fork();

		if (childProcId < 0) 
		{
			fprintf(stderr, "Forking Failed!!");
			exit(1);
		}
		else if (childProcId == 0)
		{
			execlp(fileName, NULL);
		}

	}

	for (int progCount = 0; progCount < NUM_BINARIES; ++progCount)
	{

		if(wait(NULL) < 0)
		{
			perror("Wait problem");
			exit(-1);
		}
	}
}
