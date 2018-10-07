#include <malloc.h>
#include <stdio.h>
#include <string.h>

void ParseCommand(int argc,char **argv);

typedef struct command_runner
{
    void (*add)(char**);//add id 10001 name robert math 100 chinese 100 english 100
    void (*help)();//print help message
    void (*list)();//list all students message
    void (*sort)();//sort and print stuedents message list
    void (*remove)(char**);//remove one or more students message with id. remove 10001
    void (*edit)(char**);//edit student message serarched by id. edit 10001 math 200 english 150
}CommandRunner;

CommandRunner* new_CommandRunner();