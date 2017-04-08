/* File: hw6.c
 Homework 6, 600.120 Spring 2017 4/9

 Jason Zhang jzhan127 jzhan127@jhu.edu
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "methods.h"

typedef struct pixel{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Pixel;

Pixel *data;
int row;
int col;
int color;
int invert = 0;

int checkChar(char a, int count){
    int valid = 0;
    if(a == 'P' && count < 10){
        valid = 1;
    }
    if(a >= 0 && a <=9){
        valid = 1;
    }
    return valid;
}

int main() {
    char str[250];
    while(str[0] != 'q'){
        FILE *input;
        FILE *output;
        menu_prompt();
        int throw;
        scanf("%d\n", &throw);
        fgets(str, 250, stdin);
        for(int i = 0; i < strlen(str); i++){
            if(str[i] == '\n'){
                str[i] = '\0';
            }
        }
        if(str[0] == 'r'){
            free(data);
            char file[200];
            strcpy(file, str+2);
            //printf("%s\n", file);
            input = fopen(file, "r");
            char temp[100];
            char throw;
            fgets(temp, 100, input);
            throw = getc(input);
            while(throw == '#'){
                while(throw != '\n'){
                    throw = getc(input);
                }
                throw = getc(input);
            }
            ungetc(throw, input);
            fscanf(input, "%d %d \n%d\n",&col, &row, &color);
            data = malloc(row*col*sizeof(Pixel));
            fread(data, sizeof(Pixel) *col, row, input);
            fclose(input);
        }
        if(str[0] == 'w'){
            char file[100];
            strcpy(file, str+2);
            output = fopen(file, "w");
            fprintf(output, "P6\n");
            fprintf(output, "%d %d\n", col, row);
            fprintf(output, "%d\n", color);
            fwrite(data, sizeof(Pixel)*col, row, output);
            fclose(output);
        }
        if(str[0] == 'c'){
            str[17] = ' ';
            int vals[5];
            int offset = 2;
            int ind = 0;
           for(int i = 2; i < 30; i++){
                if(str[i] == ' '){
                    char temp[4];
                    strncpy(temp, str+offset, i - offset);
                    temp[i-offset] = '\0';
                    vals[ind] = atoi(temp);
                    ind++;
                    offset = i;
                }
            }

            int crop = (vals[1]) *col + (vals[0]);
            int newRow = (vals[2]) - (vals[0]);
            int newCol = (vals[3]) - (vals[1]);
            Pixel *temp = malloc(newRow*newCol*sizeof(Pixel));
            int count = 0;

            for(int i = 0; i < newRow; i++){
                for(int j = 0; j < newCol; j++){
                    temp[count] = data[crop + j];
                    count++;
                }
                crop += col;
            }
           free(data);
           data = temp;
           col = newCol;
           row = newRow;
        }
        if(str[0] == 'i'){
            for(int i = 0; i < col*row; i++){
               data[i].red = color - data[i].red;
               data[i].green = color - data[i].green;
               data[i].blue = color - data[i].blue;
            }
        }
        if(str[0] == 's'){
            for(int i = 0; i < col*row; i++){
               unsigned char temp = data[i].red;
               unsigned char temp2 = data[i].green;
               unsigned char temp3 = data[i].blue;
               data[i].red = temp2;
               data[i].green = temp3;
               data[i].blue = temp;
            }
        }
        if(str[0] == 'g'){
            for(int i = 0; i < col*row; i++){
               double intensity = 0.30*data[i].red + 0.59*data[i].green + 0.11*data[i].blue;
               data[i].red = intensity;
               data[i].green = intensity;
               data[i].blue = intensity;
            }

        }
        if(str[0] == 'b'){
            char inp[100];
            strcpy(inp, str+2);
            float brightness = atof(inp);
            printf("%f", brightness);
            for(int i = 0; i < col*row; i++){
               if(data[i].red * brightness > 255){
                   data[i].red = 255;
               }
               else{
                   data[i].red *= brightness;
               }
               if(data[i].green * brightness > 255){
                   data[i].green = 255;
               }
               else{
                   data[i].green *= brightness;
               }
               if(data[i].blue * brightness > 255){
                   data[i].blue = 255;
               }
               else{
                   data[i].blue *= brightness;
               }

            }
        }
    }
    return 0;
}

