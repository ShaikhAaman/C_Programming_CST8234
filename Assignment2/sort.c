#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "rental.h"
#include "sort.h"

//sorting by rent
int sortByRent(property* propertyOne, property* propertyTwo) 
{	
	int value = propertyOne->rent - propertyTwo->rent;
	return value;
}

//sorting by distance
int sortByDistance(property* propertyOne, property* propertyTwo)
{
	int value = distance(propertyOne) - distance(propertyTwo);
	return value;
}

//sorting by address, if same then by street number
int sortByAddress(property* propertyOne, property* propertyTwo)
{
	int value = strcmp(propertyOne->streetName, propertyTwo->streetName);
	if(value == 0)
		value = propertyOne->streetNumber - propertyTwo->streetNumber;
	return value;
}

//sorting by number of rooms
int sortByRooms(property* propertyOne, property* propertyTwo)
{
	int value = propertyOne->numRooms - propertyTwo->numRooms;
	return value;
}

//swapping the nodes
void swap(Node *propertyOne, Node *propertyTwo)
{
	property *temp = propertyOne->pProperty;
	propertyOne->pProperty = propertyTwo->pProperty;
	propertyTwo->pProperty = temp;
}

//sorting the list
void sort(Node *pHead, int(*pComparator)(property *a, property *b))
{
	int i, j;
	int size = getCount(pHead);
	for (i = 0; i < size - 2; i++)
	{
		
		for (j = 0; j < size - i - 1; j++)
		{
			Node *a = getNodeAtIndex(pHead, j);
			Node *b = getNodeAtIndex(pHead, j + 1);
			if ((*pComparator)(a->pProperty, b->pProperty) > 0)
			{
				swap(a, b);
			}
		}
	}
}