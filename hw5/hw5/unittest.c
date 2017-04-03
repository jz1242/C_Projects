/* File: unittest.c
 Homework 5, 600.120 Spring 2017 4/2

 Jason Zhang jzhan127 jzhan127@jhu.edu
 */
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "methods.h"
#include "prompts.h"

void testCreateCourse();
void testCheckCase();
void testCompareCourse();
void testSearchCourse();
void testSearchTranscript();
void testSearchTranscriptNoDel();
void testCheckValidCourse();
void testCheckValidTitle();
void testCheckValidCred();
void testCheckValidSem();
void testCheckValidGrade();
void testCheckDup();
void testGradeConvert();

int main() {
    testCreateCourse();
    testCheckCase();
    testCompareCourse();
    testSearchCourse();
    testCheckValidCourse();
    testCheckValidTitle();
    testCheckValidCred();
    testCheckValidSem();
    testCheckValidGrade();
    testGradeConvert();
    printf("All tests passed");
    return 0;
}

void testCreateCourse() {             //takes in input from dna1 to test the function
    char str[100] = "EN.550.171 4.0 Discrete Mathematics";
    Course course = createCourse(str);
    assert(strcmp(course.div, "EN") == 0);
    assert(course.dep == 550);//test int arrays of the strings inputted
    assert(course.num == 171);
    assert(strcmp(course.title, "Discrete Mathematics") == 0);
}

void testCheckCase(){
    char a[3] = "EN";
    char b[3] = "en";
    int c = checkCase(a, b);
    assert(c == 1);
}

void testCompareCourse(){
    char str[] = "en.550.171 4.0 Discrete Mathematics";
    Course course1 = createCourse(str);
    Course course2 = createCourse(str);
    int a = compareCourse(course1, course2);
    assert(a == 1);

}

void testSearchCourse(){
    FILE *input = fopen("catalog1.txt", "r");      //get file and take user inpt
    int index = 0;  //variable counters
    int size = 10;
    char temp[100];
    Course temp2;
    data = malloc(size * sizeof(Course));
    while (fgets(temp, 100, input)) {
        if (index >= size) {
            size *= 2;
            data = realloc(data, size * sizeof(Course));
        }
        temp2 = createCourse(temp);
        data[index] = temp2;
        index++;
    }
    char inp[] = "en.550.171";
    fclose(input);
    assert(searchCourse(index, inp) == 0);
}

void testCheckValidCourse(){
    char inp[]="en.550.171";
    assert(checkValidCourse(inp) == 1);
}

void testCheckValidTitle(){
    char inp[]="DiscreteMathematics";
    assert(checkValidTitle(inp) == 1);
}
void testCheckValidCred(){
    char inp[] = "4.0";
    assert(checkValidCred(inp) == 1);
}
void testCheckValidSem(){
    char inp[] = "1999.s";
    assert(checkValidSem(inp) == 1);
}

void testCheckValidGrade(){
    assert(checkValidGrade("A+") == 1);
}

void testGradeConvert(){
    assert(gradeConvert("A+") == 4.0);
}

