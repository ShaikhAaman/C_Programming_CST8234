/*
Name: Mohammedaaman Shaikh and Soham chaudhary
id: shai0043@algonquinlive.com and chau0161@algonquinlive.com
Purpose: make a program to read files and seperate it accordingly i.e. number of words and repetation
Section : CST8234 C language
Assignment 1
 */

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

int wordlen;
int i; /*used for for loop */
char * line;
int linesProcessed = 0, wordsProcessed = 0, wordsStored = 0;
char filename[20];
FILE * fp;

struct word{
	char* word_;
	int count;
	struct word *next;
};
struct word* elem;
struct word* newWord;

struct word* newword(){
	struct word* p = (struct word*)malloc(sizeof(struct word));
	p->next = NULL;
	p->count = 1;
	p->word_ = NULL;
	return p;
}
/*this method will look for words and see if its present or not in the linked list */
int ifPresent(char *line, int start, int end, struct word* linkedList){
	struct word* elem = linkedList;
	while(elem != NULL){
		int wordLen = strlen(elem->word_);
		if(end-start == wordLen){
			int i = start;
			while(i<end){
				if(line[i] == (elem->word_)[i-start] || (line[i] + 32) == (elem->word_)[i-start])  
					i++;
				else
					break;
			}
			if(i==end){
				elem->count = elem->count +  1;
				return 1;
			}
		}
		elem = elem->next;
	}
	return 0;
}
/*this method will sort the words */
void sortedInsert(struct word** head_ref, struct word* new_node)  
{  
    struct word* current;  
    if (*head_ref == NULL || strcmp((*head_ref)->word_,new_node->word_) > 0)  
    {  
        new_node->next = *head_ref;  
        *head_ref = new_node;  
    }  
    else
    {  
        current = *head_ref;  
        while (current->next!=NULL &&  
            strcmp((current->next)->word_, new_node->word_) < 0)  
        {  
            current = current->next;  
        }  
        new_node->next = current->next;  
        current->next = new_node;  
    }  
}  
/*this method will process the word and it will store the word i9n the linked list */
void processWord(char *line, int start, int end, struct word** linkedList, int *wordsStored){
	if(!ifPresent(line, start, end, *linkedList)){
		(*wordsStored) = (*wordsStored) + 1; 
		wordlen = end - start;
		newWord = newword();
		newWord->word_ = (char *)malloc(sizeof(char) * wordlen);
		
		for(i=start;i<end;i++){
			if(line[i] >= 65 && line[i] <= 90)
				newWord->word_[i-start] = (char) (line[i] + 32);
			else
				newWord->word_[i-start] = line[i];
		}
		if((*linkedList) == NULL){
			(*linkedList) = newWord;
			return;
		}
		sortedInsert(linkedList, newWord);
	}	
}

/*this method will process the line and will inwoke the procesWord method */
void processLine(char *line, struct word** linkedList, int *wordsProcessed, int *wordsStored){
	int len = (int)strlen(line);
	int start = 0;
	int i = 0;
	while(!((line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= 'a' && line[i] <= 'z'))){
		i++;
		if(i == len)
			return;
	}
	start = i;
	for(i=start+1;i<len;i++){
		if(line[i] == ' ' || line[i] == '\n' || line[i] == '\0'){
			(*wordsProcessed) = (*wordsProcessed) + 1;
			processWord(line, start, i, linkedList, wordsStored);
			while(!((line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= 'a' && line[i] <= 'z'))){
				i++;
				if(i == len)
					return;
			}
			start = i;
		}
	}
}
/* this method will display the menu */
void displayMenu(){
	printf("\n\n");
	printf("1. Display Statistics :\n");
	printf("2. List all the words in ascending sorted order :\n");
	printf("3. List all the words greater than a certain length :\n");
	printf("4. List all the words less than a certain length :\n");
	printf("5. List all the words equal to a certain length :\n");
	printf("6. Write all the words found to a file :\n");
	printf("9. Exit :\n");
}
/*this method will process the file in addition this method will allocate memory using malloc
and this method will inwoke the processline method */
void processFile(char *filename, struct word **linkedList){
	FILE * fp;
	fp = fopen(filename, "r");
	if(fp == NULL){
		printf("File %s not found. Terminating\n", filename);
		return;
	}

	line = (char *)malloc(sizeof(char) *  255);
	
	while (fgets(line, 255, fp)) {
        processLine(line, linkedList, &wordsProcessed, &wordsStored);
        linesProcessed++;
    }
    printf("Lines Processed : %d\n", linesProcessed);
    printf("Words Processed : %d\n", wordsProcessed);
    printf("   Words Stored : %d\n", wordsStored);
    fclose(fp);
}
/*this method will be used to print a line which has a word and howmany time it found */
void printWord(struct word* word){
	printf("word = %s & count = %d\n", word->word_, word->count);
}
/*this method will basically print the whole linked list in which all the words are saved */
void printLinkedlist(struct word* linkedList){
	printf("Displaying all words:\n");
	elem = linkedList;
	while(elem != NULL){
		printWord(elem);
		elem = elem->next;
	}
	return;
}

