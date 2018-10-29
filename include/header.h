#ifndef HEADER
#define HEADER
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <stdlib.h>

//////////////////////////
//Macro list
//#define INSERT_BY_ID_ORDER
#define DEBUG
/////////////////////////

#ifdef DEBUG
void Command_UnitTest();
#endif

typedef struct exception
{
	jmp_buf buf;
}Exception;

Exception ex_stack[256];
extern int ex_pointer;
#define ERROR printf("[Error]")
#define EXCEPTION longjmp(ex_stack[ex_pointer].buf, 0)

void ParseCommand(int argc,char **argv);

typedef struct command_runner
{
    struct data_base* database;
    struct student_factory* studentFactory;
    void (*add)(struct command_runner*,char**,size_t);//add id 10001 name robert math 100 english 100 computer 100. if value is invalid,then value is set to 0.
    void (*help)();//print help message
    void (*list)(struct command_runner*);//list all students message
    void (*sort)(struct command_runner*,char*);//sort by property and print students message list. sort math
    void (*remove)(struct command_runner*,char**,size_t);//remove one or more students message with id. remove 10001 .if id is invalid ,then remove the student whose id is 0.
    void (*edit)(struct command_runner*,char**,size_t);//edit student message serarched by id. edit 10001 math 200 english 150
}CommandRunner;
#define ID 0
#define NAME 1
#define MATH_SCORE 2
#define ENGLISH_SCORE 3
#define COMPUTER_SCORE 4
typedef struct student_message
{
    int id;
    char* name;
    double math_score;
    double english_score;
    double computer_score;
    struct student_message* next;
    struct student_message* prev;
}Student;

typedef struct student_factory
{
    Student* (*createStudent)(int id);
}StudentFactory;

typedef struct data_base
{
    Student* data;//link list
    size_t count;//do not change this var outside the database.c
    void (*add)(struct data_base*,Student*);//add a student message to the database.tow option:add by id order or add to the last node
    Student** (*sort)(struct data_base*,int);//return a sorted link list
    void (*remove)(struct data_base*,int);//remove a student by id
    Student* (*get)(struct data_base*,int);//get a student pointer by id.
}DataBase;

CommandRunner* new_CommandRunner(DataBase*,StudentFactory*);
StudentFactory* new_StudentFactory();
DataBase* new_DataBase();
#endif
