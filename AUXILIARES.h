#ifndef _AUXILIARES_H_
#define _AUXILIARES_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CLIENT.h"
#include "CHECK.h"
#include "QUEUE.h"


/**
 * Function used to get a line from stdin. 
 * Input stops whan a newline character is found 
 * Takes in no inputs and returns the line read
 */		
char* getLine(char* line);



/*Queue auxiliary functions*/

/**
 * CompareQueue is the compare function we use to compare two items of the queue.
 * This function depends on the item being used, so it should be defined accordingly 
 * It takes as inputs two generic pointers.
 * In this case, the items are of type CheckP and so we compare them by reference,
 * as specified in the CheckP type.
 * It returns 1 if equal or 0 if not.
 */
int compareQueueCheck(void* ele1, void* ele2);

/**
 * Input: - queue of checks; - vector of two ints to return some info
 * Cycles through the queue of checks and deletes it (frees all the memory).
 * While doing that it counts the number of checks in the queue (nch) and 
 * the total amount they add up to (vch) and stores them in the vector given, 
 * respectively.
 */
void count_clearQueueCheck(Queue q, long int vec[2]);

/* Prints the check info */
void printCheck(CheckP c);



/*AVL auxiliary functions*/

/**
 * lessClient is used in the AVL tree for finding or inserting an item
 * comparing the keys (references in this case).
 * It takes as inputs the generic pointers for the keys.
 * Returns 1 if ref1 is less than ref2 or 0 if not.
 */

int lessClient(void* ref1, void* ref2);

/**
 * Key_Client is used in the AVL tree for accessing the keys of items.
 * It takes the generic pointer to a client.
 * Returns the pointer to the key.
 */
void* Key_Client(void*);

/**
 * deleteClient frees de memory from a client.
 * Takes as input a generic pointer to a client.
 */
void deleteClient(void* c);

/*Prints the Client info*/
void printClient(ClientP c);

/*Prints the Client info according to the specifications*/
void printClientInfo(void* c);

#endif
