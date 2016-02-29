/*File that implements an AVL Tree*/
#include "AVL.h"


/**
 * Creates a new node for the AVL Tree.
 * Takes as inputs:
 * 		- A generic pointer to an item;
 * 		- The link to the left and right sons.
 * Returns the AVLlink to the node.
 */
AVLlink newNodeAVL(void *item, AVLlink l, AVLlink r){
	AVLlink x = (AVLlink) xmalloc(sizeof(struct avlNode));
	x->item = item;
	x->l = l;
	x->r = r;
	x->height = 0;
	return x;
}


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
AVLlink insertAVL(AVLlink h, void *item, int (*less)(void*, void*), void* (*Key_item)(void*) ){
	if (h == NULL)
		return newNodeAVL(item, NULL, NULL);
	if (less(Key_item(item), Key_item(h->item)))
		h->l = insertAVL(h->l, item, less, Key_item);
	else 
		h->r = insertAVL(h->r, item, less, Key_item);
	h=AVLbalance(h);
	return h;
}


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
AVLlink deleteAVL(AVLlink h, void *key, int (*less)(void*, void*), void* (*Key_item)(void*), void (*deleteItem)(void*)){/*lessequal tem de ser definido*/
	if (h==NULL) return h;
	else if (less(key, Key_item(h->item))) h->l=deleteAVL(h->l, key, less, Key_item, deleteItem);
	else if (less(Key_item(h->item),key)) h->r=deleteAVL(h->r, key, less, Key_item, deleteItem);
	else{
		if (h->l !=NULL && h->r !=NULL){
			AVLlink aux=max(h->l);
			{void* x; x=h->item; h->item=aux->item; aux->item=x;}
			h->l= deleteAVL(h->l, Key_item(aux->item), less, Key_item, deleteItem);
		}
		else{
			AVLlink aux=h;
			if (h->l == NULL && h->r == NULL) h=NULL;
			else if (h->l==NULL) h=h->r;
			else h=h->l;
			deleteItem(aux->item);
			free(aux);
		}
	}
	h=AVLbalance(h);
	return h;
}


/**
 * Searches the element in a Tree which key matches the given key.
 * The inputs are:
 *		- the AVLlink of the tree;
 *		- a generic pointer to the key to find;
 *		- a function to compare the keys from items;
 *		- a function that returns a generic pointer to the key of an item;
 * Returns a generic pointer to the item. NULL if no matching item is found.
 */
void* getItemAVL(AVLlink h, void *key, int (*less)(void*, void*), void* (*Key_item)(void*)){
	if (h==NULL) return NULL;
	if (less(key, Key_item(h->item))) return getItemAVL(h->l, key, less, Key_item);
	else if (less(Key_item(h->item), key)) return getItemAVL(h->r, key, less, Key_item);
	return h->item; /*se nao é maior ou menor e o que queremos*/
}


/**
 * Traverses the Tree and "visits" the Item according to the given function.
 * Takes as inputs a Tree and a function that takes a generic pointer to an item.
 */
void IOtraverseAVL(AVLlink h, void (*visit)(void*)){
	if (h == NULL) return;
	IOtraverseAVL(h->l, visit);
	visit(h->item);
	IOtraverseAVL(h->r, visit);
}


/**
 * Returns the link to the node with item that has the higher key value.
 */
AVLlink max(AVLlink h) {
	if (h==NULL || h->r==NULL) return h;
	else return max(h->r);
}


/**
 * Returns the link to the node with item that has the lower key value.
 */
AVLlink min(AVLlink h) {
	if (h==NULL || h->l==NULL) return h;
	else return min(h->l);
}

	
/**
 * Returns the height of a node. -1 = height of empty AVL Tree.
 */	
int height(AVLlink h){
	if (!h) return -1;
	return h->height;
}


/**
 * Rotates a node to the right.
 * Returns the new root of the Tree.
 */
AVLlink rotR(AVLlink h) {
	int height_left, height_right;
	AVLlink x = h->l;
	h->l = x->r;
	x->r = h;

	height_left = height(h->l); height_right = height(h->r);
	h->height = height_left > height_right ? height_left + 1 : height_right + 1;
	height_left = height(x->l); height_right = height(x->r);
	x->height = height_left > height_right ? height_left + 1 : height_right + 1;
	return x; 
}


/**
 * Rotates a node to the left.
 * Returns the new root of the Tree.
 */
AVLlink rotL(AVLlink h) {
	int height_left, height_right;
	AVLlink x = h->r;
	h->r = x->l;
	x->l = h;	

	height_left = height(h->l); height_right = height(h->r);
	h->height = height_left > height_right ? height_left + 1 : height_right + 1;
	 height_left = height(x->l); height_right = height(x->r);
	 x->height = height_left > height_right ? height_left + 1 : height_right + 1;
	return x;
}


/**
 * Does a Left-Right rotation to the given node.
 * Returns the new root of the Tree.
 */
AVLlink rotLR(AVLlink h){ /*rotação dupla esquerda direita*/
	if (h==NULL) return h;
	h->l = rotL(h->l);
	return rotR(h);
}


/**
 * Does a Right-Left rotation to the given node.
 * Returns the new root of the Tree.
 */
AVLlink rotRL(AVLlink h){ /*rotação dupla direita esquerda*/
	if (h==NULL) return h;
	h->r = rotR(h->r);
	return rotL(h);
}


/**
 * Returns the balance factor of a node.
 */
int Balance(AVLlink h) {/*Balance factor*/
	if(h == NULL) return 0;
	return height(h->l)-height(h->r);
}


/**
 * Balances a Tree.
 * Returns the new root of the Tree.
 */
AVLlink AVLbalance(AVLlink h) {
	int balanceFactor;
	int height_left, height_right;
	if (h==NULL) return h;
	balanceFactor = Balance(h);

	if(balanceFactor>1){
		if (Balance(h->l)>0) h=rotR(h);
		else h=rotLR(h);

	}
	else if(balanceFactor<-1){
		if (Balance(h->r)<0) h = rotL(h);
		else h = rotRL(h);
	}
	else{
		height_left = height(h->l); 
		height_right = height(h->r);
		h->height = height_left > height_right ? height_left + 1 : height_right + 1;
	}
	return h;
}


/** 
 * Clears an AVL Tree and frees the memory of the items.
 * Takes as inputs a Tree and a function that frees items (takes a generic pointer to it).
 * Returns nothing.
 */
void clearAVL(AVLlink h, void (*deleteItem)(void*)){
	if (h == NULL) return;
	clearAVL(h->l, deleteItem);
	clearAVL(h->r, deleteItem);
	deleteItem(h->item);
	free(h);
}


/**
 * Counts the number of nodes of a Tree.
 * Returns the number of nodes counted.
 */
int countAVL(AVLlink h) {
	if (h==NULL) return 0;
	else return countAVL(h->r) + countAVL(h->l) + 1;
}
