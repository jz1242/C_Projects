/* File: unittest.c
 Homework 4, 600.120 Spring 2017 3/8

 Jason Zhang jzhan127 jzhan127@jhu.edu
 */
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "dnasearch.h"

void testCheckMatch();
void testValid();

int main() {
    testCheckMatch();
    testValid();
    printf("All tests passed");
    return 0;
}

void testCheckMatch() {             //takes in input from dna1 to test the function
    FILE *input = fopen("dna1.txt", "r");
    int count = 0;
    int s = 0;
    char temp;
    while (!feof(input)) {
        fscanf(input, "%c", &temp);
        if (!isspace(temp)) {
            data[s] = toupper(temp);
            s++;
            count++;
        }

    }
    assert(checkMatch("CAT", 3, count)[0] == 0);       //test int arrays of the strings inputted
    assert(checkMatch("TAC", 3, count)[0] == 5);
    assert(checkMatch("TAC", 3, count)[1] == 11);
    assert(checkMatch("CGA", 3, count)[0] == 7);
    assert(checkMatch("GGG", 3, count)[0] == -1);
}

void testValid(){
    assert(valid('F') == 0);        //checks random characters to see if valid works
    assert(valid('A') == 1);
    assert(valid('C') == 1);
    assert(valid('T') == 1);
    assert(valid('G') == 1);
    assert(valid('Z') == 0);
}

