#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

	//--------------------------------------------
	// NAME- Iosyf Saleh
	// CLASS- XIb
	// NUMBER- 18
	// PROBLEM- #2
	// FILE NAME- Makefile
	// FILE PURPOSE-
	// This is the makefile for the task for the OS homework
	// It needs the following argument as input to work- make ./wc
	// Then the program wc.c can be executed by writing -./wc (arguments)- in the terminal
	//---------------------------------------------
	
char** parse_cmdline (const char* cmdline){
	char **args= malloc (99 * sizeof(char *)+100);
	char * pch;
	int i, count=1, a=0;
	for (i=0, count=0; cmdline[i]; i++)
	  count += (cmdline[i] == ' ');
	char *ok = malloc(sizeof(char *)+100);
	for (i=0;i<=strlen(cmdline);i++)
	{
		ok[i]=cmdline[i];
	}
	pch = strtok (ok," ");
	while (pch != NULL)
	{
		args[a] = pch;
		a=a+1;
		pch = strtok (NULL, " ");
	}
	//free (ok);
	//const char *file = on[0];
	//printf("%s\n",file);
	//execv(file[0], file);
	//perror("execv");
	free(pch);
	//execv("/bin/ls", pch);
	return args;
};

int main(){
	char *line = NULL, *tmp = NULL;
	//pid_t child_pid;
	//int child_status;
    size_t size, index;
    pid_t pit;
    char **mass= malloc (99 * sizeof(char *)+100);
    int ch;
    while (1)
    {
		size =0;
		index =0;
		ch = EOF;
		while (ch) {
			ch = getc(stdin);

			/* Check if we need to stop. */
			if (ch == EOF || ch == '\n')
				ch = 0;

			/* Check if we need to expand. */
			if (size <= index) {
				size += 10;
				tmp = realloc(line, size);
				if (!tmp) {
					free(line);
					line = NULL;
					break;
				}
				line = tmp;
			}

			/* Actually store the thing. */
			line[index++] = ch;
		}
		mass=parse_cmdline(line);
		pit = fork();
		if (pit == 0) {
			execv(mass[0], mass);
			perror("./shell");
		} else if (pit > 0) {
			
		}
	//	printf("%s", *mass );
		line = NULL;
		tmp = NULL;
		mass = NULL;
		free (line);
		free (mass);
	}
	
	return 0;
}