/*this method will display the statistics */
void displayStatistics(struct word *linkedList){
	printLinkedlist(linkedList);
}
/*this method is used to display the words greater than the length of enterd number(user will enter th number) */
void displayGreaterThanLength(struct word *linkedList, int minLength){
	printf("Displaying words greater than length: %d\n", minLength);
	elem = linkedList;
	while(elem != NULL){
		if(strlen(elem->word_) >(unsigned) minLength)
			printWord(elem);
		elem = elem->next;
	}
	return;
}
/*this method is used to display the words less than the length of enterd number(user will enter th number) */
void displayLessThanLength(struct word *linkedList, int maxLength){
	printf("Displaying words less than length: %d\n", maxLength);
	elem = linkedList;
	while(elem != NULL){
		if(strlen(elem->word_) < (unsigned)maxLength)
			printWord(elem);
		elem = elem->next;
	}
	return;
}
/*this method is used to display the words equal to the length enterd number(user will enter th number) */
void displayEqualToLength(struct word *linkedList, int Length){
	printf("Displaying words equal to length: %d\n", Length);
	elem = linkedList;
	while(elem != NULL){
		if(strlen(elem->word_) == (unsigned) Length)
			printWord(elem);
		elem = elem->next;
	}
	return;
}
/*this method is used to write down all the words found from the enterd file so this 
method will creat a new file with all the saved words in addition this method will ask user
to give the name of the file */
void writeToFile(struct word* linkedList){
	printf("Enter output file name:");
	
	scanf("%s", filename);
	
	fp = fopen(filename, "w");
	elem = linkedList;
	while(elem != NULL){
		fprintf(fp, "%s\n", elem->word_);
		elem = elem->next;
	}
	fclose(fp);
}
/*the main method */
int main(int argc, char **argv)
{
	struct word *linkedList = NULL;
    int exitFlag = 0;
	int choice;
    char *filename = (char *)malloc(sizeof(char) * 20);
    int minLength, maxLength, Length;
    while(1){
    	displayMenu();
    	
    	printf("\nEnter Your Choice:");
    	scanf("%d", &choice);
    	switch(choice){
    		case 1:
    			printf("Input Filename:");
    			printf(" %s", argv[1]);
			filename = argv[1];
    			processFile(filename, &linkedList);
       			break;
    		case 2:
    			displayStatistics(linkedList);
    			break;
    		case 3:
    			printf("Enter the minimum word length:");
    			scanf("%d", &minLength);
    			displayGreaterThanLength(linkedList, minLength);
    			break;
    		case 4:
    			printf("Enter the maximum word length:");
    			scanf("%d", &maxLength);
    			displayLessThanLength(linkedList, maxLength);
    			break;
    		case 5:
    			printf("Enter the  word length:");
    			scanf("%d", &Length);
    			displayEqualToLength(linkedList, Length);
    			break;
    		case 6:
    			writeToFile(linkedList);
    			break;
    		case 9:
    			printf("Goodbye\n");
    			exitFlag = 1;
    			break;
    		default:
    			printf("Invalid Input\n");
    	}
    	if(exitFlag == 1)
    		break;
    }
	return 0;
}
