// Linked list interface ... COMP9024 17s2
// Edited By:- Anchit Verma
// Date:- January 2019

#include <stdbool.h>

typedef struct Node *List;

List insertLL(List L, int n, float pr);
List updatepr(List L, int n, float pr);
int size(List L);
int value(List L, int *arr, int c);
List deleteLL(List, int);
bool inLL(List, int);
void freeLL(List);
void showLL(List);
