//hw07.cpp
//Warrior.cpp
//Shiv Lakhanpal
//svl238

#include "Warrior.h"
#include <iostream>
using namespace std;
namespace WarriorCraft
{
	Warrior::Warrior(string name, int strength) : wName(name), wStrength(strength), isAlive(true), master(nullptr)
	{}
	string const Warrior::nameGetter(){
		return wName;
	}
	int const Warrior::strengthGetter()
	{
		return wStrength;
	}
	void Warrior::strengthSetter(int s)
	{
		wStrength = strength;
	}
	void Warrior::hireSetter(Noble* nob)
	{
		master = nob;
	}
	Noble* Warrior::hireGetter() const
	{
		return master;
	}
	void Warrior::deadSetter()
	{
		isAlive = false;
	}
	bool Warrior::aliveGetter() const
	{
		return isAlive;
	}
	void Warrior::runaway()
	{
		if (master != nullptr)
		{
			master->remove(this);
			cout << wName << " flees in terror, abandoning his lord, " << master->getNobleName()<<endl;
			master = nullptr;
		}
	}
}
