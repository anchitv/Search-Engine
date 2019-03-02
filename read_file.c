// Written By:- Anchit Verma
// Date:- January 2019

#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "listIteratorInt.h"
#include "BSTree.h"
#include "Graph.h"

#define MAXSTRING 1000


// reads the file containing list of urls and creates a coded list
// returns number of urls added
int initialise(IteratorInt coded_list) {
  char filename[] = "collection.txt";
  char delim[] = " \t\r\n\v\f";
  char *token;
  char line[MAXSTRING];
  FILE *f;

  int count = 0;


  if ((f = fopen(filename, "r")) == NULL) {
    printf("No such file in directory.\n");
    return 0;
  }

  while(fgets(line, MAXSTRING, f) != NULL) {
    token = strtok(line, delim);

    while(token != NULL) {
      add(coded_list, token, count++);
      token = strtok(NULL, delim);
    }
  }

  return count;
}


// removes punctuations from end of string and converts string to lower
char *process_str(char *str) {
  int i = 0;
  for(; str[i]; i++) {
    str[i] = tolower(str[i]);
  }

  if (!(strcmp(&str[i-1], ".") && strcmp(&str[i-1], ",") && strcmp(&str[i-1], ";") && strcmp(&str[i-1], "?"))) {
    char *x = "\0";
    str[i-1] = *x;
  }

  return str;
}


// creates a directed graph using code of urls for 1 url file
Graph section1(char *file, Graph g, IteratorInt coded_list) {
  char filename[100] = "";
  strcat(filename, file);
  strcat(filename, ".txt");

  char delim[] = " \t\r\n\v\f";
  char *token;
  char line[MAXSTRING];
  FILE *f;
  char *limiter = "Section-1";

  if ((f = fopen (filename, "r")) == NULL) {
  	printf("No such file in directory.\n");
  	return NULL;
  }

  // reads from section 1 in each url file to find connected urls
  while(fgets(line, MAXSTRING, f) != NULL)  {
    token = strtok(line, delim);
    while (token != NULL && strcmp(token, "#start") != 0) {
      token = strtok(NULL, delim);
    }
    token = strtok(NULL, delim);
    if (token != NULL && strncmp(token, limiter, 9) == 0) {
      token = strtok(NULL, delim);
      while(fgets(line, MAXSTRING, f) != NULL) {
        token = strtok(line, delim);
        while(token != NULL && strcmp(token, "#end") != 0) {
          Edge e;
          e.v = *findNext(coded_list, file);
          e.w = *findNext(coded_list, token);
          insertEdge(g, e);
          token = strtok(NULL, delim);
        }
        token = strtok(NULL, delim);
        if (token != NULL && strncmp(token, limiter, 9) == 0) {
          break;
        }
      }

      return g;
    }
  }

  return g;
}

// returns the directed graph of urls for all urls
Graph readsection1(IteratorInt coded_list) {
    int nV = initialise(coded_list);
    Graph url_graph = newGraph(nV);

    reset(coded_list);

    while(hasNext(coded_list))
      url_graph = section1(next(coded_list), url_graph, coded_list);

    return url_graph;
}



// inserts words in url into the tree node of that url as a list
Tree section2(char *file, Tree t) {
  char filename[100] = "";
  strcat(filename, file);
  strcat(filename, ".txt");

  char delim[] = " \t\r\n\v\f";
  char *token;
  char line[MAXSTRING];
  FILE *f;
  char *limiter = "Section-2";
  int count = 0;

  if ((f = fopen (filename, "r")) == NULL) {
  	printf("No such file in directory.\n");
  	return NULL;
  }

  // reads from section 2 in each url file to find words in each url
  while(fgets(line, MAXSTRING, f) != NULL)  {
    token = strtok(line, delim);
    while (token != NULL && strcmp(token, "#start") != 0) {
      token = strtok(NULL, delim);
    }
    token = strtok(NULL, delim);
    if (token != NULL && strncmp(token, limiter, 9) == 0) {
      token = strtok(NULL, delim);
      while(fgets(line, MAXSTRING, f) != NULL) {
        token = strtok(line, delim);
        while(token != NULL && strcmp(token, "#end") != 0) {
          t = TreeInsert(t, process_str(token), file);
          token = strtok(NULL, delim);
          count += 1;
        }
        token = strtok(NULL, delim);
        if (token != NULL && strncmp(token, limiter, 9) == 0) {
          break;
        }
      }

      return t;
    }
  }

  return t;
}

// creates a tree of all urls, having the list of words as an attribute of each url node
Tree readsection2() {
    IteratorInt coded_list = IteratorIntNew();
    initialise(coded_list);
    Tree word_tree = newTree();

    reset(coded_list);

    while(hasNext(coded_list)) {
      word_tree = section2(next(coded_list), word_tree);
    }

    return word_tree;
}
