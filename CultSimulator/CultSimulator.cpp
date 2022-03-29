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

//peoplelists
list <unique_ptr<Person>> memberList;
list <unique_ptr<Person>> potentialList;
list <unique_ptr<Person>> enemyList;

void CreateCult();
void PrintCult();
void GoNext();
void TestCult();
void DayCycleCheckers();
void DayCycleActivities();

//namespace for cult activities
namespace Activities {

    //method for activiting lists.
    void valueMethod(int faith, int insanity, unique_ptr<Person>& member) {

        //print faith and insanity changes.
        cout << " (";
        if (faith > 0)
            cout << "faith +" << faith << " ";
        else if (faith < 0)
            cout << "faith " << faith << " ";
        if (insanity > 0)
            cout << "insanity +" << insanity;
        if (insanity < 0)
            cout << "insanity " << insanity;
        cout << ")\n";

        member->AddFaith(faith); member->AddInsanity(insanity);
    }

    void GoodActivity(unique_ptr<Person>& member) {
        int which = rand() % 5;
        switch (which) {
        case 0:
            cout << member->GetName() + " is trying to find new followers.";
            valueMethod(2, 0, member);
            break;
        case 1:
            cout << member->GetName() + " prays for 8 hours.";
            valueMethod(3, 2, member);
            break;
        case 2:
            cout << member->GetName() + " reads the cult scripture.";
            valueMethod(1, 1, member);
            break;
        case 3:
            cout << member->GetName() + " makes threatening calls to the previous cult members.";
            valueMethod(1, 2, member);
            break;
        case 4:
            cout << member->GetName() + " writes a religious opinion to a cooking web site.";
            valueMethod(1, 1, member);
            break;
        }

    }

    void NeutralActivity(unique_ptr<Person>& member) {
        int which = rand() % 3;
        switch (which) {
        case 0:
            cout << member->GetName() + " has a coffee break.";
            valueMethod(0, -1, member);
            break;
        case 1:
            cout << member->GetName() + " is doing nothing.\n";
            break;
        case 2:
            cout << member->GetName() + " uses psychiatrist.";
            valueMethod(0, -3, member);
            break;
        }
    }

    void BadActivity(unique_ptr<Person>& member) {
        int which = rand() % 3;
        switch (which) {
        case 0:
            cout << member->GetName() + " listens propaganda radio.";
            valueMethod(-2, 0, member);
            break;
        case 1:
            cout << member->GetName() + " finds suspicious letters written by the cult leader.";
            valueMethod(-2, 1, member);
            break;
        case 2:
            cout << member->GetName() + " attends to enemy cult’s meeting for recearch purpose.";
            valueMethod(-3, 0, member);
            break;
        }
    }


}

int main()
{
    cout << "CULT SIMULATOR";
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
    cout << "\n\nRecap:\n";
    for (auto& member : memberList) {
        if (member->GetRole() == "New member" && member->GetFaith() > 59) {
            cout << member->GetName() + " has been promoted to full-time member.\n";
            member->ChangeRole("Member");
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
            if (member->GetRole() == "Member") {
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
  
        //APULUVUN SAAMINEN FAITHIN MUKAAN!
        int apuluku1 = 100 - member->GetFaith();
        int apuluku2 = rand() % apuluku1;
        apuluku2 = 100 - apuluku2;

        if (apuluku2 < 33)
            Activities::BadActivity(member);
        else if (apuluku2 < 66)
            Activities::NeutralActivity(member);
        else
            Activities::GoodActivity(member);
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

    BasicData::AddPerson(memberList, leaderName, 50, 5, "Leader");

    //add other members.
    for (int i = 1; i < howmany; i++) {
        string memberName = "";
        cout << "Add member:\n";
        cin >> memberName;
        BasicData::AddPerson(memberList, memberName, 50, 0, "New member");
    }
    cout << "The cult is now created.\n";
}

//TEST CULT
void TestCult() {
    cultName = "Erkin kultti";
    godName = "Erkki";
    BasicData::AddPerson(memberList, "Jaska", 60, 5, "New member");
    BasicData::AddPerson(memberList, "Sari", 30, 0, "New member");
    BasicData::AddPerson(memberList, "Hilda", 70, 0, "New member");
    BasicData::AddPerson(memberList, "Masi", 20, 0, "Leader");
}

//Prints cult data.
void PrintCult() {
    cout << "\n\nCult members:\n\n";
    for (auto& member : memberList) {
        cout << member->GetRole() + ": "+ member->GetName() + ", faith " + to_string(member->GetFaith()) + ", insanity " + to_string(member->GetInsanity()) + ". \n";
    }
}

void GoNext() {
    string empty = "";
    cout << "\nWrite C to Continue.\n";
    cin >> empty;
    system("cls");
    cout << "CULT SIMULATOR";
}


