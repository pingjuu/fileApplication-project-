#include "person.h"
//struct를 또다른 struct에 삽입
void person::operator=(const person &other){
        memcpy(this->name, other.name, strlen(this->name)+1);
        memcpy(this->address, other.address, strlen(this->address)+1);
        this->age = other.age;
        this->haknum = other.haknum;
    }