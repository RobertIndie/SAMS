#include "include/header.h"

void ParseCommand(int argc,char **argv)
{
    char help_formatter[] = \
    "This Student-Achievement-Management-System is open source under GPLv2.0.\n\
Author: AaronRobert \n\
    ";

    printf("%s",help_formatter);
}

void list(CommandRunner* this)
{
    Student* p = this->database->data;
    printf("List(count:%d):\n",this->database->count);
    for(size_t i=0;i<this->database->count;i++){
        printf("%d\n",p->id);
        p = p->next;
    }
}

CommandRunner* new_CommandRunner(DataBase* database,StudentFactory* studentFactory)
{
    CommandRunner* product = (CommandRunner*)malloc(sizeof(CommandRunner));
    if(!product){
        printf("[ERROR]Out of memory");
        return NULL;
    }
    product->database = database;
    product->studentFactory = studentFactory;
    product->list = list;
    return product;
}
