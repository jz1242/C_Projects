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
            Course temp = data[ind];
            for(unsigned j = 0; j < strlen(temp.title); j++){
                if(temp.title[j] == '\n'){
                    temp.title[j] = '\0';
                }
            }

            printf("%s.%03d.%03d %0.1f %s\n", temp.div, temp.dep,
                    temp.num, temp.assignment, temp.title);

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
            Course temp = data[ind];
            for(unsigned j = 0; j < strlen(temp.title); j++){
                if(temp.title[j] == '\n'){
                    temp.title[j] = '\0';
                }
            }

            printf("%s.%03d.%03d %0.1f %s\n", temp.div, temp.dep,
                    temp.num, temp.assignment, temp.title);
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
                    fgets(inp, 10, stdin);
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
           // printTranscript(&head, count);

            transcript_updated_msg();
            // printf("%s.%d.%d %0.1f %s\n", data[ind].div, data[ind].dep, data[ind].num, data[ind].assignment, data[ind].title);

            menu_prompt();
        } else if (menu == '6') {
            if(count > 0){
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
            }
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

