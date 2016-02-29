/* File that defines a type CLIENT */
#include "CLIENT.h"

/**
 * Iniciates a new client with the reference ID
 */
 ClientP newClient (long int ID){
 	ClientP c = (ClientP) xmalloc(sizeof(struct client)); /* allocates the  memory */

 	c->nche = 0, c->vche = 0, c->nchb = 0, c->vchb = 0; /* initializes values as 0 */
 	c->ref = ID; /* puts the ID given in the client structure */

 	return c;
 }

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
 void changeClientIssued(ClientP client, int value){
  	client->vche += value; /* makes the change in the total amount of checks issued */

  	/* check whether to increase or decrease the number of checks issued and do it */
  	client->nche += (value > 0)? 1 : -1;     
  }

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
void changeClientReceived(ClientP client, int value){
	client->vchb += value; /* makes the change in the total amount of checks to receive */

  	/* check whether to increase or decrease the number of checks to receive and do it */
  	client->nchb += (value > 0)? 1 : -1;      
  }
