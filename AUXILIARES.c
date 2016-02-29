/*This file defines some auxiliary functions needed for the project*/
 #include "AUXILIARES.h"



/** 
 * Gets a line from stdin.
 * Limits the size of the line to BUFSIZ. So be aware that lines
 * with more than 512 characters might be truncated.
 * Returns the pointer to the string.
 */
char* getLine(char* line){
  int line_len;

  line = (char*) xrealloc(line, BUFSIZ);
  fgets(line, BUFSIZ - 1, stdin);
  line_len = strlen(line);
  line = (char*) xrealloc(line, line_len + 1);

  return line;
}



/*Queue auxiliary functions*/

/**
 * CompareQueue is the compare function we use to compare two items of the queue.
 * This function depends on the item being used, so it should be defined accordingly 
 * It takes as inputs two generic pointers.
 * In this case, the items are of type CheckP and so we compare them by reference,
 * as specified in the CheckP type.
 * It returns 1 if equal or 0 if not.
 */
int compareQueueCheck(void* ref, void* check){ 
  return (*((long int*) ref) == getCheckREF(((CheckP) check)));
}
 
/**
 * Input: - queue of checks; - vector of two ints to return some info
 * Cycles through the queue of checks and deletes it (frees all the memory).
 * While doing that it counts the number of checks in the queue (nch) and 
 * the total amount they add up to (vch) and stores them in the vector given, 
 * respectively.
 */
void count_clearQueueCheck(Queue q, long int vec[2]){
  int nch = 0, vch = 0;
  CheckP check;

/**
  * Gets and deletes all the nodes (checks) of the queue one at a time, while 
  * getting their information (to update the nch and vch) and freeing the 
  * memory allocated for them.
  */
  while(!emptyQueue(q)){
    check = (CheckP) getFirstQueue(q);

    nch++;
    vch += getCheckVAL(check);

    freeCheck(check);
  }

  /*free the Q*/
  freeQ(q);
  /* storing the nch and vch in the vector */
  vec[0] = nch;
  vec[1] = vch;
}

/* Prints the check info */
void printCheck(CheckP c){
  printf("Cheque-info: %ld %d %ld --> %ld\n",
                getCheckREF(c), getCheckVAL(c),
                getCheckREFissue(c),
                getCheckREFreceive(c));
}


/*AVL auxiliary functions*/


/**
 * lessClient is used in the AVL tree for finding or inserting an item
 * comparing the keys (references in this case).
 * It takes as inputs the generic pointers for the keys.
 * Returns 1 if ref1 is less than ref2 or 0 if not.
 */
int lessClient(void* ref1, void* ref2){
  return *((long int*) ref1) < *((long int*) ref2);
}


/**
 * Key_Client is used in the AVL tree for accessing the keys of items.
 * It takes the generic pointer to a client.
 * Returns the pointer to the key.
 */
void* Key_Client(void* client){
  return &(getClientREF((ClientP) client));
}


/**
 * deleteClient frees de memory from a client.
 * Takes as input a generic pointer to a client.
 */
void deleteClient(void* c){
  freeClient((ClientP) c);
}


/*Prints the Client info*/
void printClient(ClientP c){
  printf("%ld %d %ld %d %ld\n", getClientREF(c), getClientNCHE(c),\
                                getClientVCHE(c), getClientNCHB(c),\
                                getClientVCHB(c));
}

/*Prints the Client info according to the specifications*/
void printClientInfo(void* c){
  printf("*");
  printClient((ClientP) c);
}
