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
    FILE *input = fopen(argv[1], "r");      //get file and take user inpt
    if (argc == 1) {
        return 1;  // exit program because no command line argument present
    }
    int count = 0;          //variable counters
    int countPat = 1;
    int s = 0;
    char temp;
    while (fscanf(input, "%c", &temp) != EOF) {
       if(!isspace(temp) && (valid(toupper(temp))) && count <= 15000){      //check if file is >15000 and if character is valid
           data[s] = toupper(temp);
           s++;
           count++;
       }
       else if(!isspace(temp) && (!valid(toupper(temp)) || count > 15000) ){
           printf("Invalid text file\n");
           return 1;
       }

    }
    fclose(input);

    int q = 0;
    char temp2;
    while (scanf("%c", &temp2) >= 1) {  //take user input until the eof
        match[q] = toupper(temp2);
        countPat++;
        q++;
    }
    match[q - 1] = ' ';

    char pat[15000];        //temp string
    int *hold;              //to hold int array
    int offset;             //holds offset
    bool cont = true;
    for (int i = 0; i < countPat; i++) {
        if (match[i] == ' ') {      //check for pattern > total data
            if(i - offset > count){
                printf("Invalid pattern\n");
                return 1;
            }
            else{
                strncpy(pat, match + offset, (i - offset));     //get a substring of pattern
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
               if(cont == true){                        //if string is legal then check for matches
                    hold = checkMatch(pat, (i - offset), count);
                    printAll(pat, hold);
                    free(hold);
                }
                else{
                    printf("Invalid pattern\n");
                    return 1;

                }
            }
            offset = (i + 1);           //increase the offset

        }
    }

    return 0;
}

