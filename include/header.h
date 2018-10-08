#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "setjmp.h"

void ParseCommand(int argc,char **argv);

typedef struct command_runner
{
    struct data_base* database;
    struct student_factory* studentFactory;
    void (*add)(char**,size_t);//add id 10001 name robert math 100 english 100 computer 100
    void (*help)();//print help message
    void (*list)(struct command_runner*);//list all students message
    void (*sort)(char*);//sort by property and print stuedents message list. sort math
    void (*remove)(char**,size_t);//remove one or more students message with id. remove 10001
    void (*edit)(char**,size_t);//edit student message serarched by id. edit 10001 math 200 english 150
}CommandRunner;

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
    void (*add)(struct data_base*,Student*);
    Student** (*sort)(struct data_base*,int);//return a sorted link list
    void (*remove)(struct data_base*,int);//remove a student by id
    Student* (*get)(struct data_base*,int);//get a student pointer by id.
}DataBase;

CommandRunner* new_CommandRunner(DataBase*,StudentFactory*);
StudentFactory* new_StudentFactory();
DataBase* new_DataBase();
