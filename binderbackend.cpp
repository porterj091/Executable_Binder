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
		
	printf("Starting to run the %d binaries!\n", NUM_BINARIES);

	for (int progCount = 0; progCount < NUM_BINARIES; ++progCount)
	{
		char *fileName = tmpnam(NULL);
		FILE *fp = fopen(fileName, "wb");

		// Write the contents to the file
		if(fwrite(codeArray[progCount], sizeof(char), programLengths[progCount], fp) < 0)
		{
			perror("fwrite");
			exit(-1);
		}
		
		// Close the file
		fclose(fp);

		// Make it executable
		chmod(fileName, 0777);

		// Fork the new process
		childProcId = fork();

		if (childProcId < 0) // Forking failed
		{
			fprintf(stderr, "Forking Failed!!");
			exit(1);
		}
		else if (childProcId == 0) // Child process
		{

			// Execute the new temp file
			if(execlp(fileName, "awesome", NULL) < 0)
			{
				perror("execlp");
				exit(-1);
			}
		}

	}

	for (int progCount = 0; progCount < NUM_BINARIES; ++progCount)
	{

		if(wait(NULL) < 0)
		{
			perror("wait");
			exit(-1);
		}
	}
}
