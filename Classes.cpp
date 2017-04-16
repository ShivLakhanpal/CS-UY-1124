#include <iostream>
#include <string>

using namespace std;

/*
Public:
- Primarily functions to perform actions on private information
- Anyone can access anything public

Private:
- The default
- Primarily data, but will also have functions that do not need to be public
- Accessible only by functions which are part of the class
*/

class Date{
  int day;
  int month;
  int year;
public:
  Date(){day = 1; month = 1; year = 1970;}
  Date(int newDay, int newMonth, int newYear){
    day = newDay;
    month = newMonth;
    year = newYear;
  }
  int getDay() const{return day;}
  int getMonth() const{return month;}
  int getYear() const{return year;}
}

class BankAccount{
  double balance;
  int acctno;
  double interestRate;
  bool isChecking;
  Date openDate;
  double fee;
  bool open;
  //BankAccount otherAccount;
public:
  BankAccount(double balance, double interestRate=0.01, bool isChecking=true);
  bool withdraw1(double amount);
  void deposit(double amount);
  void calculateInterest();
  double getBalance() const{return balance;}
}


/*class Tree{
  double height;
  int rings;
  bool broken;
public:
  Tree(); //Defualt constructor
         // called automatically when an object is instantiated
  void grow(double addition);
  double getHeight(){return height;}
  bool isBroken(){return broken;}
};

Tree::Tree(){
  height = 0;
  rings = 1;
  broken false;
}

int main(){
  Tree t;
  t.grow(100);
}*/
