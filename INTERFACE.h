#ifndef _INTERFACE_H_
#define _INTERFACE_H_

/**
 * File that defines the functions associated with the command interface
 * The valid commands are:
 *    - "cheque <valor> <refe> <refb> <refc>"
 *    - "processa"
 *	  - "porcessaR <refc>"
 *    - "infocheque <ref>"
 *    - "infocliente <ref>"
 *    - "info"
 *    - "sair"
*/

#include <stdlib.h>
#include <stdio.h>
#include "AUXILIARES.h"
#include "CHECK.h"
#include "QUEUE.h"
#include "CLIENT.h"
#include "AVL.h"



/**
 * Issues a new check to the database of checks yet to be processed.
 */
 void doCheck(char* command);


/**
 * Processes the oldest check in the database of checks and removes 
 * it from the database.
 * If the database is empty prints that information to the user.
 */
 void doProcess();


/**
 * Processes the check of reference refc and removes it from the database.
 * If it doesn't exist prints out that information to the user.
 */
 void doProcessR(char* command);


/**
 * Looks up the check with reference ref and prints out it's info
 */
 void doInfoCheck(char* command);


/**
 * Looks up for the client with reference ref and prints out it's info.
 */
 void doInfoClient(char* command);


/**
 * Prints out the information of all the active clients with reference in 
 * a ascending order.
 */
 void doInfo();


/**
 * Exits the program and deletes everything, printing dome generic info.
 */
 void doExit();


/**
 * Updates the: - issuing client's nche and vche - if reference is given;
 *              - receiving client's nchb and vchb - if reference given.
 * Takes as input: 
 *     - the issuing client's reference (0 if it is not to be updated);
 *     - the receiveing client's ref (0 if it is not to be updated);
 *     - an int, 1 indicates that a check was added and 0 that it was removed 
 *          from the client's portfolio.
 * If any of the clients cease to be active (when mode is 0), it also 
 * removes the client from the clients' database.
 */
 void updateClient(ClientP ce, ClientP cb, int val, int mode);


#endif
 