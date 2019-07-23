#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "node.h"
#include "rental.h"

property* makeProperty()
{
	property *tempProperty = malloc(sizeof(property));//temporary property 

	char* streetArray[]=
	{
		"Cat St.","Tiger Boul.","Ferret Ave.","Mouse Ave.","Fox St.",
	    "Coyote Crt.","Kitkat Cres.","Woodref st.","Mellow St.","Mary Ave."
	};
    
	tempProperty->streetNumber = (rand() % 200)+1;
	tempProperty->streetName = streetArray[(rand() % 10)];
	tempProperty->numRooms = (rand() % 4) + 1;
	tempProperty->rent = 50 * (rand() % (9) + 4);
	tempProperty->distance = 100 * (rand() % (21) + 1);
	return tempProperty;
}

//adding the distance to house from street
float distance(property *tempProperty){
	float distance = tempProperty->distance + (20 * tempProperty->streetNumber);
	return distance;
}

//printing properties table
void printProperties(Node *pHead, int choice){
	float km = 0;
	if(pHead!=NULL){
		if(choice == 0){
			printf("\nUndecided Rental Properties\n");
		}
		else printf("\nFavourite Rental Properties\n");
		printf("Address\t\t\t\t\t # Rooms\t Rent/Room\t \tDistance\n\n");
		printf("-----------------------\t\t\t-----------\t----------\t\t----------\n");

		while(pHead != NULL){
	
			km = distance(pHead->pProperty)/1000;
			printf("%2d %-23s\t\t%7d\t%17d\t\t%6.2f km\n",pHead->pProperty->streetNumber, pHead->pProperty->streetName, pHead->pProperty->numRooms, pHead->pProperty->rent, km);
			pHead = pHead->next; 
		}
	}else{
		printf("There are no more rental properties");
	}
}

//Asking user about the property
void showUser(Node *pHead){
	if(pHead != NULL){
		float	km = distance(pHead->pProperty)/1000;
		printf("\nWhat do you think about this rental property?\n");
		printf("\tAddr: %d %s, # Rooms: %d, Rent/Room: $%d, Distance: %.2f km\n\n", pHead->pProperty->streetNumber, pHead->pProperty->streetName, pHead->pProperty->numRooms, pHead->pProperty->rent, km);
	}else{
		printf("There are no more rental properties");		
	}
}

//help menu
void printHelp()
{
	printf("\nValid commands are:\n");
	printf("\th  - display this help\n");
	printf("\ta  - display all the rental properties on the current list\n");
	printf("\tf  - switch to the favourites list\n");
	printf("\tu  - switch to the undecided list\n");
	printf("\tl  - 'swipe left' on the current rental property\n");
	printf("\tr  - 'swipe right' on the current rental property\n");
	printf("\tn  - skip to the next rental property\n");
	printf("\tsa - set the sorting to 'by address'\n");
	printf("\tsn - set the sorting to 'by number of rooms'\n");
	printf("\tsr - set the sorting to 'by rent'\n");
	printf("\tsd - set the sorting to 'by distance'\n");
	printf("\tq  - quit the program\n\n");
}

//printing the node at the index
void printAll(Node **presentList, int index, int nextProperty)
{
	printProperties(presentList[index], index);
	if (presentList[index] != NULL)
	{
		showUser(getNodeAtIndex(presentList[index], nextProperty));
	}
	else
	{
		printf("\nNo more rental properties\n");
	}
}


