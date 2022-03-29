#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <time.h> 
#include <conio.h>

#include "Person.h";
#include "BasicData.h";

using namespace std;

//variables
int membercount;
int power;
string cultName;
string godName;

//lists
list <unique_ptr<Person>> memberList;
list <unique_ptr<Person>> potentialList;
list <unique_ptr<Person>> enemyList;



void CreateCult();
void PrintCult();
void GoNext();
void TestCult();
void DayCycleCheckers();
void DayCycleActivities();

int main()
{
    //Start
    //CreateCult();
    //GoNext();
    TestCult();
    PrintCult();
    GoNext();

    //Day Cycle
    while (true) {
        DayCycleCheckers();
        DayCycleActivities();
        GoNext();
        PrintCult();
        GoNext();
    }

}

//These checks if anything must be changed inside the cult.
void DayCycleCheckers() {
    //check if faith is more than 60.
    for (auto& member : memberList) {
        if (member->GetRole() == "New member" && member->GetFaith() > 59) {
            cout << member->GetName() + " has been promoted to honorary member.\n";
            member->ChangeRole("Honorary member");
        }
    }

    //check if someone must be thrown out.
    for (auto& member : memberList) {
        if (member->GetFaith() < 15) {
            cout << member->GetName() + " has resign the cult and is now a public enemy.\n";
            BasicData::AddPerson(enemyList, member->GetName(), member->GetFaith(), member->GetInsanity(), "Enemy");
            memberList.remove(member);
            break;
        }
    }

    //check if there is no leader.
    bool noLeader = true;
    for (auto& member : memberList) {
        if (member->GetRole() == "Leader") {
            noLeader = false;
            break;
        }
    }
    //if there is no leader, get random member with Honorary member - role and make them a leader.
    //EDIT now it only takes the first member.
    if (noLeader) {
        for (auto& member : memberList) {
            if (member->GetRole() == "Honorary member") {
                cout << "Since the previous leader is no longer among us, " + member->GetName() + " is now the new leader.\n";
                member->ChangeRole("Leader");
                break;
            }
        }
    }
}

void DayCycleActivities() {
    cout << "\nDaily Activities:\n\n";
    for (auto& member : memberList) {
  
        cout << member->GetName() << " is doing nothing.\n";
        
    }
}

//Creating cult.
void CreateCult() {
    power = 0;
    membercount = 0;

    cout << "Welcome to the Cult Simulator! Tell me the name of your cult:" << endl;
    cin >> cultName;
    cout << "\nNext, tell me the name of your god:\n";
    cin >> godName;
    
    //how many members
    int howmany = 0;
    cout << "\nTime to add some members. Tell me, how many members will there be (4-10):\n";
    cin >> howmany;
    cout << "\nExcellent! Now you can add members by writing their names.\n";

    //add leader.
    cout << "At first, choose your leader:\n";
    string leaderName;
    cin >> leaderName;

    BasicData::AddPerson(memberList, leaderName, 80, 5, "Leader");

    //add other members.
    for (int i = 1; i < howmany; i++) {
        string memberName = "";
        cout << "Add member:\n";
        cin >> memberName;
        BasicData::AddPerson(memberList, memberName, 30, 0, "New member");
    }
    cout << "The cult is now created.\n";
}

//TEST CULT
void TestCult() {
    cultName = "Erkin kultti";
    godName = "Erkki";
    BasicData::AddPerson(memberList, "Jaska", 80, 5, "New member");
    BasicData::AddPerson(memberList, "Sari", 30, 0, "New member");
    BasicData::AddPerson(memberList, "Hilda", 70, 0, "New member");
    BasicData::AddPerson(memberList, "Masi", 9, 0, "New member");
}

//Prints cult data.
void PrintCult() {
    cout << "Cult members:\n\n";
    for (auto& member : memberList) {
        cout << member->GetRole() + ": "+ member->GetName() + ", faith " + to_string(member->GetFaith()) + ", insanity " + to_string(member->GetInsanity()) + ". \n";
    }
}

void GoNext() {
    string empty = "";
    cout << "\nWrite C to Continue.\n";
    cin >> empty;
    system("cls");
}