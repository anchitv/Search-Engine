// Written By:- Anchit Verma
// Date:- January 2019

#include <string.h>
#include <stdio.h>

#include "BSTree.h"

#define MAXSTRING 1000

// creates a tree with given inverted index of words and urls
Tree process (char *file, Tree t, char *str) {
  char delim[]=", \t\r\n\v\f";
  char *token;
  char line[MAXSTRING];
  FILE *f;


  if ((f = fopen (file, "r")) == NULL) {
    printf("No such file in directory.\n");
    return 0;
  }

  while (fgets(line, MAXSTRING, f) != NULL && token < str) {
    token = strtok(line, delim);

    if (token != NULL && strcmp(token, str) == 0) {
      while (token != NULL) {
        token = strtok(NULL, delim);
        if (token != NULL) {
          t = TreeInsert(t, token, str);
        }
      }
    }
  }

  return t;
}


// updates the pagerank fields of each url in tree
// extracts pagerank information from a given file
Tree process_pagerank (char *file, Tree t) {
  char delim[]=", \t\r\n\v\f";
  char *token;
  char line[MAXSTRING];
  FILE *f;
  char *url;

  if ((f = fopen (file, "r")) == NULL) {
    printf("No such file in directory.\n");
    return 0;
  }

  while (fgets(line, MAXSTRING, f) != NULL) {
    token = strtok(line, delim);
    url = token;

    if (token != NULL) {
        token = strtok(NULL, delim);
        token = strtok(NULL, delim);
        t = update_pagerank(t, url, token);
    }
  }

  return t;
}


// prints the top urls for given search query in descending order of relevance
int main(int argc, char *argv[]) {
  Tree t = newTree();

  for(int i = 0; i < argc; ++i)
    t = process("invertedIndex.txt", t, argv[i]);

  t = process_pagerank("pagerankList.txt", t);
  search_engine(t);

  return 0;
}
