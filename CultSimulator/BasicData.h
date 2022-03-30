#pragma once
#include <string>
#include <list>
#include <iostream>
#include <memory>
#include <time.h> 

using namespace std;
class Person;

namespace BasicData {

	//Useful list functions

	void AddPerson(list <unique_ptr<Person>>& lista, string name, int faith, int insanity, string role);

	void DeletePerson(unique_ptr<Person>& person, list <unique_ptr<Person>>& lista);

	//void AddActivities(list <unique_ptr<Person>>& lista);
}