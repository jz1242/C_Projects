/* File: hw4.c
 Homework 4, 600.120 Spring 2017 3/8

 Jason Zhang jzhan127 jzhan127@jhu.edu
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

//variables and the function definitions
char data[15001];
char match[15001];
int matched[15000];

int* checkMatch(char toCheck[], int len, int lenTot) {
    int* places = (int *) malloc(sizeof(int)*2000);
    bool match = true;
    int count = 0;
    for(int i = 0; i < lenTot - len; i++){
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
    return places;
}

void printAll(int a[]){
    int i = 0;
    while(a[i] != -1){
        printf("%d ", a[i]);
        i++;
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    FILE *input = fopen(argv[1], "r");
    if (argc == 1) {
        return 1;  // exit program because no command line argument present
    }
    int count = 0;
    int countPat = 1;

    int s = 0;
    while (!feof(input)) {
        fscanf(input, "%c", &data[s]);
        s++;
        count++;

    }
    fclose(input);
    printf("%s\n", data); //2 spots for \n
    printf("%c\n", data[9]);

    int q = 0;
    while (scanf("%c", &match[q]) >= 1) {

        countPat++;
        q++;
    }
    match[q] = ' ';

    char pat[15000];
    int offset;
    for (int i = 0; i < countPat; i++) {
        if (match[i] == ' ') {
            strncpy(pat, match + offset, (i - offset));
            pat[i - offset] = '\0';
            printAll(checkMatch(pat, (i - offset), count - 1));
            offset = (i + 1);
            printData[0] = '\0';
        }
    }

    return 0;
}

