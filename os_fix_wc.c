//--------------------------------------------
// NAME: Iosyf Saleh
// CLASS: XIb
// NUMBER: 18
// PROBLEM: #1
// FILE NAME: wc.c
// FILE PURPOSE:
// This is the program for the OS homework.
// When run it takes the arguments from the terminal and the files with those names in your current directory will be checked.
// As output the program returns what the wc command would return. (Almost - doesn't have all of the wc command's functions) 
//---------------------------------------------

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int File_Compiler(int wc[],int q,int argc,char *Argv[]);
//--------------------------------------------
// FUNCTION: File_Compiler
// предназначение на функцията : open the file specified in the terminal; get the number of lines; words; characters; from the file, storing them in wc_temp; then adding the sum to wc[] from the main program which is the total
// PARAMETERS: wc[], q, argc, Argv[];
// q - the current number of the argument being read from the terminal.
// wc[] - total score/sum of wc_temp and it's self.
// argc,Argv[] - number of arguments in the terminal when executing the program, the arguments themselves;
// VARIABLES:
// i - used as a counter
// state - used to count the words - is a filter.
// buff - buffer - used to store all the charecters from the file with the name of Argv[q]
// fd - used to open the file
//----------------------------------------------

int main(int argc, char *Argv[])
{
	int wc[]={0,0,0};
	int wc_temp[] ={0,1,0};
	int state; // Promenliva izpolzvana za filtrirane na tova koga ima duma
	int i=0; // Promenliva da gleda kolko simvola usera vuvezda pri "-" kato argument na Argv
	int q=0; // Izpolzvana pri cikula s argc taka che da mine prez vsichki Argv komentari
	char c; // Poredniat vuveden simvol ot usera v sluchai na "-"
	char minus='-'; //selfexplanatory
	for (q=1;q<argc;q++) // Za vsichki argumenti ot terminala zapochvaiki sled 1rvia ((./a.out) || (./wc))
	{
		if ((sizeof(Argv[q]) > 1) && (Argv[q][0] == minus)) // If Argv[q] is = to "-" then the program starts reciving input from the terminal unitl the user presses ctrl+d
		{
			i=0;
			while ((c=getchar()) != EOF) // Dokato usera ne natisne ctrl+d shte priema input ot klaviaturata
			{
				i++;
				if (c == '\n')
				{
					state = 1;
					wc_temp[0]++;
				}
				else if (c == ' ' || c == '\t' || i==0)
				{
					state = 1;
				}
				else
				{
					if (state == 1)
					{
						wc_temp[1]++;
					}
					state=0;
				}
			}
			if (i==0)
			{
					wc_temp[1]=0;
			}
			printf ("\n\t%d\t%d\t%d\t-\n", wc_temp[0], wc_temp[1], i);
			wc[0]+=wc_temp[0];
			wc[1]+=wc_temp[1];
			wc[2]+=i;
			for (i=0;i<=2;i++)
			{
				wc_temp[i]=0;
			}
			wc_temp[1]=1;
		}
		else
		{
			File_Compiler(wc,q,argc,Argv);
			i=-1;
		}
		
	}
	if (argc > 2)
	{
		printf ("\t%d\t%d\t%d\ttotal\n",wc[0],wc[1],wc[2]);
	}
	return 0;
}
//--------------------------------------------
// FUNCTION: main
// предназначение на функцията : open the file specified in the terminal; get the number of lines; words; characters; from the file, storing them in wc_temp; then adding the sum to wc[] from the main program which is the total
// PARAMETERS: argc,Argv[] - number of arguments in the terminal when executing the program, the arguments themselves;
//----------------------------------------------

int File_Compiler(int wc[],int q,int argc,char *Argv[])
{
	int i=0; // izpolzvana za for cikli
	int a = 0; // izpolzvana za da poluchi stoinostta na status_read
	int fd; // Izpolzvana da otvori faila
	int wc_temp[3]={0,0,0}; // wc_temp e izpolzvano da zapazi stoinostite (bori na \n-ove ; dumi ; simvoli)
	int state=0; // filtur za tova dali e duma ili ne
	char buff[200]; // buffer - poluchava vsichki simvoili v papkata
	fd = open(Argv[q], O_RDONLY);
	int accessed = access(Argv[q],R_OK);
	if (fd == -1)
	{
		perror(Argv[q]);
		return 1;
	}
	else if (accessed == -1)
		perror(Argv[q]);
	int eof = 0;
	while(!eof) 
	{
		int status_read = read(fd, buff, 1);
		//printf("%d ",status_read);
		if (status_read == -1) 
		{
			if(errno == EINTR) {
				status_read = 0;
			}
			else {
				perror(Argv[q]);
				return 1;
			}
		}
		else if (status_read == 0){
			eof = 1;
			break;
		}
		if (buff[0] == '\n')
		{
			state = 1;
			wc_temp[0]++;
		}else if (buff[0] == ' ' || buff[0] == '\t' || i==0)
		{
			state = 1;
		}else
		{
			if (state == 1)
			{
				wc_temp[1]++;
			}
			state=0;
		}
		//printf("%s",buff);
		i++;
		a+=status_read;
	}
	i=0;
	if (buff == "\0") // If the file is empty
	{
		printf ("\t0\t0\t0\t%s\n", Argv[q]);
		int close_status = close(fd);
		if (close_status == -1)
		{
			perror(Argv[q]);
			return 1;
		}
		return 0;
	}
	wc_temp[2]=a;
	wc[2]= wc[2]  + a;
	printf ("\t%d\t%d\t%d\t%s\n", wc_temp[0], wc_temp[1], wc_temp[2], Argv[q]);
	wc[0] = wc[0]  + wc_temp[0];
	wc[1] = wc[1]  + wc_temp[1];
	wc_temp[0]=0;
	wc_temp[1]=0;
	int close_status = close(fd);
	if (close_status == -1)
	{
		perror(Argv[q]);
		return 1;
	}
	return 0;
}


/*
exe: \
compile
	./wc
compile: \
wc.c
	c99 wc.c
text:
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
*/
