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

Course *data;
Course createCourse(char *str);
node* Create(Course course, char* year, char* grade);
void InsertAfter(node *e, Course course, char* year, char* grade);
void InsertHead(node **head, Course course, char* year, char* grade);
void DeleteAfter(node *e);
void DeleteHead(node **head);
int checkValidSem(char *a);

Course createCourse(char *str) {
    Course course;
    strncpy(course.div, str, 2);
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
    return course;

}
void printCourses(int num) {
    for (int i = 0; i < num; i++) {
        printf("%s.%d.%d %0.1f %s\n", data[i].div, data[i].dep, data[i].num,
                data[i].assignment, data[i].title);
    }

}
int checkCase(char* a, char* b) {
    int equal = 1;
    // printf("%d %d \n", strlen(a), strlen(b));
    for (unsigned i = 0; i < strlen(b); i++) {
        if (toupper(a[i]) != toupper(b[i])) {
            equal = 0;
        }
    }
    return equal;
}
int compareCourse(Course a, Course b) {
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
int searchCourse(int num, char *str) {
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

node* Create(Course course, char* year, char* grade) {
    node *e = malloc(sizeof(node));
    e->next = NULL;
    e->course = course;
    strcpy(e->year, year);
    strcpy(e->grade, grade);
    return e;
}

void InsertAfter(node *e, Course course, char* year, char* grade) {
    node *newE = Create(course, year, grade);
    newE->next = e->next;
    e->next = newE;
}

void InsertHead(node **head, Course course, char* year, char* grade) {
    node *e = Create(course, year, grade);
    e->next = *head;
    *head = e;
}

void DeleteAfter(node *e) {
    node* eNext = e->next;
    if (!eNext) {
        return;
    }
    e->next = e->next->next;
    free(eNext);
}
void DeleteHead(node **head) {
    node* e = (*head);
    *head = e->next;
    free(e);
}

int searchTranscript(node **head, Course course) {
    node *e;
    int exist = 0;
    bool run = false;
    for (e = *head; e != NULL; e = e->next) {
        if (compareCourse(course, e->course)) {
            exist++;
        }
    }
    if (exist == 1) {
        if (compareCourse(course, (*head)->course)) {
            DeleteHead(*(&head));
        }

        else {
            for (e = *head; e->next != NULL; e = e->next) {

                if (compareCourse(course, (e->next)->course)) {
                    DeleteAfter(e);
                    break;
                }
            }
        }
    } else if (exist > 1) {
            int valid2 = 0;
            char inp[7];
            while(valid2 == 0){
                semester_prompt();
                fgets(inp, 7, stdin);
                valid2 = checkValidSem(inp);
                if(!valid2){
                    invalid_input_msg();
                }
            }
            inp[5] = toupper(inp[5]);
            if (compareCourse(course, (*head)->course)) {
                if(strcmp((*head)->year, inp) == 0){
                    DeleteHead(*(&head));
                }
                else{
                    run = true;
                }

            }
            if(run){
                for(e = *head; e->next !=NULL; e = e->next){
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

int searchTranscriptNoDel(node **head, Course course){
    node *e;
    int exist = 0;
    for (e = *head; e != NULL; e = e->next) {
        if (compareCourse(course, e->course)) {
            exist++;
        }
    }
    return exist;
}


void printTranscript(node **head, int count) {
    node *e;
    if (count <= 0) {
        empty_transcript_msg();
    } else {
        for (e = *head; e != NULL; e = e->next) {
            printf("%s %s %s.%d.%d %0.1f %s \n", e->year, e->grade,
                    (e->course).div, (e->course).dep, (e->course).num,
                    (e->course).assignment, (e->course).title);
        }
    }
}

void printCourseData(node **head, Course course) {
    node *e;
    for (e = *head; e != NULL; e = e->next) {
        if (compareCourse(course,e->course)) {
            printf("%s %s\n", e->year, e->grade);
        }
    }
}

int checkValidCourse(char *a){
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

int checkValidTitle(char *a){
    if(strlen(a) > 33){
        return 0;
    }
    return 1;
}

int checkValidCred(char *a){
    if(strlen(a) > 4){
        return 0;
    }
    if(a[1] != '.'){

        return 0;
    }
    return 1;
}

int checkValidSem(char *a){
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

int checkValidGrade(char *a){
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
int checkDup(node **head, Course course, char *sem){
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
double gradeConvert(char *a) {
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

void gpaCalc(node **head, int count) {
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

int main(int argc, char* argv[]) {
    FILE *input = fopen(argv[1], "r");      //get file and take user inpt
    if (argc == 1) {
        return 1;  // exit program because no command line argument present
    }
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
        // printf("%s\n", data[index].title);
        //printf("%d %d\n", size, index);
        index++;
    }
    // printf("%d", index);
    fclose(input);
    char menu;
    menu_prompt();
    node *head = NULL;
    node *e;
    // char inpz[10] = "1999";
    //char impzf[10] = "F";

    // printf("%d \n", atoi(strncpy(impzf, inpz, 4)));
    // printf("%d %d\n",'F', impzf);
    int count = 0;
    while (menu != 'q') {     //loop to keep showing menu options
        scanf("%c", &menu);
        menu = tolower(menu);
        if (menu == '1') {
            printCourses(index);
            menu_prompt();
        } else if (menu == '2') {
            char str[100];
            int ind = -1;
            int valid = 0;
            while (ind == -1) {
                course_prompt();
                int throw;
                scanf("%d\n", &throw);
                fgets(str, 100, stdin);
                valid = checkValidCourse(str);
                if(valid){
                    ind = searchCourse(index, str);
                }
                else{
                    invalid_input_msg();
                }
            }

            printf("%s.%d.%d %0.1f %s\n", data[ind].div, data[ind].dep,
                    data[ind].num, data[ind].assignment, data[ind].title);

            //printf("%s\n", str);
            menu_prompt();

        } else if (menu == '3') {
            char str[100];
            int ind = -1;
            int valid = 0;
            int valid2 = 0;
            while (ind == -1) {
                course_prompt();
                int throw;
                scanf("%d\n", &throw);
                fgets(str, 100, stdin);
                valid = checkValidCourse(str);
                if(valid){
                    ind = searchCourse(index, str);
                }
                else{
                    invalid_input_msg();
                }
            }
            char inp[35];
            while(valid2 == 0){
                new_title_prompt();
                fgets(inp, 100, stdin);
                valid2 = checkValidTitle(inp);
                if(valid2){
                    strcpy(data[ind].title, inp);
                }
                else{
                    invalid_input_msg();
                }
            }
            if(count > 0){
                for(e = head; e != NULL; e = e -> next){
                    strcpy(e->course.title, inp);
                }
            }
            course_updated_msg();
            // printf("%s.%d.%d %0.1f %s\n", data[ind].div, data[ind].dep, data[ind].num, data[ind].assignment, data[ind].title);

            menu_prompt();
        } else if (menu == '4') {
            course_prompt();
            char str[100];
            int ind = -1;
            int valid = 0;
            int valid2 = 0;
            while (ind == -1) {
                int throw;
                scanf("%d\n", &throw);
                fgets(str, 100, stdin);
                valid = checkValidCourse(str);
                if(valid){
                    ind = searchCourse(index, str);
                }
                else{
                    invalid_input_msg();
                }
            }
            while(valid2 == 0){
                char cred[5];
                new_credit_prompt();
                fgets(cred, 100, stdin);
                valid2 = checkValidCred(cred);
                if(valid2){
                    data[ind].assignment = atof(cred);
                }
                else{
                    invalid_input_msg();
                }
            }

            printf("%s.%d.%d %0.1f %s\n", data[ind].div, data[ind].dep,
                    data[ind].num, data[ind].assignment, data[ind].title);
            course_updated_msg();
            menu_prompt();

        } else if (menu == '5') {
            char str[100];
            char inp[8];
            char inp2[4];
            int ind = -1;
            int valid4 = 1;
            while(valid4 == 1){
                ind = -1;
                int valid = 0;
                int valid2 = 0;
                int valid3 = 0;
                while (ind == -1) {
                    course_prompt();
                    int throw;
                    scanf("%d\n", &throw);
                    fgets(str, 100, stdin);
                    valid = checkValidCourse(str);
                    if(valid){
                        ind = searchCourse(index, str);
                    }
                    else{
                        invalid_input_msg();
                    }
                }


                while(valid2 == 0){
                    semester_prompt();
                    fgets(inp, 7, stdin);
                    valid2 = checkValidSem(inp);
                    if(!valid2){
                        invalid_input_msg();
                    }
                }
                inp[5] = toupper(inp[5]);
                while(valid3 == 0){
                    grade_prompt();
                    int throw2;
                    scanf("%d\n", &throw2);
                    fgets(inp2, 3, stdin);
                    valid3 = checkValidGrade(inp2);
                    if(!valid3){
                        invalid_input_msg();
                    }
                }

                valid4 = checkDup(&head, data[ind], inp);
                if(valid4 > 0){
                    duplicate_course_msg();
                }
            }
            char comp1[5];
            char comp2[5];
            strncpy(comp1, inp, 4);
            // strncpy(comp2, head->year, 4);
            if (!head) {
                head = Create(data[ind], inp, inp2);
            } else if (atoi(comp1) < atoi(strncpy(comp2, head->year, 4))) {
                InsertHead(&head, data[ind], inp, inp2);
            } else if (atoi(comp1) == atoi(strncpy(comp2, head->year, 4)) && toupper(inp[5]) >= toupper(head->year[5])) {
                InsertHead(&head, data[ind], inp, inp2);
            } else {

                for (e = head; e->next != NULL && atoi(comp1) >= atoi(strncpy(comp2, e->next->year,4)); e = e->next) {
                    if (toupper(inp[5]) >= toupper(e->next->year[5]) && atoi(comp1) == atoi(strncpy(comp2, e->next->year, 4))) {
                        break;
                    }

                }
                InsertAfter(e, data[ind], inp, inp2);

            }
            count++;
            //printf("%s", head->year);
            printTranscript(&head, count);

            course_updated_msg();
            // printf("%s.%d.%d %0.1f %s\n", data[ind].div, data[ind].dep, data[ind].num, data[ind].assignment, data[ind].title);

            menu_prompt();
        } else if (menu == '6') {
            int ind = -1;
            int exist = -1;
            int valid = 0;
            char str[100];
            while (ind == -1 || exist == 0) {
                course_prompt();
                int throw;
                scanf("%d\n", &throw);
                fgets(str, 100, stdin);
                valid = checkValidCourse(str);
                if(valid){
                    ind = searchCourse(index, str);
                }
                else{
                    invalid_input_msg();
                }
                if (ind != -1) {
                    exist = searchTranscript(&head, data[ind]);
                    if (exist == 0) {
                        course_not_taken_msg();
                    }
                    else{
                        count--;
                    }
                }

                //printTranscript(&head, count);


            }
            transcript_updated_msg();
            menu_prompt();
        } else if (menu == '7') {
            printTranscript(&head, count);
            menu_prompt();
        } else if (menu == '8') {
            if (count > 0) {
                int ind = -1;
                int exist = -1;
                int valid = 0;
                char str[100];
                while (ind == -1 || exist == 0) {
                    course_prompt();
                    int throw;
                    scanf("%d\n", &throw);
                    fgets(str, 100, stdin);
                    valid = checkValidCourse(str);
                    if(valid){
                        ind = searchCourse(index, str);
                    }
                    else{
                        invalid_input_msg();
                    }
                    if (ind != -1) {
                        exist = searchTranscriptNoDel(&head, data[ind]);
                        if (exist == 0) {
                            course_not_taken_msg();
                        }
                    }

                }
                printCourseData(&head, data[ind]);
            }
            menu_prompt();
        } else if (menu == '9') {
            gpaCalc(&head, count);
            menu_prompt();
        }

    }
    free(data);
    return 0;
}

