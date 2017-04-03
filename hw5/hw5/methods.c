/* File: hw5.c
 Homework 5, 600.120 Spring 2017 3/8

 Jason Zhang jzhan127 jzhan127@jhu.edu
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "methods.h"
#include "prompts.h"

Course createCourse(char *str) {	//creates course by parsing the input string
    Course course;
    strncpy(course.div, str, 2);
    course.div[2] = '\0';
    char dep[4];
    strncpy(dep, str + 3, 3);
    course.dep = atoi(dep);
    char num[4];
    strncpy(num, str + 7, 3);
    course.num = atoi(num);
    char assignment[4];
    strncpy(assignment, str + 11, 3);
    course.assignment = atof(assignment);
    strncpy(course.title, str + 15, 32);
    course.title[32] = '\0';
    return course;

}
void printCourses(int num) {		//prints all of the courses

    for (int i = 0; i < num; i++) {
        Course temp = data[i];
        for(unsigned j = 0; j < strlen(temp.title); j++){
            if(temp.title[j] == '\n'){
                temp.title[j] = '\0';
            }
        }
        printf("%s.%03d.%03d %0.1f %s\n", temp.div, temp.dep, temp.num,
                temp.assignment, temp.title);
    }

}
int checkCase(char* a, char* b) {		//checks if the strings are equivalent case insensitive
    int equal = 1;
    // printf("%d %d \n", strlen(a), strlen(b));
    for (unsigned i = 0; i < strlen(b); i++) {
        if (toupper(a[i]) != toupper(b[i])) {
            equal = 0;
        }
    }
    return equal;
}
int compareCourse(Course a, Course b) {	//compares both of the courses to see if theyre equal
    int equal = 1;
    if (checkCase(a.div, b.div) == 0) {
        equal = 0;

    }
    if (a.dep != b.dep) {
        equal = 0;

    }
    if (a.num != b.num) {
        equal = 0;

    }
    //printf("%d\n",equal );
    return equal;
}
int searchCourse(int num, char *str) {	//search through all of the courses to see if it exists
    Course comp = createCourse(str);
    bool s = false;
    int ind = -1;
    for (int i = 0; i < num; i++) {
        if (compareCourse(comp, data[i])) {
            ind = i;
            s = true;
        }
    }
    if (s == false) {
        course_absent_msg();
    }
    return ind;
}

node* Create(Course course, char* year, char* grade) {	//creates a course node
    node *e = malloc(sizeof(node));
    e->next = NULL;
    e->course = course;
    strncpy(e->year, year, 6);
    (e->year)[6] = '\0';
    strncpy(e->grade, grade, 2);
    (e->grade)[2] = '\0';
    return e;
}

void InsertAfter(node *e, Course course, char* year, char* grade) { //insert a node after a passed in node
    node *newE = Create(course, year, grade);
    newE->next = e->next;
    e->next = newE;
}

void InsertHead(node **head, Course course, char* year, char* grade) {	//insert a node at the head
    node *e = Create(course, year, grade);
    e->next = *head;
    *head = e;
}

void DeleteAfter(node *e) {	//delete a node after a given node
    node* eNext = e->next;
    if (!eNext) {
        return;
    }
    e->next = e->next->next;
    free(eNext);
}
void DeleteHead(node **head) {	//delete the node at the head
    node* e = (*head);
    *head = e->next;
    free(e);
}

int searchTranscript(node **head, Course course) {	//search through the transcript
    node *e;
    int exist = 0;
    bool run = false;
    for (e = *head; e != NULL; e = e->next) {
        if (compareCourse(course, e->course)) {
            exist++;
        }
    }
    if (exist == 1) {	//delete immediately if there was only 1
        if (compareCourse(course, (*head)->course)) {
            DeleteHead(*(&head));
        }

        else {	//search through linkedlist and delete
            for (e = *head; e->next != NULL; e = e->next) {

                if (compareCourse(course, (e->next)->course)) {
                    DeleteAfter(e);
                    break;
                }
            }
        }
    } else if (exist > 1) {	//check if there are more than one course
            int valid2 = 0;
            char inp[7];
            while(valid2 == 0){;
                semester_prompt();
                fgets(inp, 100, stdin);
                valid2 = checkValidSem(inp);
				inp[5] = toupper(inp[5]);
                valid2 = checkDup(&(*head), course,inp);	//check if theres a duplicate
            }
            
            if (compareCourse(course, (*head)->course)) {
                if(strcmp((*head)->year, inp) == 0){
                    DeleteHead(*(&head));
                }
                else{
                    run = true;
                }

            }
            else{
                run = true;
            }
            if(run){
                for(e = *head; e->next !=NULL; e = e->next){	//delte the course with the inputted semester
                     if(compareCourse((e->next)->course, course)){
                         if(strcmp((e->next)->year, inp) == 0){
                             break;
                         }
                     }
                 }
                DeleteAfter(e);
            }



    }
    return exist;
}

int searchTranscriptNoDel(node **head, Course course){	//search through the transcripts without deleting
    node *e;
    int exist = 0;
    for (e = *head; e != NULL; e = e->next) {
        if (compareCourse(course, e->course)) {
            exist++;
        }
    }
    return exist;
}


void printTranscript(node **head, int count) {		//print the entire transcript
    node *e;
    if (count <= 0) {
        empty_transcript_msg();
    } else {
        for (e = *head; e != NULL; e = e->next) {
            Course temp = e->course;
            for(unsigned j = 0; j < strlen(temp.title); j++){
				
                if(temp.title[j]== '\n'){
                    temp.title[j] = '\0';
					break;
                }
            }

            printf("%s %s %s.%03d.%03d %0.1f %s\n",e->year, e->grade,
                    temp.div, temp.dep, temp.num,
                    temp.assignment, temp.title);
        }
    }
}

void printCourseData(node **head, Course course) {		//print all the course data
    node *e;
    for (e = *head; e != NULL; e = e->next) {
        if (compareCourse(course,e->course)) {
            printf("%s %s\n", e->year, e->grade);
        }
    }
}

int checkValidCourse(char *a){		//check if the course is valid 
    int valid = 1;
    if(a[2] != '.' || a[6] != '.' || strlen(a) > 11 ){
        valid = 0;
    }
    if(toupper((a[0])<65 || toupper(a[0])>90) && (toupper(a[1])<65 && toupper(a[1])>90)){
        valid = 0;
    }
    if(a[3] - '0' >9 || a[4] - '0'>9 || a[5] - '0'>9 || a[7] - '0'>9 || a[8] - '0'>9 || a[9] - '0'>9){
        valid = 0;
    }
    return valid;
}

int checkValidTitle(char *a){		//check if title is within the requirements
    if(strlen(a) > 33){
        return 0;
    }
    return 1;
}

int checkValidCred(char *a){	//check if credit assignment is valid
    if(strlen(a) > 4){
        return 0;
    }
    if(a[1] != '.'){

        return 0;
    }
    return 1;
}

int checkValidSem(char *a){	//check if the semester is valid
    if(strlen(a) > 7){
        return 0;
    }
    if(a[4] != '.'){

        return 0;
    }
    if(toupper(a[5]) != 'S'){
        if(toupper(a[5]) != 'F'){
            return 0;
        }

    }
    return 1;
}

int checkValidGrade(char *a){	//check if the grade is valid
    if(strlen(a) > 3){
        return 0;
    }
    if(toupper(a[0])<65 || toupper(a[0])>70){

        return 0;
    }
    if(a[1] != '+'){
        if(a[1] != '-'){
            if(a[1] != '/'){
                return 0;
            }
        }


    }
    return 1;
}
int checkDup(node **head, Course course, char *sem){		//check if there is a duplicate course
    sem[6] = '\0';
    node* e;
    int dup = 0;
    for(e = *head; e !=NULL; e = e->next){
        if(compareCourse(e->course, course)){
            if(strcmp(e->year, sem) == 0){

                dup = 1;
                break;
            }
        }
    }
    return dup;
}
double gradeConvert(char *a) {		//convert the grade to double 
    double grade = 0.0;
    if (toupper(a[0]) == 'A') {
        if (a[1] == '+') {
            grade = 4.0;
        } else if (a[1] == '-') {
            grade = 3.7;
        } else {
            grade = 4.0;
        }
    } else if (toupper(a[0]) == 'B') {
        if (a[1] == '+') {
            grade = 3.3;
        } else if (a[1] == '-') {
            grade = 2.7;
        } else {
            grade = 3.0;
        }
    } else if (toupper(a[0]) == 'C') {
        if (a[1] == '+') {
            grade = 2.3;
        } else if (a[1] == '-') {
            grade = 1.7;
        } else {
            grade = 2.0;
        }
    } else if (toupper(a[0]) == 'D') {
        if (a[1] == '+') {
            grade = 1.3;
        } else {
            grade = 1.0;
        }
    } else {
        grade = 0.0;
    }
    return grade;
}

void gpaCalc(node **head, int count) {	//calculate the gpa of the transcript
    node *e;
    if (count == 0) {
        gpa_msg(0);
    } else {
        double gpa = 0.0;
        float totalCred = 0.0;
        for (e = *head; e != NULL; e = e->next) {
            gpa += (gradeConvert(e->grade) * (e->course).assignment);
            totalCred += (e->course).assignment;
        }
        gpa_msg(gpa / totalCred);
    }
}

