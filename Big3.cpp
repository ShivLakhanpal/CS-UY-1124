#include <iostream>
#include <string>
#include <vector>
//#include "roster.h"

using namespace std;
class BigInt{
	int* ptr;
public:
	BigInt(int num=0){ ptr = new int(num); }
	BigInt(const BigInt& rhs) :ptr(nullptr){ *this = rhs; } //copy-constructor
	virtual ~BigInt(){ delete ptr; } //the DESTRUCTOR
	BigInt& operator=(const BigInt&); //overloaded assignment operator
};
BigInt& BigInt::operator=(const BigInt& rhs){
	if (this != &rhs){ //test for self-assignment
		delete ptr;
		ptr = new int(*rhs.ptr);
	}
	return *this;
}
class Derived : public BigInt{
	double * dptr;
public:
	Derived() :dptr(new double(100)){}
	~Derived(){ delete dptr; }
};
void func(BigInt b){

}
int main(){
	for (int i = 0; i < 10000000000; i++)
		func(100);
	BigInt * bptr = new Derived();
	delete bptr;

	//Roster r;
	//r.addStudent("Daniel Katz");
}
