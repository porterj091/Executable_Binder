#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//Parent process
int main()
{
pid_t  pid;
	/* fork another process */
	pid = fork();
	if (pid < 0) { /* error occurred */
		fprintf(stderr, "Fork Failed");
		exit(-1);
	}
	else if (pid == 0) { /* child process */
		if(execlp("/bin/ls", "ls", NULL) < 0)
		{
			perror("execlp");
			exit(-1);
		}
	}
	else { /* parent process */
	/* parent will wait for the child to complete */
		if(wait (NULL) < 0)
		{
			perror("execlp");	
			exit(-1);
		}
		printf ("Child Complete");
	}
}

