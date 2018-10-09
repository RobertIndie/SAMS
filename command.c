#include "include/header.h"
#include <stdlib.h>

void ParseCommand(int argc,char **argv)
{
    char help_formatter[] = \
    "This Student-Achievement-Management-System is open source under GPLv2.0.\n\
Author: AaronRobert \n\
    ";

    printf("%s",help_formatter);
}

void CommandRunner_add(CommandRunner* this,char** para, size_t para_count)
{
	Student* stu = this->studentFactory->createStudent(rand());
	char** p = para;
	while (para_count) {
#define NEXT para_count--;if (!para_count)break;p++;
#define PARSE_COMMAND(commandName,var,convert) if (!strcmp(*p, (commandName))) {NEXT (var) = (convert);NEXT continue;}
		PARSE_COMMAND("id", stu->id, atoi(*p));
		PARSE_COMMAND("name", stu->name, *p);
		PARSE_COMMAND("math", stu->math_score, atof(*p));
		PARSE_COMMAND("english", stu->english_score, atoi(*p));
		PARSE_COMMAND("computer", stu->computer_score, atoi(*p));
	}
	this->database->add(this->database, stu);
}

void CommandRunner_help()
{
	char command_help[] = \
		"\tadd [{id,name,math,english,computer} (value)] | Add student message\n";

	printf("%s", command_help);
}

void CommandRunner_sort(char* sortProperty)
{
	//if()
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
	product->add = CommandRunner_add;
	product->help = CommandRunner_help;
    return product;
}
