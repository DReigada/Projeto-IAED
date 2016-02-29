/* File that defines a type CLIENT */
#ifndef _CLIENT_
#define _CLIENT_

#include "Xmalloc.h"

/*Struct*/

/**
 * Defines the type client, where ClientP is the pointer to the client.
 * The type client contains: 
 *    - it's reference (the ID) -> ref
 *    - the number of checks issued by the client that are still to process 
 *      and the total amount they add up to -> nche; vche (respectively)
 *    - the number of checks to receive by the client and the total amount 
 *      they add up to -> nchb; vchb (respectively)
 */
 typedef struct client{
 	long int ref, vche, vchb;
 	int nche, nchb;
} *ClientP;
  


/*Macros*/

/* MACRO to free the memory allocated for a client */
#define freeClient(A) (free(A)) 

/* MACRO to get the client's reference */
#define getClientREF(A) ((A)->ref) 

/* MACRO to get the number of checks issued by the client */
#define getClientNCHE(A) ((A)->nche) 

/* MACRO to get the total amount in checks issued by the client */
#define getClientVCHE(A) ((A)->vche) 

/* MACRO to get the number of checks issued by the client */
#define getClientNCHB(A) ((A)->nchb) 

/* MACRO to get the total amount in checks issued by the client */
#define getClientVCHB(A) ((A)->vchb) 

/* Macro to test the inequality of two clients' ref. Returns 1 if the first
 *  client's ref is lower than the second client's and 0 otherwise.
 * The two inputs are of type references of clients 
 */
#define isLess(A, B) ((A) < (B))

/* MACRO to check if two clients are the same */
#define equalClient(A, B) (getClientREF(A) == getClientREF(B))


/*Functions*/

/**
 * Iniciates a new client with the reference ID
 */
 ClientP newClient(long int ID);

/**
  * Atualizes the number of checks issued by the client still to process (nche) 
  * and their total amount (vche). 
  * There are two input:
  *   - the pointer to the client
  *   - the change in the total amount of checks issued by the client. If the 
  *       value is negative, we decrease the number of checks and their total
  *       amount, if it is positive we increase 
  * Makes the change without returning anything
  */ 
  void changeClientIssued(ClientP client, int value);


/**
  * Atualizes the number of checks to receive by the client still to process (nchb) 
  * and their total amount (vchb). 
  * There are two input:
  *   - the pointer to the client
  *   - the change in the total amount of checks to receive by the client. If the 
  *       value is negative, we decrease the number of checks and their total
  *       amount, if it is positive we increase 
  * Makes the change without returning anything
  */ 
void changeClientReceived(ClientP client, int value);

#endif
