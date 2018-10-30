#include "include/header.h"
#include <stdlib.h>

char** divide_command(char* command, size_t* count)
{
	*count = 0;
	char* p = command;
	int canAddCount = 1;
	while (*p != '\0') {
		if (*p != ' ') {
			if (canAddCount) {
				(*count)++;
				canAddCount = 0;
			}
		}
		else {
			canAddCount = 1;
		}
		p++;
	}
	char** output = (char**)malloc(sizeof(char*)*(*count));
	int i = 0;
	int canAddP = 1;
	p = command;
	while (*p != '\0') {
		if (*p != ' ') {
			if (canAddP) {
				*(output + i) = p;
				i++;
				canAddP = 0;
			}
		}
		else {
			canAddP = 1;
			*p = '\0';
		}
		p++;
	}
	return output;
}

char* copy_str(char* dest, char* src) {
	if (dest != NULL) {
		free(dest);
		dest = NULL;
	}
	dest = (char*)malloc(sizeof(char)*strlen(src));
	strcpy(dest, src);
	return dest;
}

void ParseCommand(int argc,char **argv)
{
	StudentFactory* factory = new_StudentFactory();
	DataBase* database = new_DataBase();
	CommandRunner* commandRunner = new_CommandRunner(database, factory);
	char help_formatter[] = \
		"This Student-Achievement-Management-System is open source under GPLv2.0.\n\
Author: AaronRobert \n";
    printf("%s",help_formatter);
	char command[100];
	int exit_flag = 0;
	while (!exit_flag) {
		size_t count;
		printf(">>> ");
		scanf("%[^\n]", command);
		getchar();
		char** paraList = divide_command(command, &count);
#define PARSE_COMMAND(command,exp,minCount) if (!strcmp(*paraList, (command))) {\
		if(count-1<minCount){ERROR;printf("Too few arguments.\n");THROW;}\
		(exp);isCommandValid = 1;continue;}
		if (!setjmp(ex_stack[++ex_pointer].buf))
		{
			int isCommandValid = 0;
			PARSE_COMMAND("add", commandRunner->add(commandRunner, paraList + 1, count - 1),0);
			PARSE_COMMAND("help", commandRunner->help(),0);
			PARSE_COMMAND("list", commandRunner->list(commandRunner),0);
			PARSE_COMMAND("exit", exit_flag = 1,0);
			PARSE_COMMAND("sort", commandRunner->sort(commandRunner, *(paraList + 1)) ,1);
			PARSE_COMMAND("remove", commandRunner->remove(commandRunner, paraList + 1, count - 1),1);
			PARSE_COMMAND("edit", commandRunner->edit(commandRunner, paraList + 1, count - 1),1);
			if (!isCommandValid) 
			{
				ERROR;
				printf("%s: command not found.\n", *paraList);
				THROW;
			}
		}
		else {
			ex_pointer--;
		}
#undef PARSE_COMMAND
	}
}

Student* edit_stu(Student* stu, char** para, size_t para_count)
{
	char** p = para;
	while (para_count) {
#define NEXT para_count--;if (!para_count)break;p++;
#define PARSE_COMMAND(commandName,var,convert) if (!strcmp(*p, (commandName))) {NEXT (var) = (convert);NEXT continue;}
		PARSE_COMMAND("id", stu->id, atoi(*p));
		PARSE_COMMAND("name", stu->name, copy_str(stu->name, *p));
		PARSE_COMMAND("math", stu->math_score, atof(*p));
		PARSE_COMMAND("english", stu->english_score, atoi(*p));
		PARSE_COMMAND("computer", stu->computer_score, atoi(*p));
#undef PARSE_COMMAND
		//Unknown property
		ERROR;
		printf("[ERROR] Can not find property %s\n", *p);
		free(stu);
		stu = NULL;
		THROW;
		break;
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
"\thelp | print help message\n\
\tadd [{id,name,math,english,computer} (value)] | Add student message\n\
\tlist | list all students' message\n\
\tsort (property) | sort by property and print students message list\n\
\tremove {(id=0)} | remove student\n\
\tedit (id) {(property) (value)} | edit student\n\
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
	if (sortFlag == -1)
	{
		ERROR;
		printf("Invalid sort flag: %s\n", sortProperty);
		THROW;
	}
	Student** result = this->database->sort(this->database, sortFlag);
	printf("Sorted result:\n");
	printf("ID\tNAME\tMATH SCORE\tENGLISH SCORE\tCOMPUTER SCORE\n");
	for (int i = 0; i < this->database->count; i++) {
		Student* p = *(result + i);
		printf("%d\t%s\t%.2lf\t%.2lf\t%.2lf\n", p->id, p->name, p->math_score, p->english_score, p->computer_score);
	}
	if (!result) 
	{
		free(result);
		result = NULL;
	}
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
	if (count < 1)
	{
		ERROR;
		printf("Not para found.\n");
		THROW;
	}
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

#ifdef DEBUG
void Command_UnitTest() {
	char* str = "add 10001 computer 100";
	size_t count;
	char** result = divide_command(str, &count);
	for (int i = 0; i < count; i++)
		printf("%s\n", *(result + i));
}
#endif
