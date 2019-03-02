// Written By:- Anchit Verma
// Date:- January 2019

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "read_file.h"
#include "BSTree.h"
#include "listIteratorInt.h"
#include "list.h"


// finds url name from url code
char *decoded_list(IteratorInt coded_list, int c) {
  char *url;
  url = find_url(coded_list, c);

  return url;
}

float *reset_array(float array[], int num) {
  for (int i=0; i<num; i++)
    array[i] = 0;

  return array;
}


int main(int agrgc, char *argv[]) {
  // read given inputs
  float d = strtof(argv[1], NULL);
  float diffPR = strtof(argv[2], NULL);
  long max_iter = strtol(argv[3], NULL, 10);

  // initialisation of variables
  int iter = 0;
  float diff = diffPR;

  IteratorInt coded_list = IteratorIntNew();
  Graph url_graph = readsection1(coded_list);

  int num_vertices = url_graph->nV;
  float pr = 1.0/num_vertices;

  float pagerank_array[num_vertices];

  // initialises the pagerank of all urls
  for (int i=0; i<num_vertices; i++) {
    pagerank_array[i] = pr;
    for (int j=0; j<num_vertices; j++)
      url_graph->edges[i] = updatepr(url_graph->edges[i], j, pr);
  }

  // pagerank algorithm
  while (iter < max_iter && diff >= diffPR) {
    iter++;

    float pr_l[num_vertices];
    reset_array(pr_l, num_vertices);

    diff = 0;

    for (int i=0; i<num_vertices; i++) {
      for (int j=0; j<num_vertices; j++) {
        if (inLL(url_graph->edges[j], i))
          pr_l[i] += pagerank_array[j]/size(url_graph->edges[j]);
      }

      pagerank_array[i] = ((1 - d) / num_vertices) + (d * pr_l[i]);
      diff += fabsf(pagerank_array[i] - pr);
    }

  }


  Tree url_tree = newTree();

  // create a tree sorted by pagerank
  for (int i=0; i<num_vertices; i++)
    url_tree = sort(url_tree, decoded_list(coded_list, i), pagerank_array[i], size(url_graph->edges[i]));

  FILE *f = fopen("pagerankList.txt", "w");
  output_pagerank(url_tree, f);

  return 0;
}
