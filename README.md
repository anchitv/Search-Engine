# Search_Engine
Implementation of a simple search engine based on the PageRank algorithm (simplified).


## **Pagerank**

* pagerank.c reads data from a given collection of pages in the file collection.txt and builds a graph structure using List Representation. 

* It takes three arguments (**d** - damping factor, **diffPR** - difference in PageRank sum, **maxIterations** - maximum iterations) and using the Pagerank algorithm, calculates PageRank for every url.

* It outputs a list of urls in descending order of PageRank values to a file named pagerankList.txt. The list also includes out degrees (number of out going links) for each url, along with its PageRank value. The values in the list are comma separated.


## **Inverted Index**

* inverted.c reads data from a given collection of pages in collection.txt and generates an "inverted index" that provides a sorted list (set) of urls for every word in a given collection of pages.

* The words are normalised by -
  * removing leading and trailing spaces
  * converting all characters to lowercase,
  * remove the following punctuation marks, if they appear at the end of a word:  
    '.' (dot), ',' (comma), ';' (semicolon), ? (question mark)
    
* Outputs this "inverted index" to a file named invertedIndex.txt.


## **Search Engine**

* searchPagerank.c is a simple search engine that given search terms (words) as commandline arguments, finds pages with one or more search terms and outputs (to stdout) top 30 pages in descending order of number of search terms found and then within each group, descending order of PageRank.

* Data available in two files invertedIndex.txt and pagerankList.txt is used and result is derived from them.
