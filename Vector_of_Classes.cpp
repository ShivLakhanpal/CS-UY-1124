//hw05.cpp
//Shiv Lakhanpal, svl238
/*This assignment asked us to model a game of medieval times. We had to fill this "world" with warriors
and nobles. The nobles had to battle each other and the Warriors had to hrie or fire nobles to fight on
his behalf.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Warrior  //Constructor
{
public:
	Warrior(string wName, int wStrength) : name(wName), strength(wStrength)
	{}
	void display()
	{
		cout << "\t" << name << ": " << strength << endl; //Prints out strength and name of warriors
	}
	string const getWarriorName() //returns warrior name
	{
		return name;
	}
	int const getWarriorStrength() //returns warrior strength
	{
		return strength;
	}
	void assignStrength(int wStrength)
	{
		strength = wStrength;
	}
private:
  int strength;
	string name;
};
class Noble
{
public:
	Noble(string nameN) : nameOfNoble(nameN)  //Constructor
	{}
	void hire(Warrior*& war) //Hired Warriors
	{
		WarriorArmy.push_back(war);
	}
	string getnameOfNoble() const
	{
		return nameOfNoble;
	}
	void display()
	{
		cout << nameOfNoble << " has an Army of " << WarriorArmy.size() << endl;
		for (size_t i = 0; i < WarriorArmy.size(); i++) //Shuffles through the entire WarriorArmy array
		{
			WarriorArmy[i]->display(); //Outputs warriors in noble family
		}
	}
	void fire(Warrior*& war) //Warrior is Fired
	{
		int setPos = 0; //Original Position of Warrior
		bool change = false;
		for (size_t i = 0; i < WarriorArmy.size()-1; i++) //shuffles through the WarriorArmy
		{
			if (WarriorArmy[i]->getWarriorName() == war->getWarriorName()) //Finds warriors
			{
				change = true;
				WarriorArmy[i] = WarriorArmy[i + 1];
			}
			else if(change)
			{
				WarriorArmy[i] = WarriorArmy[i + 1];
			}
		}
		WarriorArmy.pop_back();
		cout << war->getWarriorName() << ", you're fired! --" << nameOfNoble << endl;
	}
	void battle(Noble*& nobleOne)
	{
		// Bill vs. Linus
		cout << nameOfNoble << " battles " << nobleOne->getnameOfNoble() << endl;
		int strengthTotal = 0;
		int firstNobleTotal = 0;
		for (size_t i = 0; i < WarriorArmy.size(); i++)
		{
			strengthTotal += WarriorArmy[i]->getWarriorStrength();
		}
		for (size_t i = 0; i < nobleOne->WarriorArmy.size(); i++)
		{
			firstNobleTotal += nobleOne->WarriorArmy[i]->getWarriorStrength();
		}
		if (strengthTotal == 0 && firstNobleTotal == 0)
		{
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}
		else if (strengthTotal == 0 || firstNobleTotal == 0)
		{
			cout << "He's dead, ";
			if (strengthTotal == 0)
				cout << nobleOne->getnameOfNoble() << endl;
			else
				cout << nameOfNoble << endl;
		}
		else if (strengthTotal == firstNobleTotal)
		{
			cout << "Mutual Annihilation: " << nameOfNoble << " and " << nobleOne->getnameOfNoble() << " die at each other's hands" << endl;
			for (size_t i = 0; i < WarriorArmy.size(); i++)
			{
				WarriorArmy[i]->assignStrength(0);
			}
			for (size_t i = 0; i < nobleOne->WarriorArmy.size(); i++)
			{
				nobleOne->WarriorArmy[i]->assignStrength(0);
			}
		}
		else
		{
			if (strengthTotal > firstNobleTotal)
			{
				int strFactor = (strengthTotal - firstNobleTotal) / (WarriorArmy.size());
				for (size_t i = 0; i < WarriorArmy.size(); i++)
				{
					WarriorArmy[i]->assignStrength(WarriorArmy[i]->getWarriorStrength() - strFactor);
				}
				for (size_t i = 0; i < nobleOne->WarriorArmy.size(); i++)
				{
					nobleOne->WarriorArmy[i]->assignStrength(0);
				}
				cout << nameOfNoble << " defeats " << nobleOne->getnameOfNoble() << endl;
			}
      else
      {
        int strFactor = (firstNobleTotal - strengthTotal) / (nobleOne->WarriorArmy.size());
        for (size_t i = 0; i < nobleOne->WarriorArmy.size(); i++)
        {
          nobleOne->WarriorArmy[i]->assignStrength(nobleOne->WarriorArmy[i]->getWarriorStrength() - strFactor);
        }
        for (size_t i = 0; i < WarriorArmy.size(); i++)
        {
          WarriorArmy[i]->assignStrength(0);
        }
        cout << nobleOne->getnameOfNoble() << " defeats " << nameOfNoble << endl;
      }
		}
	}
private:
	string nameOfNoble;
	vector <Warrior*> WarriorArmy;
};
void fileOpen(ifstream& stream);
void searchWarriorAndNobles(ifstream& ifs, vector<Warrior*>& warriors, vector <Noble*>& nobles);
void funcCommand(ifstream& ifs, vector <Warrior*>& warriors, vector <Noble*>& nobles);
bool checkNoble(vector <Noble*>& noble, string nameOfNoble, int& noblesetPos);
bool checkWarrior(vector<Warrior*>& warriors, string warriorName, int& warriorsetPos);
int main()
{
	ifstream ifs;
	vector<Warrior*>warriors;
	vector<Noble*>nobles;
	fileOpen(ifs);
	searchWarriorAndNobles(ifs,warriors,nobles);
	fileOpen(ifs);
	funcCommand(ifs, warriors, nobles);
    return 0;
}

void fileOpen(ifstream& stream)
{
	stream.open("nobleWarriors.txt");
	if (!stream)
	{
		cerr << "Invalid File!";
		exit(1);
	}
}

void searchWarriorAndNobles(ifstream& ifs, vector<Warrior*>& warriors, vector <Noble*>& nobles)
{
	string check;
	string name;
	int newStrength; //New Strength of Warrior
  bool nNoble = true;
	bool nWarrior = true;
	while (ifs >> check)
	{
		if (check == "Warrior")
		{
			ifs >> name;
			ifs >> newStrength;
			int junk = 0;
			nWarrior = checkWarrior(warriors, name, junk);
			if (!nWarrior)
			{
				Warrior* w1 = new Warrior(name, newStrength);
				warriors.push_back(w1);
			}
			nWarrior = true;
		}
		if (check == "Noble")
		{
			ifs >> name;
			int junk = 0;
			nNoble = checkNoble(nobles, name, junk);
			if (!nNoble)
			{
				Noble* nobleOne = new Noble(name); //Object of Warriors
				nobles.push_back(nobleOne);
			}
			nNoble = true;
		}
	}
	ifs.close();
}

bool checkNoble(vector <Noble*>& nobles, string nameOfNoble, int& noblesetPos)
{
	bool real = false; //This is false
	for (size_t i = 0; i < nobles.size(); i++)
	{
		if (nameOfNoble == nobles[i]->getnameOfNoble())
		{
			noblesetPos = i;
			return true;
		}
	}
	return false;
}

bool checkWarrior(vector <Warrior*>& warriors, string warriorName, int& warriorsetPos)
{
	bool  real = false;
	for (size_t i = 0; i < warriors.size(); i++)
	{
		if (warriorName == warriors[i]->getWarriorName())
		{
			warriorsetPos = i;
			return true;
		}
	}
	return false; //If warriors don't exist, returns false
}

void funcCommand(ifstream& ifs, vector <Warrior*>& warriors, vector <Noble*>& nobles)
{
	string command;
	string nameOfNoble;
	string noble2;
	string warriorName;
	int noblesetPos = 0;
	int noblesetPos2 = 0;
	int warriorsetPos = 0;
	bool nobleActual = false;
	bool realWarrior = false;
	bool nobleActual2 = false;
	while (ifs >> command)
	{
		if (command == "Hire") // Warriors have been hired
		{
			ifs >> nameOfNoble;
			ifs >> warriorName;
			nobleActual = checkNoble(nobles,nameOfNoble, noblesetPos);
			realWarrior = checkWarrior(warriors,warriorName, warriorsetPos);
			if (realWarrior && nobleActual)
			{
				nobles[noblesetPos]->hire(warriors[warriorsetPos]); //Hire class called
			}
		}
		else if (command == "Fire") // Warriors Fired
		{
			ifs >> nameOfNoble;
			ifs >> warriorName;
			nobleActual = checkNoble(nobles,nameOfNoble, noblesetPos);
			realWarrior = checkWarrior(warriors,warriorName, warriorsetPos);
			if (realWarrior && nobleActual)
			{
				nobles[noblesetPos]->fire(warriors[warriorsetPos]);
			}
		}
		else if (command == "Battle")
		{
			ifs >> nameOfNoble;
			ifs >> noble2;
			nobleActual = checkNoble(nobles,nameOfNoble, noblesetPos);
			nobleActual2 = checkNoble(nobles,noble2, noblesetPos2);
			if (nobleActual && nobleActual2)
			{
				nobles[noblesetPos]->battle(nobles[noblesetPos2]);
			}
		}
		else if (command == "Status")
		{
			for (size_t i = 0; i < nobles.size(); i++)
			{
				nobles[i]->display();
			}
		}
		else if (command == "Clear")
		{
			for (size_t i = 0; i < warriors.size(); i++)
			{
				delete warriors[i];
			}
			for (size_t i = 0; i < nobles.size(); i++)
			{
				delete nobles[i];
			}
			nobles.clear();
			warriors.clear();
		}

	}
	ifs.close();
}
