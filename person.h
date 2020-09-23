#pragma once
#include <iostream>
#include <string.h>

struct person{
    char name[20];
    char address[30];
    //std::string name;
    //std::string address;
    unsigned int age;
    unsigned int haknum;
    
    void operator=(const person &other);
};