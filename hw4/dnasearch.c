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

int* checkMatch(char toCheck[], int len, int lenTot) {  //checks for matches in the data
    int* places = (int *) malloc(sizeof(int)*(lenTot + 1));
    bool match = true;
    int count = 0;
    for(int i = 0; i <= lenTot - len; i++){         //for loop to find the matches
        for(int j = 0; j < len; j++){
            if(toCheck[j] != data[i+j]){
                match = false;
                break;
            }
            else{
                match = true;
            }

        }
        if(match == true){          //adds matches to an int array
            places[count] = i;
            count++;
        }
    }
    places[count] = -1;     //place  -1 in the last place to notify of last place
    return places;
}

void printAll(char check[], int a[]){       //function to print all vals in the int array
    int i = 0;
    printf("%s", check);
    while(a[i] > -1){
        printf(" %d", a[i]);
        i++;
    }
    if(i < 1){
        printf(" Not found");           //if i doesnt increment there are no values inside
    }
    printf("\n");

}

int valid(char a){          //check if a character is valid

    if(a == 'A' || a == 'C' || a == 'T'|| a == 'G'){
        return 1;

    }
    return 0;
}
