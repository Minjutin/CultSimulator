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
		int _faith;
		int _insanity;

	public:
		//constructor for activity with one cult member.
		Activity(Person& person1, int faith1, int insanity1);

		//constructor for activity with two cult members.
		Activity(Person& person1, int faith1, int insanity1, Person& person2, int faith2, int insanity2, list <unique_ptr<Person>>& lista);