/* File that defines a type CHECK*/
#include "CHECK.h"


/**
 * Creates a new check with the reference ID, value value, the issuing client's ID
 * and the receiving client's ID
 */
 CheckP newCheck(long int ID, int val, long int iID, long int rID){
    CheckP c = (CheckP) xmalloc(sizeof(struct check)); /* allocating the necessary memory */

    /* assigning the corresponding values of the input to the new check fields */
    c->ref = ID;
    c->value = val;
    c->issueID = iID;
    c->receiveID = rID; 

    return c;
 }
