#include "header.h"

Student* (*createStudent)(int id)
{
    Student* product = (Student*)malloc(sizeof(Student));
    if(!product)printf("[ERROR]Out of memory");
    product->id = id;
    product->name = NULL;
    product->math_score = 0.0;
    product->english_score = 0.0;
    product->computer_score = 0.0;
    product->next = NULL;
    product->prev = NULL;
    return product;
}

StudentFactory* new_StudentFactory()
{
    StudentFactory* product = (StudentFactory*)malloc(sizeof(StudentFactory));
    if(!product)printf("[ERROR]Out of memory");
    return product;
}

//Private
Student* getByIndex(DataBase* this,size_t index)
{
    Student* p = this->data;
    for(int i=0;i<index;i++)p=p->next;
    return p;
}

void DataBase_add(DataBase* this,Student* stu)
{
    if(!this->count)this->data=stu;
    else{
        Student* lastStu = getByIndex(this,this->count-1);
        lastStu->next = stu;
        stu->prev = lastStu;
        this->count++;
    }
}

DataBase* new_DataBase()
{
    DataBase* product = (DataBase*)malloc(sizeof(DataBase));
    product->count = 0;
    product->add = DataBase_add;
    return product;
}
