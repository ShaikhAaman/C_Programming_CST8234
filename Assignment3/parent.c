#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> // library for fcntl function 
#include  <sys/types.h>
#include  <signal.h>
#include "parent.h"


// called when user does not choose the number for timeOut/2 seconds
void SIGUSR2_handler(int sig)
{
	printf("\nAre you still there? Time is running out!\n");
}

// called when user does not choose the number for timeOut seconds
void SIGUSR1_handler(int sig)
{
	printf("\nSorry, you ran out of time!\n");
	exit(0);
}

// parent function
void main_parent(int p2c[], int c2p[], int timeOut, int maxNum)
{
	int num = -1;

	// setting SIGUSR1 signal handler
	if (signal(SIGUSR1, SIGUSR1_handler) == SIG_ERR)
	{
		printf("SIGUSR1 install error\n");
		return;
    }

    // setting SIGUSR2 signal handler
	if (signal(SIGUSR2, SIGUSR2_handler) == SIG_ERR) 
	{
		printf("SIGUSR2 install error\n");
		return;
	}

	// stores the response send by child
	int response;

	// closing the read end of pipe from (parent to child)
	close(p2c[0]);
	// closing the write end of pipe from (child to parent)
	close(c2p[1]);

	while(1){
		printf("\nEnter a number between 0 - %d (You have %d seconds to make a guess):", maxNum-1, timeOut);
		scanf("%d",&num);
		while(num > (maxNum-1) || num < 0)
		{
			printf("out of range... Enter between 0 - %d: ", (maxNum-1));
			scanf("%d", &num);
			while(num>(maxNum-1) || num<0)
			{
				printf("Incorrect value... enter between 0 - %d: ", maxNum-1);
				scanf("%d", &num);
			}
		}
		// writing number chosen by user to pipe
		write(p2c[1], &num, sizeof(num));

		// reading response sent from child
		read(c2p[0], &response, sizeof(response));

		if(response == 0){	// if number chosen is correct
			printf("Congratulations, You guessed the number (%d) correctly\n", num);
			//cleaning pipes
			close(p2c[1]);
			close(c2p[0]);
			return;
		}
		else if(response == -1){ // if number chosen is low
			printf("Your guess was too low\n");
		}else if(response == 1){ // if number chosen is high
			printf("Your guess was too high\n");
		}
	}
}