#ifndef _NODE_H
#define _NODE_H
typedef struct Property{
	int streetNumber;
	char* streetName;
	int numRooms;
	int rent;
	float distance;
}property;

typedef struct Node{
	property *pProperty;
	struct Node *next;
}Node ;

Node* generateNode();
int getCount(Node *pHead);
Node *getNodeAtIndex(Node *pHead, int i);
void appendNode(Node **ppHead, Node *pNewNode);
void insertNode(Node **ppHead, Node *pNewHead, int i);
Node *removeNodeAtIndex(Node **ppHead, int i);

#endif