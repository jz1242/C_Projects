/* File: hw4.c
 Homework 4, 600.120 Spring 2017 3/8

 Jason Zhang jzhan127 jzhan127@jhu.edu
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "dnasearch.h"

int main(int argc, char* argv[]) {
    FILE *input = fopen(argv[1], "r");
    if (argc == 1) {
        return 1;  // exit program because no command line argument present
    }
    int count = 0;
    int countPat = 1;
    int s = 0;
    char temp;
    while (!feof(input)) {
       fscanf(input, "%c", &temp);
       if(!isspace(temp) && (valid(toupper(temp))) && count <= 15000){
           data[s] = toupper(temp);
           s++;
           count++;
       }
       else if(!isspace(temp) && (!valid(toupper(temp)) || count > 15000) ){
           printf("Invalid text file\n");
           return 0;
       }

    }
    fclose(input);
    //printf("%s\n", data); //2 spots for \n


    int q = 0;
    char temp2;
    while (scanf("%c", &temp2) >= 1) {
        match[q] = toupper(temp2);
        countPat++;
        q++;
    }
    match[q - 1] = ' ';

    char pat[15000];
    int *hold;
    int offset;
    bool cont = true;
    for (int i = 0; i < countPat; i++) {
        if (match[i] == ' ') {
            if(i - offset > count){
                printf("Invalid pattern\n");
            }
            else{
                strncpy(pat, match + offset, (i - offset));
                pat[i - offset] = '\0';

                for(int j = 0; j < i - offset; j++){
                    if(valid(pat[j])){
                        cont = true;

                    }
                    else{
                        cont = false;
                        break;
                    }
                }
               if(cont == true){
                    hold = checkMatch(pat, (i - offset), count);
                    printAll(pat, hold);
                    free(hold);
                }
                else{
                    printf("Invalid pattern\n");

                }
            }
            offset = (i + 1);

        }
    }

    return 0;
}

