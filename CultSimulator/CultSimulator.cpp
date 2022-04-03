#include <iostream>
#include <list>
#include <memory>
#include <time.h> 
#include <limits>
#include <conio.h>
#include <string>

#include "Person.h";
#include "BasicData.h";

using namespace std;

//variables
int day;
float membercount;
int power;
string cultName;
string godName;

//peoplelists
list <unique_ptr<Person>> memberList;
list <unique_ptr<Person>> potentialList;
list <unique_ptr<Person>> enemyList;

//Namespace for basic methods / methods without other namespace.
namespace BasicMethods {

    //for getting member in list.
    string GetRandomName(list <unique_ptr<Person>>& lista) {
        int luku1 = 0;
        int luku2 = rand() % lista.size();
        for (auto& person : lista) {
            if (luku1 == luku2) {
                return person->GetName();
            }
            luku1++;
        }
    }
    void EndCult();

    //Prints cult data.
    void PrintCult() {
        day++;

        //check if there is no more cult members and end the game.
        if (memberList.empty()) {
            system("cls");
            BasicMethods::EndCult();
        }

        //check if membercount is high enough and game can be won.
        if (membercount > 3000) {
            BasicMethods::EndCult();
        }

        //edit global membercount
        membercount = membercount * (1+memberList.size()/25.0) / (1+enemyList.size()/20.0);
        cout << "\n\nGlobal member count: " << floor(membercount);

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

        //print enemies
        if (!enemyList.empty()) {
            cout << "\nPublic enemies:\n\n";
            for (auto& enemy : enemyList) {
                cout << enemy->GetName()+". \n";
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

    //Print the ending depending on why it happened.
    void EndCult() {
        cout << "THE END";
        if (membercount > 3000) {
            int ending = rand() % 3;
            cout << ending;
            switch (ending) {
            case 0:
                cout << "\n\nAfter getting enough followers "+cultName+" managed to summon "+godName+".\nHowever, "+godName+" wasn't that happy about the early wake-up call and instead of giving anyone anything started eating people.\n";
                break;
            case 1:
                cout << "\n\nBeing the number one suspicious cult in the world wasn't easy, especially after media found some tweets of the original leader.\nWho would've guessed that "+cultName+" was actually just a funny prank made by a lonely, socially awkward person?\n";
                break;
            case 2:
                string kamu = BasicMethods::GetRandomName(memberList);
                cout << "\n\nEverything went fine until " + kamu + " predicted the end of the world. Quickly, things turned out pretty chaotic.\nThe followers went on full rampage and the world around them was set on fire. Oh, if someone had told them that the only reason why "+kamu+" had made their prophet was to impress a girl...\n";
                break;
            }
        }
        else if (membercount > 500) {
            cout << "\n\nAlthough " + cultName + " never managed to reach its goals before being shutted down, after hundreds of years a new moment was born from the old writings. They call themselves THE NEW "+ cultName+".\n";
        }

        else{
            cout << "\n\nLike many beautiful things in the world, after a while "+cultName+" and all of its followers just vanished.\nIt almost felt like they had never been there. Maybe they should have joined some other cult...\n";
        }
        exit(0);
    }
}

//Namespace for cult activities.
namespace Activities {

    //method for changing faith and insanity and print it.
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

    //Activities to rise faith and insanity.
    void GoodActivity(unique_ptr<Person>& member) {
        int which = rand() % 6;
        int apuluku = 0;
        string apustring = "";

        //Check what is chosen.
        switch (which) {
        
        //follower finder.
        case 0:
            apuluku = rand() % 4;
                if (apuluku < 1) {
                    cout << "\n" << member->GetName() + " has found a potential member! Give them a name so they can be added to the list:";
                    valueMethod(3, -1, member);
                    while (true) {
                        getline(cin, apustring);
                        if (apustring != "") {
                            break;
                        }
                        cout << "Give them a name:\n";
                    }

                    BasicData::AddPerson(potentialList, apustring, 10, 0, "Potential");
                    cout << endl;

                }
                else {
                    cout << member->GetName() + " is trying to find new followers.";
                    valueMethod(1, 0, member);
                }
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
            valueMethod(3, 2, member);
            break;
        case 4:
            cout << member->GetName() + " writes a religious opinion to a cooking web site.";
            valueMethod(2, 1, member);
            break;

        //harassing potential members to join the cult.
        case 5:
            if (potentialList.empty()) {
                GoodActivity(member);

            }
            else {
                apustring = BasicMethods::GetRandomName(potentialList);
                cout << member->GetName() + " is persuading " + apustring + " to join " + cultName+".";
                for (auto& potential : potentialList) {
                    if (potential->GetName() == apustring) { if (potential->GetFaith() < 50) { potential->AddFaith(10); } }
                }
                valueMethod(2, 1, member);
            }
            break;
        }


    }

    //Activities that make a member lose insanity.
    void NeutralActivity(unique_ptr<Person>& member) {
        int which = rand() % 3;
        switch (which) {
        case 0:
            cout << member->GetName() + " has a coffee break.";
            valueMethod(0, -2, member);
            break;
        case 1:
            cout << member->GetName() + " is doing nothing.";
            valueMethod(0, -1, member);
            break;
        case 2:
            cout << member->GetName() + " uses psychiatrist.";
            valueMethod(0, -3, member);
            break;
        }
    }
    
    //Activities that make a member lose faith.
    void BadActivity(unique_ptr<Person>& member) {
        int which = rand() % 4;
        string apustring = "";
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
        case 3:
            apustring = BasicMethods::GetRandomName(memberList);
            cout << member->GetName() + " is influencing " + apustring + " with their bad opinions. (faith -2 for both)\n";
            for (auto& member2 : potentialList) {
                if (member2->GetName() == apustring) { member2->AddFaith(-2); }
            }
            member->AddFaith(-2);
        }
    }
    
    //Check why the member has died and delete them.
    void DeathActivity(unique_ptr<Person>& member) {
        int which = rand() % 4;
        switch (which) {
        case 0:
            cout << member->GetName() + " thinks they can fly and jumps out of the roof. They are declared dead.\n";
            break;
        case 1:
            cout << member->GetName() + " disappeares mysteriously. "+cultName+" declares them dead.\n";
            break;
        case 2:
            cout << member->GetName() + " threatens to spread the secrets of older cult members. Later, they are declared dead.\n";
            break;
        case 3:
            cout << member->GetName() + " volunteered to be sacrificed for " + godName + ". They are declared dead.\n";
        }

        //HERE we should add insanity for everyone maybe.

        BasicData::DeletePerson(member, memberList);
    }

    void EnemyActivity(unique_ptr<Person>& enemy) {
        int which = rand() % 2;
        switch (which) {
            case 1: 
                string name = BasicMethods::GetRandomName(memberList);
                cout << "Public enemy "+ enemy->GetName() + " is influecing " + name + " secretly with their opinions. (faith -3 for " + name + ")\n";
                for (auto& member2 : potentialList) {
                    if (member2->GetName() == name) { member2->AddFaith(-3); }
                }
        }
    }
}

//Namespace for cult creating methods.
namespace CreatingCult {
    
    //Creating cult.
    void CreateCult() {
        power = 0;
        day = 0;

        cout << "\n\nWelcome to the Cult Simulator! Tell me the name of your cult:" << endl;
        getline(cin, cultName);
        cout << "\nNext, tell me the name of your god:\n";
        getline(cin, godName);

        //how many members
        string howmany = "";
        cout << "\nTime to add some members. Tell me, how many members will there be (4-6):\n";

        //check if user input is cool.
        while (true) {
            getline(cin,howmany);
            if (stoi(howmany) < 7 && stoi(howmany) > 3) {
                break;
            }
            cout << "Invalid input. How many members? (4-6)\n";
        }
        membercount = stoi(howmany);

        cout << "\nExcellent! Now you can add members by writing their names.\n";

        //add leader.
        cout << "At first, choose your leader:\n";
        string leaderName;
        getline(cin, leaderName);

        BasicData::AddPerson(memberList, leaderName, 50, 0, "Leader");

        //add other members.
        for (int i = 1; i < stoi(howmany); i++) {
            string memberName = "";
            cout << "Add member:\n";
            getline(cin, memberName);
            BasicData::AddPerson(memberList, memberName, 50, 0, "New member");
        }
        cout << "The cult is now created.\n";
    }

    //TEST CULT
    void TestCult() {
        cultName = "Petterin kultti";
        godName = "Petteri";
        BasicData::AddPerson(memberList, "Jaska", 55, 0, "Leader");
        BasicData::AddPerson(memberList, "Sari", 55, 0, "New member");
        BasicData::AddPerson(memberList, "Hilda", 55, 0, "New member");
        BasicData::AddPerson(memberList, "Elmeri", 55, 0, "New member");
        membercount = memberList.size();
        day = 0;
    }

}

//Namespace for day cycle methods.
namespace DayCycle {

    //Different things that may happen at the start of the day, such as follower becoming enemy etc.
    void DayCycleCheckers() {

        cout << "\n\nRecap:\n\n";
        
        //check if faith is more than 60 and make them a follower.
        for (auto& member : memberList) {
            if (member->GetRole() == "New member" && member->GetFaith() > 59) {
                cout << member->GetName() + " has been promoted to a follower of "+godName+".\n";
                member->ChangeRole("Follower");
            }
        }

        //check if someone must be thrown out.
        for (auto& member : memberList) {
            if (member->GetFaith() < 40) {
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

        //if there is no leader, get the first member with Honorary member - role and make them a leader.
        if (noLeader) {
            for (auto& member : memberList) {
                if (member->GetRole() == "Follower") {
                    cout << "Since the previous leader is no longer among us, " + member->GetName() + " is now the new leader.\n";
                    member->ChangeRole("Leader");
                    break;
                }
            }
        }

        //Check if there is a potential member with faith 50 and make them a member.
        for (auto& potential : potentialList) {
            if (potential->GetFaith() > 49) {
                cout << potential->GetName() + " has joined "+ cultName +"!\n";
                BasicData::AddPerson(memberList, potential->GetName(), 50, 0, "New member");
                BasicData::DeletePerson(potential, potentialList);
                break;
            }
        }
    }

    //Check what every member does during the day.
    void DayCycleActivities() {
        cout << "\nDaily Activities:\n\n";

        //go through every member and check what they do.
        for (auto& member : memberList) {

            //Check if member diesss.
            int kuolinluku = rand()%(member->GetInsanity()+1);
            if (kuolinluku > 10) {
                Activities::DeathActivity(member);
                break;
            }

            //Make apuluku based on faith.
            float apuluku1 = member->GetFaith() - 50;
            float apuluku2 = rand() % 100 + apuluku1;

            //Check what kind of activity happens.
            if (apuluku2 < 33)
                Activities::BadActivity(member);
            else if (apuluku2 < 63)
                Activities::NeutralActivity(member);
            else
                Activities::GoodActivity(member);
        }
    }

    //Check what every enemy does during the day.
    void DailyEnemy() {
        if (!enemyList.empty()) {
            cout << "\nEnemy activities:\n\n";
            for (auto& enemy : enemyList) {

                //Check if enemy does anything.
                int tehda = rand() % 2;

                //Then print enemy activity.
                if (tehda < 1) {
                    Activities::EnemyActivity(enemy);
                }
            }
        }
    }


}

//THE GAME ITSELF.
int main()
{
    cout << "CULT SIMULATOR";
    std::srand(std::time(0));
    //Create a cult
    CreatingCult::CreateCult();
    BasicMethods::GoNext();
    
    //Test cult for testing only
    //CreatingCult::TestCult(); 
    
    //pre-printing.
    BasicMethods::PrintCult();
    BasicMethods::GoNext();

    //Day Cycle
    while (true) {
        //Day cycle.
        cout << "\n\nDay " << day;
        DayCycle::DayCycleCheckers();
        DayCycle::DayCycleActivities();
        DayCycle::DailyEnemy();
        BasicMethods::GoNext();

        //Cult information.
        BasicMethods::PrintCult();
        BasicMethods::GoNext();
    }

}
