/* File that defines a type CHECK */
#ifndef _CHECK_
#define _CHECK_

#include "Xmalloc.h"


/*Structure*/

/**
 * Defines the type check, where checkP is the pointer to the check struct.
 * The type check contains: 
 *    - it's reference (the ID) -> ref
 *    - the value of the check -> value
 *    - the issuing client's ID -> issueID
 *    - the receiving client's ID -> receiveID
 */
typedef struct check{
  long int ref, issueID, receiveID;
  int value;
} *CheckP;



/*Macros*/

/*The next Macros take in as inputs arguments of type CheckP */

/* MACRO to free the memory allocated for a check */
#define freeCheck(A) (free(A)) 

/* MACRO to get the checks reference */
#define getCheckREF(A) ((A)->ref)

/* MACRO to get the value of the check */
#define getCheckVAL(A) ((A)->value)

/* MACRO to get the ID of the issuing client */
#define getCheckREFissue(A) ((A)->issueID)

/* MACRO to get the ID of the receiving client */
#define getCheckREFreceive(A) ((A)->receiveID)

/* MACRO to check if two checks are the same */
#define equalCheck(A, B) (getCheckREF(A) == getCheckREF(B))
 
/*Functions*/

/**
 * Iniciates a new check with the reference ID, value value, the issuing 
 * client's ID and the receiving client's ID
 */
 CheckP newCheck(long int ID, int val, long int iID, long int rID);

 #endif
