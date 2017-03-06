/* File: hw4.c
    Homework 4, 600.120 Spring 2017 3/8

    Jason Zhang jzhan127 jzhan127@jhu.edu
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//variables and the function definitions
char data[15001];
char match[2500];
int matched[15000];

int checkMatch(char toCheck){

}


int main(int argc, char* argv[]) {
 // printf("%s", argv[1]);
  FILE *input = fopen(argv[1], "r");
  if (argc == 1) {
         return 1;  // exit program because no command line argument present
  }
  int count = 0;

  int s = 0;
  while(!feof(input)){
      count++;
      fscanf(input, "%c", &data[s]);
      s++;

  }
  fclose(input);
  printf("%s\n", data); //2 spots for \n
  printf("%c\n", data[9]);

  int q = 0;
  while(scanf("%c", &match[q]) >= 1){
      q++;
  }
  printf("%d", matched[0]);
  return 0;

}

