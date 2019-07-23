#ifndef SORT_H_
#define SORT_H_

int sortByRent(property* propertyOne, property* propertyTwo);
int sortByDistance(property* propertyOne, property* propertyTwo);
int sortByAddress(property* propertyOne, property* propertyTwo);
int sortByRooms(property* propertyOne, property* propertyTwo);
void swap(Node *propertyOne, Node *propertyTwo);
void sort(Node *pHead, int(*pComparator)(property *a, property *b));


#endif