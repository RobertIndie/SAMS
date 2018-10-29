#include "include/header.h"

int ex_pointer = -1;

void test()
{
	if (!setjmp(ex_stack[++ex_pointer].buf))
	{
		StudentFactory* factory = new_StudentFactory();
		DataBase* database = new_DataBase();
		CommandRunner* commandRunner = new_CommandRunner(database, factory);
		commandRunner->help();
		Student* stu1 = factory->createStudent(10001);
		stu1->computer_score = 100;
		Student* stu2 = factory->createStudent(10096);
		stu2->computer_score = 60;
		Student* stu3 = factory->createStudent(10078);
		stu3->computer_score = 56;
		Student* stu4 = factory->createStudent(10065);
		stu4->computer_score = 94;
		Student* stu5 = factory->createStudent(10022);
		database->add(database, stu1);
		database->add(database, stu2);
		database->add(database, stu3);
		database->add(database, stu4);
		database->add(database, stu5);
		char* removeIDList[] = {
			"10065","10055"
		};
		commandRunner->remove(commandRunner, removeIDList, 2);
		char* addCommand[] = {
			"id","10010"
		};
		commandRunner->add(commandRunner, addCommand, 2);
		char* editCommand[] = {
			"10001","english","100"
		};
		commandRunner->edit(commandRunner, editCommand, 3);
		commandRunner->list(commandRunner);
		Student** sortResult = database->sort(database, COMPUTER_SCORE);
		printf("sort\n");
		for (int i = 0; i < database->count; i++) {
			Student* p = *(sortResult + i);
			printf("%d\t%s\t%.2lf\t%.2lf\t%.2lf\n", p->id, p->name, p->math_score, p->english_score, p->computer_score);
		}
	}
	else {
		ex_pointer--;
	}
}

int main(int argc,char *argv[])
{
	Command_UnitTest();
	test();
    ParseCommand(argc,argv);
}
