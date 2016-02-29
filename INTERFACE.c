/* Command interface with the commands required for this project */

#include "INTERFACE.h"


/*Constant definitions*/
#define COMMAND_MAX_SIZE 20


/* The databases for checks and clients are global variables */
Queue checkQ;
AVLlink clientAVL;



/*MAIN*/

int main(int argc, char* argv[]){

	/* initializing some useful variables */
	char *completeCommand  = NULL, *command = xmalloc(COMMAND_MAX_SIZE + 1);

	checkQ = initQueue();
	clientAVL = initAVL();

	/* Number of arguments should be one */
	if (argc != 1) { 
		fprintf(stderr, "Erro no numero de argumentos da main.\n");
		exit(1);
	}

	/* command interface */
	while(1){
		completeCommand = getLine(completeCommand);

		if (sscanf(completeCommand, "%15s", command) != 1 && strcmp(completeCommand, "\n")){
			fprintf(stderr, "error in scanf command interface.\n");
			exit(2);
		}
 	

		if (strcmp("cheque", command) == 0) doCheck(completeCommand);

		else if (strcmp("processa", command) == 0) doProcess();

		else if (strcmp("processaR", command) == 0) doProcessR(completeCommand);

		else if (strcmp("infocheque", command) == 0) doInfoCheck(completeCommand);

		else if (strcmp("infocliente", command) == 0) doInfoClient(completeCommand);

		else if (strcmp("info", command) == 0) doInfo();

		else if (strcmp("sair", command) == 0){ doExit(completeCommand, command); return 0;}

		else printf("Invalid command. Please type again.\n");

	}

	printf("Error with scanf in main - stoping execution.\n");
	exit(2);
}


/**
 * Issues a new check to the database of checks yet to be processed.
 */
 void doCheck(char* command){
 	int val;
 	long int refe, refb, refc;
 	CheckP check;
 	ClientP ce, cb;

 	/* get the check info from the user command */
 	if(sscanf(command, "%*s %d %ld %ld %ld", &val, &refe, &refb, &refc) == 4){
 		
 		check = newCheck(refc, val, refe, refb); 
 		addQueue(check, checkQ); /* adding the check to the queue */
 		/* Create a new client, if it is  a new one and save that info in flag */
 		if ((ce = (ClientP) getItemAVL(clientAVL, &refe, lessClient, Key_Client)) == NULL){
 			ce = newClient(refe);
 			clientAVL = insertAVL(clientAVL, ce, lessClient, Key_Client);
		}	

 		/* Create a new client if that is the case and save that info in a flag */
 		if ((cb = (ClientP) getItemAVL(clientAVL, &refb, lessClient, Key_Client)) == NULL){
 			cb = newClient(refb);
 			clientAVL = insertAVL(clientAVL, cb, lessClient, Key_Client);
 		}

 		/* Update the clients' info, with this new check's value */
 			updateClient(ce, cb, val, 1);

		return;
 	}

 	/* if there was some error reading input, return message */
 	printf("Invalid command. Please type again.\n");
 }



/*Functions*/

/**
 * Processes the oldest check in the database of checks and removes 
 * it from the database.
 * If the database is empty prints that information to the user.
 */
 void doProcess(){
 	CheckP check;
 	ClientP ce, cb;
 	/* remove the oldest check from the database */
 	check = (CheckP) getFirstQueue(checkQ); 

 	/* return if the database is empty, printing a warning message */
 	if (check == NULL){ puts("Nothing to process"); return;}
 	/* find the clients associated with the check */
 	ce = (ClientP) getItemAVL(clientAVL, &getCheckREFissue(check), lessClient, Key_Client);
	cb = (ClientP) getItemAVL(clientAVL, &getCheckREFreceive(check), lessClient, Key_Client);

 	/* update the clients' info */
 	updateClient(ce, cb, getCheckVAL(check), 0);

 	freeCheck(check);
 }


