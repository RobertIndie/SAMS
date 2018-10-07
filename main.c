#include "include/header.h"

void test()
{
    StudentFactory* factory = new_StudentFactory();
    Student* stu = factory->createStudent(10001);
    DataBase* database = new_DataBase();
    CommandRunner* commandRunner = new_CommandRunner(database,factory);
    database->add(database,stu);
    commandRunner->list(commandRunner);
}

int main(int argc,char *argv[])
{
    ParseCommand(argc,argv);
    test();
}