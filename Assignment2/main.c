/*
PROGRAM: Assignment1 - CST8234_012
AUTHOR: Ali Saad Jaffer, Mohammedaaman Shaikh
DATE: Mar 11,2019
PURPOSE: Create linked list and make a tinder like application for rental properties
LEVEL OF DIFFICULTY: 5/5
CHALLENGES: deleting nodes, managing the list, sorting.
HOURS SPENT: 2 Weeks
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "node.h"
#include "rental.h"
#include "sort.h"



int main()
{	srand(time(NULL)); 
	char choice[2];    //string for user input
	Node *presentList[] = { NULL, NULL };  

	int index = 0;

	int nextProperty = 0; 
	int(*pComparator)(property *a, property *b) = NULL; 

	// generating 6 random property 
	for (int i = 0; i < 6; i++)
	{
		Node *newNode = generateNode();         
		appendNode(&presentList[index], newNode);   //node added to the undecided list
	}
		printProperties(presentList[index], index);          // printing the undecided list
		showUser(getNodeAtIndex(presentList[index], nextProperty)); 


	do
	{
		printf("\nCommand ('h' for help): ");
		scanf("%s", choice);

		if (strcmp(choice, "h") == 0)  //generate printHelp method to view all valid commands
		{
			printHelp();
		}
		else if (strcmp(choice, "a") == 0)  //show all rental properties on the current list
		{
			printAll(presentList, index, nextProperty);
		}
		
		else if (strcmp(choice, "l") == 0)  //remove from the list
		{
			if (presentList[index] != NULL)  // check if the list is null or not
			{
				removeNodeAtIndex(&presentList[index], nextProperty);
				printf("\n\nRental property deleted\n\n");

				if (getNodeAtIndex(presentList[index], nextProperty) == NULL)
				{
					nextProperty = 0;
				}
				if (presentList[index] == NULL)
				{
					printf("\nNo more rental properties\n");
				}
			}
			else
			{
				printf("\nNo more rental properties\n");
			}
		}
		
		else if (strcmp(choice, "f") == 0)  //switch to favourite list
		{
			index = 1;            //index will be changed to 1 as 1 represents favourite list
			nextProperty = 0;
			printAll(presentList, index, nextProperty);
		}
		else if (strcmp(choice, "u") == 0)  //50% generate a new rental property
		{
			index = 0;
			nextProperty = 0;

			if (rand() % 2 == 0)   //if value is 0, new property will be generated
			{
				Node *newNode = generateNode();
				appendNode(&presentList[index], newNode);
			}
			printAll(presentList, index, nextProperty);
		}
		
		
		else if (strcmp(choice, "n") == 0)  //skip the rental property
		{
			if (getCount(presentList[index]) - 1 > nextProperty)
			{
				printf("\n");
				nextProperty++;
			}
			else if (presentList[index] == NULL)
			{
				printf("\nThere are no rental properties ..\n");
			}
			else
			{
				printf("\nThis is the last property\n");
			}
		}
		
		else if (strcmp(choice, "r") == 0)  //move property to favourites list
		{
			if (index == 0 && presentList[index] != NULL)
			{
				appendNode(&presentList[index + 1], removeNodeAtIndex(&presentList[index], nextProperty));
				printf("\n\nRental property moved to your favourites list\n\n");
				if (getNodeAtIndex(presentList[index], nextProperty) == NULL)
				{
					nextProperty = 0;
				}

				if (presentList[index] == NULL)
				{
					printf("\nNo more rental properties\n\n");
				}
			}
			else if (presentList[index] == NULL)
			{
				printf("\nThere are no properties to move to favorites\n");
			}
			else
			{
				printf("\nThis rental property is already on your favourites list\n");
			}
		}
		

		else if(choice[0] == 's') //sorting the list according to user input
		{
			switch(choice[1]) 
			{
				case 'r':
					pComparator = &sortByRent;;
					break;
				case 'd':
					pComparator = &sortByDistance;
					break;
				case 'n':
					pComparator = &sortByRooms;
					break;
				case 'a':
					pComparator = &sortByAddress;
					break;
				default:
					printf("Wrong selection!!!");
			}
				if (choice[1] == 'r' || choice[1] == 'd' || choice[1] == 'n' || choice[1] == 'a')
				{
					if (presentList[index] != NULL)
					sort(presentList[index], pComparator);
					printAll(presentList, index, nextProperty);
				}
			
		}
		else if (strcmp(choice, "q") == 0)  //quit the program
		{
			break;
		}
		else
		{
			printf("That is not a supported command\n");
			printHelp();
		}

		if (presentList[index] != NULL && (strcmp(choice, "l") == 0 || strcmp(choice, "r") == 0 || strcmp(choice, "n") == 0))
		{
			if (presentList[index] != NULL)
				showUser(getNodeAtIndex(presentList[index], nextProperty));
		}

	} while (strcmp(choice, "q") != 0);  

	return 0;
}
