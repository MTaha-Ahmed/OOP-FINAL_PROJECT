#include "Person.h"

using namespace std;

Person::Person(int id, string name) {
    this->id = id;
    this->name = name;
}

Person::~Person() {}

int Person::getId() const { return id; }
string Person::getName() const { return name; }