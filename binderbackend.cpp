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
		
	for (int progCount = 0; progCount < NUM_BINARIES; ++progCount)
	{
		char *fileName = tmpnam(NULL);
		chmod(fileName, 0777);

	}

	return 0;
}
