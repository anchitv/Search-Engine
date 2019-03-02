// Binary Search Tree ADT implementation ... COMP9024
// Edited and Modified by:- Anchit Verma
// Date:- January 2019

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "BSTree.h"
#include "listIteratorInt.h"

#define data(tree)  ((tree)->data)
#define left(tree)  ((tree)->left)
#define right(tree) ((tree)->right)

typedef struct Node {
   char  *data;
   float count;
   float pagerank;
   IteratorInt urls;
   Tree left, right;
} Node;


// make a new node containing data
Tree newNode(Item it) {
   Tree new = malloc(sizeof(Node));
   assert(new != NULL);
   data(new) = malloc(strlen(it)+1);
   strcpy(data(new), it);
   left(new) = right(new) = NULL;
   new->count = 1;
   new->pagerank = 0;
   new->urls = IteratorIntNew();
   return new;
}


// create a new empty Tree
Tree newTree() {
   return NULL;
}


// free memory associated with Tree
void freeTree(Tree t) {
   if (t != NULL) {
      freeTree(left(t));
      freeTree(right(t));
      free(t);
   }
}


// display Tree and its values sideways
void showTreeR(Tree t, int depth) {
   if (t != NULL) {
      showTreeR(right(t), depth+1);
      int i;
      for (i = 0; i < depth; i++)
	 putchar('\t');            // TAB character
      printf("%s - %f, %f\n", data(t), t->count, t->pagerank);
      showTreeR(left(t), depth+1);
   }
}

void showTree(Tree t) {
   showTreeR(t, 0);
}


// count #nodes in Tree
int TreeNumNodes(Tree t) {
   if (t == NULL)
      return 0;
   else
      return 1 + TreeNumNodes(left(t)) + TreeNumNodes(right(t));
}


// check whether a key is in a Tree
Tree TreeSearch(Tree t, Item it) {
   if (t == NULL)
      return NULL;
   else if (strcmp(it, data(t)) < 0)
      return TreeSearch(left(t), it);
   else if (strcmp(it, data(t)) > 0)
      return TreeSearch(right(t), it);
   else                                 // it == data(t)
      return t;
}


// insert a new item into a Tree
Tree TreeInsert(Tree t, Item it, Item s) {
  if (t == NULL) {
    t = newNode(it);
    if (s != NULL) {
      add(t->urls, s, 0);
      t->count = count(t->urls);
    }
  }
  else if (strcmp(t->data, it) == 0) {
    if (s != NULL) {
      add(t->urls, s, 0);
      t->count = count(t->urls);
    }
  }
  else if (strcmp(it, data(t)) < 0)
    left(t) = TreeInsert(left(t), it, s);
  else if (strcmp(it, data(t)) > 0)
    right(t) = TreeInsert(right(t), it, s);
  return t;
}


Tree joinTrees(Tree t1, Tree t2) {
   if (t1 == NULL)
      return t1;
   else if (t2 == NULL)
      return t2;
   else {
      Tree curr = t2;
      Tree parent = NULL;
      while (left(curr) != NULL) {    // find min element in t2
	 parent = curr;
	 curr = left(curr);
      }
      if (parent != NULL) {
	 left(parent) = right(curr);  // unlink min element from parent
	 right(curr) = t2;
      }
      left(curr) = t1;
      return curr;                    // min element is new root
   }
}


// delete an item from a Tree
Tree TreeDelete(Tree t, Item it) {
   if (t != NULL) {
      if (strcmp(it, data(t)) < 0)
	 left(t) = TreeDelete(left(t), it);
      else if (strcmp(it, data(t)) > 0)
	 right(t) = TreeDelete(right(t), it);
      else {
	 Tree new;
	 if (left(t) == NULL && right(t) == NULL)
	    new = NULL;
	 else if (left(t) == NULL)    // if only right subtree, make it the new root
	    new = right(t);
	 else if (right(t) == NULL)   // if only left subtree, make it the new root
	    new = left(t);
	 else                         // left(t) != NULL and right(t) != NULL
	    new = joinTrees(left(t), right(t));
	 free(t);
	 t = new;
      }
   }
   return t;
}

Tree rotateRight(Tree n1) {
   if (n1 == NULL || left(n1) == NULL)
      return n1;
   Tree n2 = left(n1);
   left(n1) = right(n2);
   right(n2) = n1;
   return n2;
}

