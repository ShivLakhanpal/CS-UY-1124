#include <iostream>
using namespace std;

int getANumber(){
  int input;
  cout << "Enter a number : ";
  cin >> input;
  return input;
}

int getANumberInRange(int start, int end){
  int input;
  do {
    cout << "Enter a number in range (" << start << "," << end<<"): ";
    cin >> input;
  } while(input < start || input > end);
  return input;
}


Pass-by-value:
void func(int param){
  param = 0;
}
int main(){
  int x = 100;
  func(x);
  cout << x;
}

Pass-by-reference
void func(int& param){
  param = 0;
}
int main(){
  int x = 100;
  func(x)
  cout << x;
}

void openInputFile(ifstream& inFile){
  string filename;
  cout << "What file you wanna open? ";
  cin >> filename;
  ifstream inFile;
  inFile.open(filename);
  while(!inFile){ //test that the file opened
    cout << "bad filename" << endl;
    cout << "what filename? ";
    cin >> filename;
    inFile.clear();
    inFile.open(filename);
  }
