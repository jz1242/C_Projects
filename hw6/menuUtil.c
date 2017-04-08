/* File: hw6.c
 Homework 6, 600.120 Spring 2017 4/9

 Jason Zhang jzhan127 jzhan127@jhu.edu
 */
#include <stdio.h>
#include "methods.h"

void menu_prompt() {
    printf(
      "Main menu:\n"
      "        r <filename> -read image from <filename>\n"
      "        w <filename> -write image to <filename>\n"
      "        c <x1><y1><x2><y2> -crop image to the box with the given corners\n"
      "        i - invert intensities\n"
      "        s - swap color channels\n"
      "        g - convert to grayscale\n"
      "        b <amt> - change brightness (up or down) by the given amount\n"
      "        q - quit \n"
      "Enter your choice:\n");
}

void course_absent_msg() {
    printf("The course is not available.\n");
}

void course_not_taken_msg() {
    printf("The course has not been taken.\n");
}

void course_updated_msg() {
    printf("The course has been updated.\n");
}

void empty_transcript_msg() {
    printf("The transcript is empty.\n");
}

void invalid_input_msg() {
    printf("Invalid input.\n");
}

void duplicate_course_msg() {
    printf("The course is already present.\n");
}

void transcript_updated_msg() {
    printf("The transcript has been updated.\n");
}

void course_prompt() {
    printf("Enter a course:\n");
}

void semester_prompt() {
    printf("Enter a semester:\n");
}

void grade_prompt() {
    printf("Enter course grade:\n");
}

void new_title_prompt() {
    printf("Enter a new course title:\n");
}

void new_credit_prompt() {
    printf("Enter a new credit assignment:\n");
}

void gpa_msg(double gpa) {
    printf("Student GPA is %.2f\n", gpa);
}
