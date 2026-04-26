#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
protected:
    int id;
    std::string name;
public:
    Person(int id, std::string name);
    virtual ~Person();
    
    int getId() const;
    std::string getName() const;

    virtual void display() const = 0; 
};

#endif