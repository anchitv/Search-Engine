/*
  listIteratorInt.h
  Interface to List Iterator that stores integer values
  Written by Ashesh Mahidadia
  Edited by Anchit Verma
  Date: January 2019

  *** DO NOT modify this file. ***
*/

#ifndef LISTITERINT_H
#define LISTITERINT_H

#include <stdio.h>

typedef struct IteratorIntRep *IteratorInt;

IteratorInt IteratorIntNew();
int add(IteratorInt it, char *v, int c);
int hasNext(IteratorInt it);
int hasPrevious(IteratorInt it);
char *next(IteratorInt it);
int *previous(IteratorInt it);
int deleteElm(IteratorInt it);
int set(IteratorInt it, int v);
int *findNext(IteratorInt it, char *v);     
char *find_url(IteratorInt it, int c);      // Return url name from url code
int *findPrevious(IteratorInt it, int v);
void reset(IteratorInt it);
void freeIt(IteratorInt it);
void output(IteratorInt it, FILE *f);
int count(IteratorInt it);

#endif
