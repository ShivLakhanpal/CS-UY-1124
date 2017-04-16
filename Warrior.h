//hw07.cpp
//Warrior Header
//Shiv Lakhanpal, svl238

#ifndef WARRIOR_H
#define WARRIOR_H
#include "Noble.h"
#include <iostream>
#include <vector>
#include <string>
namespace WarriorCraft
{
	class Noble;
	class Warrior
	{
	public:
		Warrior(std::string name, int strength);
		std::string const nameGetter();
    void strengthSetter(int s);
    void hireSetter(Noble* nob);
		int const strengthGetter();
		Noble* hireGetter() const;
		void deadSetter();
		bool aliveGetter() const;
		void runaway();
	private:
		std::string name;
    int wStrength;
    bool isAlive;
		Noble* master;
	};
}
#endif
