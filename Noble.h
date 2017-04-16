//hw07.cpp
//Noble Header
//Shiv Lakhanpal
//svl238

#ifndef NOBLE_H
#define NOBLE_H
#include "Warrior.h"
#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft
{
	class Warrior;
	class Noble
	{
		friend std::ostream& operator<<(std::ostream& os, Noble& n);
	public:
		Noble(std::string nNoble); //This is name of noble
		std::string nobleNameGetter() const;
		std::vector<Warrior*>& armyGetter(); //Army is returned
		int strengthGetter() const;
		void strengthAdjust(int factor);
		void hire(Warrior& w); //Hire Function
		void remove(Warrior* w); //Removes warrior
		void fire(Warrior*& w); //Fire Function
		void battle(Noble n1);
	private:
		std::string nameOfNoble;
		std::vector <Warrior*> army;
	};
}
#endif
