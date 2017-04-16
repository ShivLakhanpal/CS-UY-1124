//hw07.cpp
//Noble Cpp
//Shiv Lakhanpal
//svl238

#include "Noble.h"
#include <iostream>
using namespace std;
namespace WarriorCraft
{
	ostream& operator<<(ostream& os, Noble& n) {

		os << n.getNobleName() << " has an army of " << n.armyGetter().size() << endl;
		for (size_t i = 0; i < n.armyGetter().size(); i++)

		{
			os << "\t" << n.armyGetter()[i]->nameGetter() << ": " << n.armyGetter()[i]->strengthGetter() << endl;
		}
		return os;
	}

	Noble::Noble(string nNoble): nameOfNoble(nNoble){}
	string Noble::getNobleName() const
	{
		return nameOfNoble;
	}
	std::vector<Warrior*>& Noble::armyGetter()
	{
		return army;

	}
	int Noble::strengthGetter() const
	{
		int strength = 0;
		for (size_t i = 0; i < army.size(); i++)
		{
			strength += army[i]->strengthGetter();
		}
		return strength;
	}
	void Noble::strengthAdjust(int key)
	{
		if (key < strengthGetter())
		{
			key = key / army.size();
		}
		for (size_t i = 0; i < army.size(); i++)
		{
			if (army[i]->strengthGetter() <= key)
			{
				army[i]->strengthSetter(0);
				army[i]->deadSetter();
			}
			else
			{
				army[i]->strengthSetter(strengthGetter() - key);
			}
		}
	}
	void Noble::hire(Warrior& w)
	{
		if (w.hireGetter() == nullptr)
		{
			army.push_back(&w);
			w.hireSetter(this);
		}
	}
	void Noble::remove(Warrior* w)
	{
		int pos = 0;//position number
		for (size_t i = 0; i < army.size(); i++)
		{
			if (army[i]->nameGetter() == w->nameGetter())
			{
				for (size_t x = i; x < army.size() - 1; x++)
				{

					army[x] = army[x + 1];
				}
				i += army.size();
			}
		}
		army.pop_back();
	}
	void Noble::fire(Warrior*& w)
	{
		remove(w);
		cout << w->nameGetter() << ", you're fired! --" << nameOfNoble << endl;
	}
	void Noble::battle(Noble n1)
	{
		cout << nameOfNoble << " battles " << n1.getNobleName() << endl;
		if (strengthGetter()== 0 && n1.strengthGetter() == 0)
		{
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}
		else if (strengthGetter() == 0 || n1.strengthGetter() == 0)
		{
			cout << "He's dead, ";
			if (strengthGetter() == 0)
				cout << n1.getNobleName() << endl;
			else
				cout << nameOfNoble << endl;
		}
		else if (strengthGetter() == n1.strengthGetter())
		{
			cout << "Mutual Annihilation: " << nameOfNoble << " and " << n1.getNobleName() << " die at each other's hands" << endl;
			strengthAdjust(strengthGetter());
			n1.strengthAdjust(n1.strengthGetter());
		}
		else
		{
			if (strengthGetter() > n1.strengthGetter())
			{
				strengthAdjust(n1.strengthGetter());
				n1.strengthAdjust(n1.strengthGetter());
				cout << nameOfNoble << " defeats " << n1.getNobleName() << endl;
			}
			else
			{
				n1.strengthAdjust(strengthGetter());
				strengthAdjust(strengthGetter());
				cout << n1.getNobleName() << " defeats " << nameOfNoble << endl;
			}
		}
	}
}
