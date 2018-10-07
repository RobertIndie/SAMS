#include <malloc.h>
#include <stdio.h>
#include <string.h>

void ParseCommand(int argc,char **argv);

typedef struct command_runner
{
    void (*add)(char**,int);//add id 10001 name robert math 100 english 100 computer 100
    void (*help)();//print help message
    void (*list)();//list all students message
    void (*sort)();//sort and print stuedents message list
    void (*remove)(char**,int);//remove one or more students message with id. remove 10001
    void (*edit)(char**,int);//edit student message serarched by id. edit 10001 math 200 english 150
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

CommandRunner* new_CommandRunner();
StudentFactory* new_StudentFactory();