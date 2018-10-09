#include "include/header.h"
#include <stdlib.h>

void ParseCommand(int argc,char **argv)
{
	char help_formatter[] = \
		"This Student-Achievement-Management-System is open source under GPLv2.0.\n\
Author: AaronRobert \n";

    printf("%s",help_formatter);
}

Student* edit_stu(Student* stu, char** para, size_t para_count)
{
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
	return stu;
}

void CommandRunner_add(CommandRunner* this,char** para, size_t para_count)
{
	Student* stu = this->studentFactory->createStudent(rand());
	edit_stu(stu, para, para_count);
	this->database->add(this->database, stu);
}

void CommandRunner_help()
{
	char command_help[] = \
"\tadd [{id,name,math,english,computer} (value)] | Add student message\n\
\tlist | list all students' message\n\
";

	printf("%s", command_help);
}

void CommandRunner_list(CommandRunner* this)
{
    Student* p = this->database->data;
    printf("total:%d:\n",this->database->count);
	printf("ID\tNAME\tMATH SCORE\tENGLISH SCORE\tCOMPUTER SCORE\n");
    for(size_t i=0;i<this->database->count;i++){
		printf("%d\t%s\t%.2lf\t%.2lf\t%.2lf\n", p->id, p->name, p->math_score, p->english_score, p->computer_score);
        p = p->next;
    }
}

void CommandRunner_sort(CommandRunner* this,char* sortProperty)
{
	int sortFlag = -1;
#define CHECK_FLAG(propertyName,flag) if(!strcmp(sortProperty,(propertyName))){sortFlag = flag;}
	CHECK_FLAG("id", 0);
	CHECK_FLAG("name", 1);
	CHECK_FLAG("math", 2);
	CHECK_FLAG("english", 3);
	CHECK_FLAG("computer", 4);
	if (sortFlag == -1)return;//TODO:ERROR
	this->database->sort(this->database, sortFlag);
}

void CommandRunner_remove(CommandRunner* this,char** idList , size_t count)
{
	char** p = idList;
	while (count) {
		int id = atoi(*p);
		this->database->remove(this->database, id);
		printf("Remove student:%d\n", id);
		p++;
		count--;
	}
}

void CommandRunner_edit(CommandRunner* this, char** para, size_t count) 
{
	if (count < 1)return;//TODO:ERROR
	Student* stu = this->database->get(this->database, atoi(*para));
	para++;
	edit_stu(stu, para, count - 1);
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
    product->list = CommandRunner_list;
	product->add = CommandRunner_add;
	product->help = CommandRunner_help;
	product->sort = CommandRunner_sort;
	product->remove = CommandRunner_remove;
	product->edit = CommandRunner_edit;
    return product;
}
