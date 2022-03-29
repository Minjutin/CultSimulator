#pragma once
#include <string>
#include <list>
#include <iostream>
#include <memory>
#include <time.h>

using namespace std;

class Person;
class Activity {

private:

	int _faith1;
	int _insanity1;
	int _faith2;
	int _insanity2;

public:
	//constructor for activity with one cult member.
	Activity(int faith1, int insanity1);

	//constructor for activity with two cult members.
	Activity(int faith1, int insanity1, int faith2, int insanity2, list <unique_ptr<Person>>& lista);

	//Destructor??
	~Activity();

	//return member.
	Person& GetMemberFromList(list <unique_ptr<Person>>& lista);

};