Tree rotateLeft(Tree n2) {
   if (n2 == NULL || right(n2) == NULL)
      return n2;
   Tree n1 = right(n2);
   right(n2) = left(n1);
   left(n1) = n2;
   return n1;
}

Tree insertAtRoot(Tree t, Item it) {

   printf("Not yet implemented.\n");

   return t;
}

Tree partition(Tree t, int i) {
   if (t != NULL) {
      assert(0 <= i && i < TreeNumNodes(t));
      int m = TreeNumNodes(left(t));
      if (i < m) {
	 left(t) = partition(left(t), i);
	 t = rotateRight(t);
      } else if (i > m) {
	 right(t) = partition(right(t), i-m-1);
	 t = rotateLeft(t);
      }
   }
   return t;
}

Tree rebalance(Tree t) {
   int n = TreeNumNodes(t);
   if (n >= 3) {
      t = partition(t, n/2);           // put node with median key at root
      left(t) = rebalance(left(t));    // then rebalance each subtree
      right(t) = rebalance(right(t));
   }
   return t;
}


// update pagerank value of given data
Tree update_pagerank(Tree t, char *url, char *token) {
    Tree x;
    x = TreeSearch(t, url);
    if (x != NULL) {
      x->pagerank = atof(token);
    }
    return t;
}


// output data and then the urls for that data into a file
void iterate_output(Tree t, FILE *f) {
  fprintf(f, "%s ", t->data);
  output(t->urls, f);
  fprintf(f, "\n");

  return;
}

void output_to_file(Tree t, FILE *f) {
  if (left(t) == NULL && right(t) == NULL) {
    iterate_output(t, f);
    return;
  }

  if (left(t) != NULL) {
    output_to_file(left(t), f);
  }

  iterate_output(t, f);

  if (right(t) != NULL) {
    output_to_file(right(t), f);
  }

   return;
}


// output data, pagerank of that data and count in a file
void iterate_output1(Tree t, FILE *f) {
  fprintf(f, "%s,\t", t->data);
  fprintf(f, "%d, \t", (int)t->pagerank);
  fprintf(f, "%.7f\n", t->count);

  return;
}

void output_pagerank(Tree t, FILE *f) {
  if (left(t) == NULL && right(t) == NULL) {
    iterate_output1(t, f);
    return;
  }

  if (right(t) != NULL) {
    output_pagerank(right(t), f);
  }

  iterate_output1(t, f);

  if (left(t) != NULL) {
    output_pagerank(left(t), f);
  }
   return;
}


// Functions to implement search engine given pagerank
// and inverse matrix of url and search terms

// print only data of tree for only first 30 values
void print_tree(Tree t, int c) {
  if (c > 30) {
    return;
  }

  if (left(t) == NULL && right(t) == NULL) {
    printf("%s\n", t->data);
    c += 1;
    return;
  }
  if (right(t) != NULL) {
    print_tree(right(t), c);
  }
  if (c < 30) {
    printf("%s\n", t->data);
    c += 1;
  }
  if (left(t) != NULL) {
    print_tree(left(t), c);
  }

  return;
}

// insert value in tree, sorted based on first count, then pagerank if count is same
Tree sort(Tree t, char *url, float count, float pr) {
  if (t == NULL) {
    t = newNode(url);
    t->count = count;
    t->pagerank = pr;
  }
  else if (t->count == count) {
    if (t->pagerank > pr)
      left(t) = sort(left(t), url, count, pr);
    else
      right(t) = sort(right(t), url, count, pr);
  }
  else if (t->count > count)
    left(t) = sort(left(t), url, count, pr);
  else if (t->count <= count)
    right(t) = sort(right(t), url, count, pr);
  return t;
}

// iterate over tree, outorder traversal
Tree iterate(Tree x, Tree t, int depth) {
  if (t != NULL) {
     x = iterate(x, right(t), depth+1);
     x = sort(x, t->data, t->count, t->pagerank);
     x = iterate(x, left(t), depth+1);
  }

  return x;
}

// create tree with data sorted based on
// max number of arguments then pagerank
void search_engine(Tree t) {
  Tree x = newTree();
  x = iterate(x, t, 0);
  print_tree(x, 0);

  return;
}
