#ifndef NODE_H_
#define NODE_H_


property* makeProperty();
float distance(property *tempProperty);
void printProperties(Node *pHead, int choice);
void showUser(Node *pHead);
void printHelp();
void printAll(Node **presentList, int index, int nextProperty);

#endif