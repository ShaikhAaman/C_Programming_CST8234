#include<stdlib.h>
#include<stdio.h>
#include"node.h"
#include"rental.h"

//create a new node
Node* generateNode()
{
	Node *pNewNode = malloc(sizeof(Node));
	pNewNode->pProperty = makeProperty();
	return pNewNode;
}

//count the number of nodes
int getCount(Node *pHead)
{
	int count = 0;
	while (pHead != NULL)
	{
		pHead = pHead->next;
		count++;
	}
	return count;
}

//get the node at the given index
Node *getNodeAtIndex(Node *pHead, int i)
{
	Node* tempNode = pHead;
	for(int count = 0; (tempNode!=NULL); count++)
	{
		if(count == i)
			break;
		if(tempNode != NULL)
			tempNode = tempNode->next;
	}
	return tempNode;
}

//adds the node to the end of the list
void appendNode(Node **ppHead, Node *pNewNode)
{
	Node *temp = *ppHead;
	if (temp == NULL)
	{
		*ppHead = pNewNode;
	}
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = pNewNode;
	}
	pNewNode->next = NULL;
}

//insert node to the list
void insertNode(Node **ppHead, Node *pNewHead, int i)
{
		Node *temp = *ppHead;
	
	if (temp == NULL)
	{
		*ppHead = pNewHead;
	}
	else if (i == 0)
	{
		pNewHead->next = *ppHead;
		*ppHead = pNewHead;
	}
	else
	{	int count = 0;
		while (temp->next != NULL)
		{
			if (count == i - 1)
			{
				break;
			}
			temp = temp->next;
			count++;
		}
		pNewHead->next = temp->next;
		temp->next = pNewHead;
	}
}

//removes the node at the given index
Node *removeNodeAtIndex(Node **ppHead, int i)
{
	Node* removedNode = getNodeAtIndex(*ppHead, i);
	if(removedNode != NULL)
	{
		if(getCount(*ppHead) > 0)
		{
			if(i > 0)
			{
				Node* prevNode = getNodeAtIndex(*ppHead, i-1);
				prevNode->next = removedNode->next;
				removedNode->next = NULL;
			}
			else 
			{
				*ppHead = removedNode->next;
				removedNode->next = NULL;
			}
		}
	}
	return removedNode;
}
