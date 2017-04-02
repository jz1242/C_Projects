/* File: hw5.c
 Homework 5, 600.120 Spring 2017 3/8

 Jason Zhang jzhan127 jzhan127@jhu.edu
 */

#ifndef METHODS_H_
#define METHODS_H_

typedef struct courseStruct{
    char div[3];
    int dep;
    int num;
    float assignment;
    char title[33];


} Course;

typedef struct nodeStruct{
    Course course;
    char year[7];
    char grade[3];
    struct nodeStruct *next;
} node;

Course *data;
Course createCourse(char *str);
node* Create(Course course, char* year, char* grade);
void InsertAfter(node *e, Course course, char* year, char* grade);
void InsertHead(node **head, Course course, char* year, char* grade);
void DeleteAfter(node *e);
void DeleteHead(node **head);
int checkValidSem(char *a);
void printCourses(int num);
int checkCase(char* a, char* b);
int compareCourse(Course a, Course b);
int searchCourse(int num, char *str);
int searchTranscript(node **head, Course course);
int searchTranscriptNoDel(node **head, Course course);
void printTranscript(node **head, int count);
void printCourseData(node **head, Course course);
int checkValidCourse(char *a);
int checkValidTitle(char *a);
int checkValidCred(char *a);
int checkValidGrade(char *a);
int checkDup(node **head, Course course, char *sem);
double gradeConvert(char *a);
void gpaCalc(node **head, int count);


#endif /* METHODS_H_ */
