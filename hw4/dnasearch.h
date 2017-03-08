/* File: dnasearch.h
 Homework 4, 600.120 Spring 2017 3/8

 Jason Zhang jzhan127 jzhan127@jhu.edu
 */

#ifndef DNASEARCH_H_
#define DNASEARCH_H_

char data[15001];
char match[15001];
int* checkMatch(char toCheck[], int len, int lenTot);
void printAll(char check[], int a[]);
int valid(char a);

#endif /* DNASEARCH_H_ */
