/* File: dnasearch.c
 Homework 4, 600.120 Spring 2017 3/8

 Jason Zhang jzhan127 jzhan127@jhu.edu
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "dnasearch.h"

//variables and the function definitions
char data[15001];
char match[15001];

int* checkMatch(char toCheck[], int len, int lenTot) {
    int* places = (int *) malloc(sizeof(int)*2000);
    bool match = true;
    int count = 0;
    for(int i = 0; i <= lenTot - len; i++){
        for(int j = 0; j < len; j++){
            if(toCheck[j] != data[i+j]){
                match = false;
                break;
            }
            else{
                match = true;
            }

        }
        if(match == true){
            places[count] = i;
            count++;
        }
    }
    places[count] = -1;
    return places;
}

void printAll(char check[], int a[]){
    int i = 0;
    printf("%s", check);
    while(a[i] != -1){
        printf(" %d", a[i]);
        i++;
    }
    if(i < 1){
        printf(" Not found");
    }
    printf("\n");

}

int valid(char a){

    if(a == 'A' || a == 'C' || a == 'T'|| a == 'G'){
        return 1;

    }
    return 0;
}
