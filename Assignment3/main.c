/*
Program: Assignment 2
Author: Mohammedaaman Shaikh & Umang Patel
Date 17 April 2019
Purpose: make a guessing game using bi-communicational pipes and forking
Difficulty: 4/5
Challenges: Creating bi-communicational pipes and processing, handling incorrect command line arguments
Hours Spent: 10
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> // library for fcntl function 
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <ctype.h>
#include "parent.h"
#include "child.h"


int parseArguments(int argc, char* argv[], int *pmaxNum, int *ptimeOut)
{
	
// reading command line arguments
for(int i = 1; i < argc; i++)
{
	if(strcmp(argv[i],"-h")==0 || strcmp(argv[i],"--help")==0)
	{//if arguments are -h or --help then 		
		printf("\n\nUsage: ./ass2 [options]...\n\nChange the maximum number to guess from and timeout.\n");			
		printf("Will run with default maximum number = 100 (0 - 99) and timeout of 10 seconds if no argument supplied.\n");
		printf("Arguments to Posix short option and GNU long options.\n");
		printf("\t-m <integer>, --max=<integer>\t\t Change the maximum number to guess from\n");
		printf("\t-to <integer>, --timeout=<integer>\t Change the value of timeout(number of seconds to guess from) of the game\n");
		printf("\t-h, --help\t display this help and exit\n");
			
		return 0;
	}
	
	else if(strncmp(argv[i],"--max=", 6)==0 || strcmp(argv[i], "-m")==0)
	{//if arguments are --max or -m then
		char *pArgument=NULL;
		if(strcmp("-m",argv[i])==0)
			pArgument=argv[++i];
		else
			pArgument=argv[i]+6;
			
		*pmaxNum = atoi(pArgument);
		
		//storing result of sscanf in rc
		int rc = sscanf(pArgument, "%d", &(*pmaxNum));

		//checking for incorrect argument(values other than integer)
		if(rc==0)
		{
			printf("Incorrect value '%s' passed in Max... exiting program.", pArgument);
			return 0;
		}	
		//if max is less than 2 then print and exit
		if(*pmaxNum<2)
		{
			printf("Incorrect value '%s' typed in Max... exiting program.", pArgument);
			return 0;
		}	
	}
	else if(strncmp(argv[i], "--timeout=", 10)==0 || strcmp(argv[i], "-to")==0)
	{//if arguments are --timeout or -to then
		char *pArgument=NULL;
		if(strcmp(argv[i], "-to")==0)
			pArgument = argv[++i];
		else
			pArgument = argv[i] + 10;
		
		*ptimeOut = atoi(pArgument);
		
		//storing result of sscanf in rc
		int rc = sscanf(pArgument, "%d", &(*ptimeOut));
		
		//checking for incorrect argument (values other than integer)
		if(rc==0)
		{
			printf("Incorrect value '%s' passed in timeOut... exiting program.", pArgument);
			return 0;
		}	
		//if timeOut is less than 2 seconds then print and exit
		if(*ptimeOut<2)
		{
			printf("Incorrect value '%s' entered in timeOut... exiting program.", pArgument);
			return 0;
		}
	}
	else
	{//if none then
		printf("Invalid argument use -h or --help for help");
		return 0;
	}
}

	return 1;
}


int main(int argc,char* argv[]){
	
	int timeOut = 10, maxNum = 100;
	
	//check for incorrect command line arguments
	if(parseArguments(argc, argv, &maxNum, &timeOut)==0)
		return 0;	//if incorrect argument then terminate program

	int p2c[2];  // Used to store two ends of first pipe (parent to child)
    int c2p[2];  // Used to store two ends of second pipe (child to parent)

    // creating p2c
    if (pipe(p2c)==-1) 
    { 
        fprintf(stderr, "p2c Failed" ); 
        return 1; 
    } 
    // creating c2p
    if (pipe(c2p)==-1) 
    { 
        fprintf(stderr, "c2p Failed" ); 
        return 1; 
    } 
    // Non blocking read mode for p2c for child
    if (fcntl(p2c[0], F_SETFL, O_NONBLOCK) < 0) 
        exit(0);

    // creating new process
    int id = fork();
    if(id < 0)
    {
    	printf("Fork failed\n");
    	exit(0);
    }
    if(id == 0)
	{
    	// child
    	main_child(p2c, c2p, timeOut, maxNum);
    }
    else
	{
    	// parent
    	main_parent(p2c, c2p, timeOut, maxNum);
    }

	return 0;
}