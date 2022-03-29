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
	if (_faith+amount>100) 
		_faith = 100;
	else
		_faith += amount;
}

void Person::AddInsanity(int amount) {
	if (_insanity + amount > 10)
		_insanity == 10;
	else if (_insanity + amount < 0)
		_insanity == 0;
	else
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