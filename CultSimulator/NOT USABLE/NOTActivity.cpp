#include "Person.h"
#include "Activity.h"

//Constructing one person activity.
Activity::Activity(int faith1, int insanity1) {
	_faith1 = faith1;
	_insanity1 = insanity1;

	_faith2 = 0; _insanity2 = 0;
}

//Constructing activity for two people.
Activity::Activity(int faith1, int insanity1, int faith2, int insanity2, list <unique_ptr<Person>>& lista) {
	_faith1 = faith1;
	_insanity1 = insanity1;

	_faith2 = faith2; 
	_insanity2 = insanity2;
}

//Destructor
Activity::~Activity() {}

//get random member.
Person& Activity::GetMemberFromList(list <unique_ptr<Person>>& lista) {
	int which = rand() % lista.size();
	for (auto& person : lista) {
		return *person;
	}
}