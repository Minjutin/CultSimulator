#include "Person.h"

Person::Person(string name, int faith, int insanity, string role) {
	_name = name;
	_faith = faith;
	_insanity = insanity;
	_role = role;
}


//Destructor
Person::~Person() {}

//Adders
void Person::AddFaith(int amount) {
	_faith += amount;
}
void Person::AddInsanity(int amount) {
	_insanity += amount;
}

void Person::ChangeRole(string role) {
	_role = role;
}

//Getters
string Person::GetName() {
	return _name;
}
int Person::GetFaith() {
	return _faith;
}
int Person::GetInsanity() {
	return _insanity;
}
string Person::GetRole() {
	return _role;
}