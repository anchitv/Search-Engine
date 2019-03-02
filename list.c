// Linked list implementation ... COMP9024
// Edited By:- Anchit Verma
// Date:- January 2019

#include "list.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
   int v;
   float pr;
   struct Node *next;
} Node;

Node *makeNode(int n, float pr) {
   Node *new = malloc(sizeof(Node));
   assert(new != NULL);
   new->v = n;
   new->next = NULL;
   new->pr = pr;
   return new;
}

List insertLL(List L, int n, float pr) {
   if (inLL(L, n)) {
     return L;
   }

   // add new node at the beginning
   Node *new = makeNode(n, pr);
   new->next = L;
   return new;
}


int value(List L, int *arr, int c) {
  int i = 0;

  while (L != NULL) {
    L = L->next;
    arr[i] = L->v;
    i++;
  }

  return 1;
}


List updatepr(List L, int n, float pr) {
  if (L == NULL)
    return L;

  if (L->v == n) {
    L->pr = pr;
    return L;
  }
  else
    updatepr(L->next, n, pr);

  return L;
}


List deleteLL(List L, int n) {
   if (L == NULL)
      return L;
   if (L->v == n)
      return L->next;

   L->next = deleteLL(L->next, n);
   return L;

}

bool inLL(List L, int n) {
   if (L == NULL)
      return false;
   if (L->v == n)
     return true;

   return inLL(L->next, n);
}

void showLL(List L) {
   if (L == NULL)
      putchar('\n');
   else {
      printf("%d-%f ", L->v, L->pr);
      showLL(L->next);
   }
}

void freeLL(List L) {
   if (L != NULL) {
      freeLL(L->next);
      free(L);
   }
}

int size(List L) {
  int i = 0;

  while (L != NULL) {
    L = L->next;
    i += 1;
  }

  return i;
}
