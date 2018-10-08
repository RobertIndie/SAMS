#include "include/header.h"

Student* createStudent(int id)
{
    Student* product = (Student*)malloc(sizeof(Student));
    if(!product){
        printf("[ERROR]Out of memory");
        return NULL;
    }
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
    if(!product){
        printf("[ERROR]Out of memory") ;
        return NULL;
    }
    product->createStudent = createStudent;
    return product;
}

Student* getByIndex(DataBase* this,size_t index)
{
    Student* p = this->data;
    for(int i=0;i<index;i++)p=p->next;
    return p;
}

void DataBase_add(DataBase* this,Student* stu)
{
    if(!this->count){
        this->data=stu;
    }
    else{
        Student* lastStu = getByIndex(this,this->count-1);
        lastStu->next = stu;
        stu->prev = lastStu;
    }
    this->count++;
}

//if a>b return 2
//if a=b return 1
//if a<b return 0
//a>=b usage: if(compare(a,b,compareFlag))
//a<=b usage: if(compare(b,a,compareFlag))
int compare(Student* a,Student* b,int compareFlag)
{
    return a->id>=b->id?(a->id==b->id?1:2):0;
}

void quicksort(Student** list, int low, int high,int compareFlag)
{
    int i=low;
    int j=high;
    Student* temp=*(list+i);
    if(low>high){
        return;
    }
    while(i<j){
        while(compare(*(list+j),temp,compareFlag) && i<j){
            j--;
        }
        *(list+i) = *(list+j);
        while(compare(temp,*(list+i),compareFlag) && i<j){
            i++;
        }
        *(list+j) = *(list+i);
    }
    *(list+i) = temp;
    quicksort(list,low,i-1,compareFlag);
    quicksort(list,j+1,high,compareFlag);
}

//if count is zero,retunr NULL
//return result is a new memory.
Student** DataBase_sort(DataBase* this,int compareFlag)
{
    size_t count = this->count;
    if(!count)return NULL;
    Student** studentList = (Student**)malloc(sizeof(Student*)*count);//new memory
    Student* p=this->data;
    for(size_t i=0;i<count;i++){
        *(studentList+i)=p;
        p=p->next;
    }
    quicksort(studentList,0,this->count-1,compareFlag);
    return studentList;
}

DataBase* new_DataBase()
{
    DataBase* product = (DataBase*)malloc(sizeof(DataBase));
    product->count = 0;
    product->add = DataBase_add;
    product->sort = DataBase_sort;
    return product;
}
