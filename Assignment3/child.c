#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> // library for fcntl function 
#include <sys/types.h>
#include <signal.h>
#include <stdbool.h>
#include <time.h>
#include "child.h"

void idle_task()
{
	sleep(1);	// sleeping for 1 second
}

// send signal  to parent
bool send_signal(int counter, int timeOut)
{
	int parentid = getppid();
	if(counter == timeOut/2)
	{ // counter is half the timeOut
		// send signal to warn the user to choose the number
		kill(parentid, SIGUSR2);
		return false;
	}
	else
	{	// counter is 0
		// send signal to terminate the program as user has not selected a number in timeOut seconds
		kill(parentid, SIGUSR1);
		return true;
	}
}

// child function
void main_child(int p2c[], int c2p[], int timeOut, int maxNum)
{
	int counter = timeOut;
	int num = -1, nread;

	// generating actual number randomly
	int actualNum, response;
	srand(time(0));
	actualNum = rand()%maxNum;

	// closing the write end of pipe from (parent to child)
	close(p2c[1]);
	// closing the read end of pipe from (child to parent)
	close(c2p[0]);
	while(1){
		// non blocking read from child
		nread = read(p2c[0], &num, sizeof(num));

		// if child has read something from the pipes
		if(nread > 0)
		{
			if(num == actualNum)	// if guess is correct
				response = 0;
			else if(num > actualNum) // if guess is large
				response = 1;
			else	// if guess is small
				response = -1;

			// send response to user
			write(c2p[1], &response, sizeof(response));
			counter = timeOut;
			if(response == 0)
			{// if guess is correct then stop
				return;
			}
		}
		else
		{ // there is nothing to read from the pipe
			idle_task();	// sleep for 1 second
			counter--;	
			if(counter == timeOut/2 || counter == 0)
			{
				if(send_signal(counter, timeOut)==true)
				{
					//if time's up clean pipes
					close(p2c[0]);
					close(c2p[1]);
					return;
				}
			}
		}
	}

}