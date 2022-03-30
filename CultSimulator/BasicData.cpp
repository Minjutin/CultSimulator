#include "BasicData.h";
#include "Person.h";

//Add to list / delete from list.
namespace BasicData {

	void BasicData::AddPerson(list <unique_ptr<Person>>& lista, string name, int faith, int insanity, string role) {
		lista.push_back(make_unique<Person>(name, faith, insanity, role));
	}

	void BasicData::DeletePerson(unique_ptr<Person>& person, list <unique_ptr<Person>>& lista) {
		for (auto& member : lista) {
			if (member==person)
			{
				lista.remove(member);
				break;
			}
		}
	}

	//void AddActivities(list <unique_ptr<Person>>& lista) {

	//}
}
