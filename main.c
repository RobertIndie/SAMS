#include "include/header.h"

void test()
{
    StudentFactory* factory = new_StudentFactory();
    DataBase* database = new_DataBase();
    CommandRunner* commandRunner = new_CommandRunner(database,factory);
    Student* stu1 = factory->createStudent(10001);
    Student* stu2 = factory->createStudent(10046);
    Student* stu3 = factory->createStudent(10078);
    Student* stu4 = factory->createStudent(10055);
    Student* stu5 = factory->createStudent(10082);
    database->add(database,stu1);
    database->add(database,stu2);
    database->add(database,stu3);
    database->add(database,stu4);
    database->add(database,stu5);
    commandRunner->list(commandRunner);
    Student** sortResult = database->sort(database,ID);
    printf("sort\n");
    for(int i=0;i<database->count;i++){
        printf("%d\n",(*(sortResult+i))->id);
    }
}

int main(int argc,char *argv[])
{
    ParseCommand(argc,argv);
    test();
}