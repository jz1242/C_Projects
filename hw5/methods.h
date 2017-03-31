/*
 * methods.h
 *
 *  Created on: Mar 28, 2017
 *      Author: JZ
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



#endif /* METHODS_H_ */
