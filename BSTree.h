// Binary Search Tree ADT interface ... COMP9024
// Edited and Modified by:- Anchit Verma
// Date:- January 2019

#include <stdbool.h>

typedef char *Item;      // item is just a key

typedef struct Node *Tree;

Tree newTree();        // create an empty Tree
void freeTree(Tree);   // free memory associated with Tree
void showTree(Tree);   // display a Tree (sideways)

int  TreeNumNodes(Tree);       // count #nodes in Tree
Tree TreeSearch(Tree, Item);   // check whether an item is in a Tree
Tree TreeInsert(Tree, Item, Item);   // insert a new item into a Tree
Tree TreeDelete(Tree, Item);   // delete an item from a Tree
Tree update_pagerank(Tree t, char *url, char *token); // update pagerank value of given data
void output_to_file(Tree t, FILE *f); //Output to file
void output_pagerank(Tree t, FILE *f); // output data, pagerank and count in a file
void search_engine(Tree t); // create Tree with search results

// internal functions made visible for testing
Tree rotateRight(Tree);
Tree rotateLeft(Tree);
Tree insertAtRoot(Tree, Item);
Tree partition(Tree, int);
Tree rebalance(Tree);
Tree sort(Tree t, char *url, float count, float pr);
