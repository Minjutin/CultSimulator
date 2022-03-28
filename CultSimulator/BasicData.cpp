#include "BasicData.h";
#include "Person.h";

//Add to list / delete from list.
namespace BasicData {


	void BasicData::AddPerson(list <unique_ptr<Person>>& lista, string name, int faith, int insanity, string role) {
		lista.push_back(make_unique<Person>(name, faith, insanity, role));
	}

	void BasicData::DeletePerson(Person& person, list <unique_ptr<Person>>& lista) {
		for (auto& member : lista) {
			if (member->GetName() == person.GetName())
			{
				lista.remove(member);
				break;
			}
		}
	}
}
