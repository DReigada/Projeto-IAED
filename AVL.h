/*File that implements an AVL Tree*/
#ifndef _AVL_H_
#define _AVL_H_

#include "Xmalloc.h"


/*Structure*/

/**
 * Defines the type avlNode, where AVLlink is the pointer to the structure
 * The type contains:
 * 			- a pointer to the item of the node;
 *			- the pointer to the left and right nodes;
 */
typedef struct avlNode{
	void *item;
	struct avlNode *l, *r;
	int height;
}*AVLlink;



/*Macros*/

/**
 * Returns an empty AVL Tree.
*/
#define initAVL() NULL


/**
 * Checks if the tree is empty.
 * Takes an AVLlink as input.
 * Returns 1 if the Tree is empty (can be used with sub trees), 0 if not.
 */
#define emptyAVL(A) (!(A))


/*Functions*/

/**
 * Creates a new node for the AVL Tree.
 * Takes as inputs:
 * 		- A generic pointer to an item;
 * 		- The link to the left and right sons.
 * Returns the AVLlink to the node.
 */
AVLlink newNodeAVL(void *item, AVLlink l, AVLlink r);


/**
 * Inserts a new element to the AVL Tree.
 * This element will be insert respecting the rules of AVL Trees.
 * The inputs are:
 *		- the AVLlink of the tree;
 *		- a generic pointer to the item to be inserted;
 *		- a function to compare the keys from items;
 *		- a function that returns a generic pointer to the key of an item.
 * Returns the new head of the Tree.
 */
AVLlink insertAVL(AVLlink h, void *item, int (*less)(void*, void*), void* (*Key_item)(void*));


/**
 * Removes the element in a Tree which key matches the given key.
 * The element is removed respecting the rules of AVL Trees.
 * The inputs are:
 *		- the AVLlink of the tree;
 *		- a generic pointer to the key to find;
 *		- a function to compare the keys from items;
 *		- a function that returns a generic pointer to the key of an item;
 *		- a function that frees the item.
 * Returns the new head of the Tree.
 */
AVLlink deleteAVL(AVLlink h, void *key, int (*less)(void*, void*), void* (*Key_item)(void*), void (*deleteItem)(void*));


/**
 * Searches the element in a Tree which key matches the given key.
 * The inputs are:
 *		- the AVLlink of the tree;
 *		- a generic pointer to the key to find;
 *		- a function to compare the keys from items;
 *		- a function that returns a generic pointer to the key of an item;
 * Returns a generic pointer to the item. NULL if no matching item is found.
 */
void* getItemAVL(AVLlink h, void *key, int (*less)(void*, void*), void* (*Key_item)(void*));


/**
 * Traverses the Tree and "visits" the Item according to the given function.
 * Takes as inputs a Tree and a function that takes a generic pointer to an item.
 */
void IOtraverseAVL(AVLlink h, void (*visit)(void*));


/**
 * Returns the link to the node with item that has the higher key value.
 */
AVLlink max(AVLlink h) ;


/**
 * Returns the link to the node with item that has the lower key value.
 */
AVLlink min(AVLlink h) ;


/**
 * Returns the height of a node.
 */
int height(AVLlink h);


/**
 * Rotates a node to the right.
 * Returns the new root of the Tree.
 */
AVLlink rotR(AVLlink h) ;


/**
 * Rotates a node to the left.
 * Returns the new root of the Tree.
 */
AVLlink rotL(AVLlink h) ;


/**
 * Does a Left-Right rotation to the given node.
 * Returns the new root of the Tree.
 */
AVLlink rotLR(AVLlink h);


/**
 * Does a Right-Left rotation to the given node.
 * Returns the new root of the Tree.
 */
AVLlink rotRL(AVLlink h);


/**
 * Returns the balance factor of a node.
 */
int Balance(AVLlink h);


/**
 * Balances a Tree.
 * Returns the new root of the Tree.
 */
AVLlink AVLbalance(AVLlink h) ;


/** 
 * Clears an AVL Tree and frees the memory of the items.
 * Takes as inputs a Tree and a function that frees items (takes a generic pointer to it).
 * Returns nothing.
 */
void clearAVL(AVLlink h, void (*deleteItem)(void*));


/**
 * Counts the number of nodes of a Tree.
 * Returns the number of nodes counted.
 */
int countAVL(AVLlink h);

#endif
