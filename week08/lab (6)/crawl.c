// crawl.c ... build a graph of part of the web
// Written by John Shepherd, September 2015
// Uses the cURL library and functions by Vincent Sanders <vince@kyllikki.org>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <curl/curl.h>
#include "stack.h"
#include "set.h"
#include "queue.h"
#include "graph.h"
#include "html.h"
#include "url_file.h"

#define BUFSIZE 1024

void setFirstURL(char *, char *);
void normalise(char *, char *, char *, char *, int);

int main(int argc, char **argv)
{
	URL_FILE *handle;
	char buffer[BUFSIZE];
	char baseURL[BUFSIZE];
	char firstURL[BUFSIZE];
	char next[BUFSIZE];
	int  maxURLs;
	char *curr_url;
	if (argc > 2) {
		strcpy(baseURL,argv[1]);
		setFirstURL(baseURL,firstURL);
		maxURLs = atoi(argv[2]);
		if (maxURLs < 40) maxURLs = 40;
	}
	else {
		fprintf(stderr, "Usage: %s BaseURL MaxURLs\n",argv[0]);
		exit(1);
	}
	// initialise Graph to hold up to maxURLs
	Graph newG = newGraph(maxURLs);
	// initialise set of Seen URLs
	Set seen = newSet();
	// initialise the page quene to maintain
	Queue list = newQueue();
	// add firstURL to the ToDo list
	enterQueue(list,firstURL);
	insertInto(seen, firstURL);
	// while ToDo list not empty and Graph not filled
	while(!emptyQueue(list) && nVertices(newG) < maxURLs) {
		// grab Next URL from ToDo list
		curr_url = leaveQueue(list);
		// if not allowed, continue
		if (!(handle = url_fopen(curr_url, "r"))) {
			fprintf(stderr,"Couldn't open %s\n", next);
		    exit(1);
		}
		// foreach line in the opened URL
		while(!url_feof(handle)) {
			url_fgets(buffer,sizeof(buffer),handle);
			//fputs(buffer,stdout);
			int pos = 0;
			char result[BUFSIZE];
			memset(result,0,BUFSIZE);
			while ((pos = GetNextURL(buffer, curr_url, result, pos)) > 0) {
				// if Graph not filled or both URLs in Graph
				if(nVertices(newG) < maxURLs || isConnected(newG,next,result)){
				// add an edge from Next to this URL
					addEdge(newG,curr_url,result);
					// printf("Found: '%s'\n",result);
					// printf("get here\n");

				}
				// if this URL not Seen already
				if (!isElem(seen,result)){
					// add it to the Seen set
					// add it to the ToDo list
					enterQueue(list,result);
					insertInto(seen,result);
					printf("Found: '%s'\n",result);
				}
				memset(result,0,BUFSIZE);
			}
		}
	}
	url_fclose(handle);
	sleep(1);
	showGraph(newG, 1);
	return 0;
}

// setFirstURL(Base,First)
// - sets a "normalised" version of Base as First
// - modifies Base to a "normalised" version of itself
void setFirstURL(char *base, char *first)
{
	char *c;
	if ((c = strstr(base, "/index.html")) != NULL) {
		strcpy(first,base);
		*c = '\0';
	}
	else if (base[strlen(base)-1] == '/') {
		strcpy(first,base);
		strcat(first,"index.html");
		base[strlen(base)-1] = '\0';
	}
	else {
		strcpy(first,base);
		strcat(first,"/index.html");
	}
}