/**
 * Processes the check of reference refc and removes it from the database.
 * If it doesn't exist prints out that information to the user.
 */
 void doProcessR(char* command){
 	long int ref;
 	CheckP check;
 	ClientP ce, cb;

 	/* get the check's reference from the user command */
 	if (sscanf(command, "%*s %ld", &ref) != 1){ 
 		puts("Invalid command. Please type again.");
 		return;
 	}

 	/* remove the check from the database, if we find it */
 	check = (CheckP) getSpecificQueue(checkQ, &ref, compareQueueCheck, 1); 

 	/* return if we didn't find the check, printing a warning message */
 	if (check == NULL){ printf("Cheque %ld does not exist\n", ref); return;}

 	/* find the clients associated with the check */
 	ce = (ClientP) getItemAVL(clientAVL, &getCheckREFissue(check), lessClient, Key_Client);

	cb = (ClientP) getItemAVL(clientAVL, &getCheckREFreceive(check), lessClient, Key_Client);

 	/* update the clients' info */
 	updateClient(ce, cb, getCheckVAL(check), 0);

 	freeCheck(check);
 }


/**
 * Looks up the check with reference ref and prints out it's info
 */
 void doInfoCheck(char* command){
 	long int ref;
 	CheckP check;

 	/* get the check's reference from the user command */
 	if (sscanf(command, "%*s %ld", &ref) != 1){ 
 		/*puts("Invalid command. Please type again.");*/
 		return;
 	}

 	/* get the check from the database, if we find it */
 	check = (CheckP) getSpecificQueue(checkQ, &ref, compareQueueCheck, 0); 

 	/* return if we didn't find the check, printing a warning message */
 	if (check == NULL){ printf("Cheque %ld does not exist\n", ref); return;}

 	printCheck(check);
 }


/**
 * Looks up for the client with reference ref and prints out it's info.
 */
 void doInfoClient(char* command){
 	long int ref;
 	ClientP client;

 	/* get the check's reference from the user command */
 	if (sscanf(command, "%*s %ld", &ref) != 1){ 
 		puts("Invalid command. Please type again.");
 		return;
 }

 	/* get the client from the database, if we find it */
 	client = (ClientP) getItemAVL(clientAVL, &ref, lessClient, Key_Client); 

 	/* return if we didn't find the check, printing a warning message */
 	if (client == NULL){ 
 		printf("Cliente %ld does not exist\n", ref);
 		return;
 	}
 	printf("Cliente-info: ");
 	printClient(client);
 }


/**
 * Prints out the information of all the active clients with reference in 
 * ascending order.
 */
 void doInfo(){
 	if (emptyAVL(clientAVL)){ puts("No active clients"); return;}
 	IOtraverseAVL(clientAVL, printClientInfo);
 }


/**
 * Deletes everything, including the queue of checks and the AVL of clients.
 * It also calculates and prints some generic info. Concretely, it prints 
 * the number of clients (ncl) that were present in the database and the number 
 * of checks (nch) and the total amount they add up to (vhc).
 */
void doExit(char* completeCommand, char* command){
 	long int ncl, nch_vch[2];

 	/* Compute the number of clients in the AVL of clients */
 	ncl = (long int) countAVL(clientAVL);

 	/* Clear the AVL (freeing all the memory allocated) */
 	clearAVL(clientAVL, deleteClient);

 	/* Computes the nch and the vch and clears the queue of checks */
 	count_clearQueueCheck(checkQ, nch_vch);

 	/*frees the command and completeCommand strings*/
 	free(completeCommand);
 	free(command);

 	/* prints the generic info */
 	printf("%ld %ld %ld\n", ncl, nch_vch[0], nch_vch[1]);

}


/**
 * Updates the: - issuing client's nche and vche - if reference is given;
 *              - receiving client's nchb and vchb - if reference given.
 * Takes as input: 
 *     - the issuing client (0 if it is not to be updated);
 *     - the receiveing client (0 if it is not to be updated);
 *     - an int, 1 indicates that a check was added and 0 that it was removed 
 *          from the client's portfolio.
 * If any of the clients cease to be active (when mode is 0), it also 
 * removes the client from the clients' database.
 */
 void updateClient(ClientP ce, ClientP cb, int val, int mode){

 	/* if mode is 1 add, if it is 0 subtract val */
 	changeClientIssued(ce, mode? val : -val);

 	/* remove the client if it is no longer active */
 	if (!getClientNCHE(ce) && !getClientNCHB(ce))
		clientAVL = deleteAVL(clientAVL, &getClientREF(ce), lessClient, Key_Client, deleteClient);
 	
 	/* if mode is 1 add, if it is 0 subtract val */
 	changeClientReceived(cb, mode? val : -val);

 	/* remove the client if it is no longer active */
 	if ((getClientNCHE(cb) == 0) && (getClientNCHB(cb) == 0))
 		clientAVL = deleteAVL(clientAVL, &getClientREF(cb), lessClient, Key_Client, deleteClient);
 }
