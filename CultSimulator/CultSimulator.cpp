#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <time.h> 
#include <limits>
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

namespace BasicMethods {

    //Prints cult data.
    void PrintCult() {
        cout << "\n\nCult members:\n\n";
        for (auto& member : memberList) {
            cout << member->GetRole() + ": " + member->GetName() + ", faith " + to_string(member->GetFaith()) + ", insanity " + to_string(member->GetInsanity()) + ". \n";
        }

        //print potential members list
        if (!potentialList.empty()) {
            cout << "\nPotential inviduals:\n\n";
            for (auto& potential : potentialList) {
                cout << potential->GetName() + ", faith " + to_string(potential->GetFaith()) + ". \n";
            }
        }

    }

    //Change the screen
    void GoNext() {
        string empty = "";
        cout << "\nPress ENTER to continue.\n";
        cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
        system("cls");
        cout << "CULT SIMULATOR";
    }

    //for getting member in list.
        string GetRandomName(list <unique_ptr<Person>>& lista) {
        
        int luku1 = 0; 
        int luku2 = rand() % lista.size();
        for (auto& person : lista) {
            if (luku1 == luku2) {
                return person->GetName();
            }
        }
    }
}

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
        int which = rand() % 6;
        int apuluku = 0;
        string apustring = "";
        
        //Check what is chosen.
        switch (which) {
        
        //follower finder.
        case 0:
            apuluku = rand() % 3;
                if (apuluku < 1) {
                    cout << "\n" << member->GetName() + " has found a potential member! Give them a name so they can be added to the list:";
                    valueMethod(4, -1, member);
                    cin >> apustring;
                    BasicData::AddPerson(potentialList, apustring, 10, 0, "Potential");
                    cout << endl;

                }
                else {
                    cout << member->GetName() + " is trying to find new followers.";
                    valueMethod(3, 0, member);
                }
            break;
        case 1:
            cout << member->GetName() + " prays for 8 hours.";
            valueMethod(5, 2, member);
            break;
        case 2:
            cout << member->GetName() + " reads the cult scripture.";
            valueMethod(2, 1, member);
            break;
        case 3:
            cout << member->GetName() + " makes threatening calls to the previous cult members.";
            valueMethod(3, 2, member);
            break;
        case 4:
            cout << member->GetName() + " writes a religious opinion to a cooking web site.";
            valueMethod(2, 1, member);
            break;

        //harassing potential members.
        case 5:
            if (potentialList.empty()) {
                GoodActivity(member);
            }
            else {
                apustring = BasicMethods::GetRandomName(potentialList);
                cout << member->GetName() + " is persuading " + apustring + " to join " + cultName+".";
                for (auto& potential : potentialList) {
                    if (potential->GetName() == apustring) { potential->AddFaith(10); }
                }
                valueMethod(2, 1, member);
            }
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
            cout << member->GetName() + " attends to enemy cult meeting for recearch purpose.";
            valueMethod(-3, 0, member);
            break;
        }
    }


}

namespace CreatingCult {
    
    //Creating cult.
    void CreateCult() {
        power = 0;
        membercount = 0;

        cout << "\n\nWelcome to the Cult Simulator! Tell me the name of your cult:" << endl;
        cin >> cultName;
        cout << "\nNext, tell me the name of your god:\n";
        cin >> godName;

        //how many members
        int howmany = 0;
        cout << "\nTime to add some members. Tell me, how many members will there be (4-10):\n";

        //check if user input is cool.
        while (true) {
            cin >> howmany;
            if (howmany < 11 && howmany > 3) {
                break;
            }
            cout << "Invalid input. How many members? (4-10)\n";
        }

        cout << "\nExcellent! Now you can add members by writing their names.\n";

        //add leader.
        cout << "At first, choose your leader:\n";
        string leaderName;
        cin >> leaderName;

        BasicData::AddPerson(memberList, leaderName, 50, 0, "Leader");

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
        BasicData::AddPerson(memberList, "Jaska", 50, 0, "New member");
        BasicData::AddPerson(memberList, "Sari", 50, 0, "New member");
        BasicData::AddPerson(memberList, "Hilda", 50, 0, "New member");
        BasicData::AddPerson(memberList, "Elmeri", 50, 0, "New member");
        BasicData::AddPerson(memberList, "Viljami", 50, 0, "New member");
        BasicData::AddPerson(memberList, "Hulda", 50, 0, "New member");
        BasicData::AddPerson(memberList, "Masi", 50, 0, "Leader");
    }

}

namespace DayCycle {

    void DayCycleCheckers() {
        //check if faith is more than 60.
        cout << "\n\nRecap:\n";
        for (auto& member : memberList) {
            if (member->GetRole() == "New member" && member->GetFaith() > 59) {
                cout << member->GetName() + " has been promoted to follower of "+godName+".\n";
                member->ChangeRole("Follower");
            }
        }

        //check if someone must be thrown out.
        for (auto& member : memberList) {
            if (member->GetFaith() < 15) {
                cout << member->GetName() + " has resign " + cultName + " and is now a public enemy.\n";
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
                if (member->GetRole() == "Follower") {
                    cout << "Since the previous leader is no longer among us, " + member->GetName() + " is now the new leader.\n";
                    member->ChangeRole("Leader");
                    break;
                }
            }
        }

        //Check if there is a potential member with faith 50.
        for (auto& potential : potentialList) {
            if (potential->GetFaith() > 49) {
                cout << potential->GetName() + " has joined "+ cultName +"!\n";
                BasicData::AddPerson(memberList, potential->GetName(), potential->GetFaith(), 0, "New member");
                BasicData::DeletePerson(potential, potentialList);
                break;
            }
        }
    }

    void DayCycleActivities() {
        cout << "\nDaily Activities:\n\n";

        //go through every member and check what they do.
        for (auto& member : memberList) {

            //Make apuluku based on faith.
            float apuluku1 = member->GetFaith() - 50;
            float apuluku2 = rand() % 100 + apuluku1;

            //Check what kind of activity happens.
            if (apuluku2 < 25)
                Activities::BadActivity(member);
            else if (apuluku2 < 60)
                Activities::NeutralActivity(member);
            else
                Activities::GoodActivity(member);
        }
    }

}

int main()
{
    cout << "CULT SIMULATOR";
    //CreatingCult::CreateCult();
    //BasicMethods::GoNext();
    CreatingCult::TestCult(); 
    BasicMethods::PrintCult();
    BasicMethods::GoNext();

    //Day Cycle
    while (true) {
        //Day cycle.
        DayCycle::DayCycleCheckers();
        DayCycle::DayCycleActivities();
        BasicMethods::GoNext();

        //Cult information.
        BasicMethods::PrintCult();
        BasicMethods::GoNext();
    }

}

//These checks if anything must be changed inside the cult.





