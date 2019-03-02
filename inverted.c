// Written By:- Anchit Verma
// Date:- January 2019

#include "read_file.h"
#include "BSTree.h"


int main() {
  Tree word_tree = newTree();
  word_tree = readsection2();

  FILE *f = fopen("invertedIndex.txt", "w");
  output_to_file(word_tree, f);
  fclose(f);

  return 0;
}
