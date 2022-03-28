#pragma once
#include <string>
#include <list>
#include <iostream>
#include <memory>
#include <time.h> 

using namespace std;

class Person {
	
private:
	string _name;
	int _faith;
	int _insanity;
	string _role;

public:
	//roles enum.
	enum Role {Leader, HonMember, NewMember, Potential, Enemy};

	//Constructor
	Person(string name, int faith, int insanity, string role);

	//Destructor
	~Person();

	//ADDERS
	void AddFaith(int amount);
	void AddInsanity(int amount);

	//Change role
	void ChangeRole(string newRole);

	//GETTERS
	string GetName();
	int GetFaith();
	int GetInsanity();
	string GetRole();
};