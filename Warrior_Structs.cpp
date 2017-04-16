//hw02.cpp
//Shiv Lakhanpal, svl238
/*This assignment asked us to create a battle between several warriors and at the end of the fight
some would win and some would lose. They started out with a certain health and after they fought they lost
health depending on the opponent they faced.
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Warrior
{
	string warriorName; //This is the name of the warrior
	int warriorStrength;//This int is the strength of the warrior
};
void fileOpen(ifstream& ifs); //Gets file and opens it
void getWarriors(ifstream& ifs, vector<Warrior>& warriors); //Function to call vector of warriors
void statusWarriors(ifstream& ifs, vector<Warrior>& warriors); //Function to get battle and status of warriors
void warriorsBattle(Warrior& warrior1, Warrior& warrior2); //This function calls the battle between warriors
void displayWarriors(const vector<Warrior>& war); //displays/prints warriors

void fileOpen(ifstream& stream)
{
	stream.open("warriors.txt");//file is open
	if (!stream)//This sees if the file is valid
	{
		cerr << "Invalid file!";
		exit(1); //exits program
	}
}
void getWarriors(ifstream& ifs, vector<Warrior>& warriors)
{
	string check;
	string name;
	int str;
	while(ifs >> check >> name >> str)
	{
		if (check == "Warrior")//This checks if string is equal to Warrior and adds to vector
		{
			Warrior warrior1;//Object
			warrior1.warriorName = name;//Warrior Name
			warrior1.warriorStrength = str;//Warrior Strength
			warriors.push_back(warrior1);//Append to vector
		}
	}
	ifs.close();
}
void statusWarriors(ifstream& ifs, vector<Warrior>& warriors)
{
	string command;
	while (ifs >> command)
	{
		if (command == "Status")//If Command equals Status get status of warriors
		{
			displayWarriors(warriors);//Displays warriors
			cout << endl;
		}
		if (command == "Battle")//Checks for the battle command
		{
			string battle1;//1st warrior
			string battle2;//2nd warrior
			ifs >> battle1 >> battle2;//
			int firstWarriorPos; //Position of 1st warrior
			int secondWarriorPos; //Position of 2nd warrior
			for (size_t i = 0; i < warriors.size(); i++)//For loops to run through entire vector
			{
				if (warriors[i].warriorName == battle1)//1st Warrior's position in vector
				{
					firstWarriorPos = i;
				}
				if (warriors[i].warriorName == battle2)//2nd Warrior's position in vector
				{
					secondWarriorPos = i;
				}
			}
			warriorsBattle(warriors[firstWarriorPos], warriors[secondWarriorPos]);//Battles between warriors
			cout << endl;
		}
	}
}
void warriorsBattle(Warrior& warrior1, Warrior& warrior2)//Battle
{
	cout << warrior1.warriorName << " battles " << warrior2.warriorName << endl;//Displays names
	if (warrior1.warriorStrength == 0 && warrior2.warriorStrength == 0)//This statement says if both warriors die then print out:
	{
		cout << "Oh, NO! They're both dead! Yuck!" << endl;
	}
	 else if (warrior1.warriorStrength == 0 || warrior2.warriorStrength == 0)//This statement says if one of them die
	{
		cout << "He's dead, ";
		if (warrior2.warriorStrength == 0) //This statement says is second warrior dies then:
			cout << warrior1.warriorName << endl; //First warrior wins
		else
			cout << warrior2.warriorName << endl;//Second warrior wins
	}
	else if (warrior1.warriorStrength == warrior2.warriorStrength)//This statement says if both warriors remain alive
	{
		cout << "Mutual Annihilation: " << warrior1.warriorName << " and " << warrior2.warriorName << " die at each other's hands" << endl;
		warrior1.warriorStrength = 0; //First warrior's health is 0
		warrior2.warriorStrength = 0; //Second warrior's health is 0
	}
	else//This statement says if both are alive but health diff.
	{
		if (warrior1.warriorStrength > warrior2.warriorStrength)//Warrior 1 > Warrior 2
		{
			warrior1.warriorStrength = warrior1.warriorStrength - warrior2.warriorStrength; //Warriors 1 str reduces by Warrior 2
			warrior2.warriorStrength = 0;//Warrior 2 health = 0
			cout << warrior1.warriorName << " defeats " << warrior2.warriorName << endl;
		}
		else//Warrior 2 > Warrior 1
		{
			warrior2.warriorStrength = warrior2.warriorStrength - warrior1.warriorStrength; //Warriors 2 str reduces by Warrior 1
			warrior1.warriorStrength = 0;//Warrior 1 health = 0
			cout << warrior2.warriorName << " defeats " << warrior1.warriorName << endl;
		}
	}
}
void displayWarriors(const vector<Warrior>& war)
{
	cout << "There are: " << war.size() << " Warriors" << endl;
	for (size_t i = 0; i < war.size(); i++)
	{
		cout << "Warrior: " << war[i].warriorName << ", strength: "<< war[i].warriorStrength << endl;
	}
}

int main()
{
	vector<Warrior>warriors;
	ifstream ifs;
	fileOpen(ifs);
	getWarriors(ifs, warriors);
	fileOpen(ifs);
	statusWarriors(ifs, warriors);
	ifs.close();
    return 0;
}
