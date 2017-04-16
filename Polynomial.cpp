//hw08
//Shiv Lakhanpal
//svl238
/*
	This assignment asked us to create a Polynomial class that would store and manipulate Polynomial
	expressions.
*/

#include "Polynomial.h"
#include <math.h>
using namespace std;

namespace Poly {
	Polynomial::Polynomial(const vector<int>& numCoefficients) : head(nullptr), polyDegree(numCoefficients.size() - 1) {
		for (size_t i = 0; i < numCoefficients.size(); ++i) {

				firstInsert(numCoefficients[i]);  //Insert the coefficients in order

		}
	}

	Polynomial::~Polynomial() {
		clearList();
	}

	Polynomial::Polynomial(const Polynomial& rhs) {
		polyDegree = rhs.polyDegree;
		Node* temp = rhs.head;
		head = new Node(temp->data);
		Node* pos = head;
		temp = temp->next;
		while (temp) {
			pos->next = new Node(temp->data);
			pos = pos->next;
			temp = temp->next;
		}
	}

	Polynomial& Polynomial::operator= (const Polynomial& rhs) { //Assignment Operator
		if (this != &rhs) {
			clearList();
			polyDegree = rhs.polyDegree;
			Node* temp = rhs.head;
			head = new Node(temp->data);
			Node* pos = head;
			temp = temp->next;
			while (temp) {
				pos->next = new Node(temp->data); //Position goes to next spot
				pos = pos->next;
				temp = temp->next; //The temp spot points to next
			}
		}
		return *this;
	}

	void Polynomial::firstInsert(int numCoefficient) {  //Insert the coefficient
		Node* newNode = new Node(numCoefficient);
		if (!head) {
			head = newNode;
		}
		else {
			newNode->next = head;
			head = newNode;
		}
	}

	int Polynomial::getDegree() const { //Get Degree of Polynomial
		return polyDegree;
	}


	Node* Polynomial::getHead() const {  //Get Head of Polynomial
		return head;
	}

	Node* Polynomial::searchLast() const { //Find the last position of Polynomial
		Node* temp = head;
		while (temp->next) {
			temp = temp->next;
		}
		return temp;
	}

	void Polynomial::clearList() { //Clear
		while (head) {
			Node* temp = head->next;
			delete head;
			head = temp;
		}
	}

	void Polynomial::lastRemove() const { //Remove last position
		Node* temp = head;
		if (temp->next == nullptr) return;
		while (temp->next->next != nullptr) {
			temp = temp->next;
		}
		delete temp-> next;
		temp->next = nullptr;
		return;
	}

	int Polynomial::evalPoly(int value) const{
		int outcome = 0;
		int power = 0;
		Node* temp = head;
		while (temp) {
			outcome += (temp->data)*(pow(value, power));
			power++;
			temp = temp->next;
		}
		return outcome;
	}

	Polynomial& Polynomial::operator+= (const Polynomial& rhs) {    //Assignment Operator
		if (rhs.polyDegree > polyDegree) {
			Node* pos = head;
			Node* temp = rhs.head;
			while (pos->next) {
				pos->data += temp->data;
				pos = pos->next;
				temp = temp->next;
			}
			pos->data += temp->data;
			temp = temp->next;
			while (temp) {
				pos->next = new Node(temp->data);
				pos = pos->next;
				temp = temp->next;
				polyDegree++;
			}
		}
		else {
			Node* pos = head;
			Node* temp = rhs.head;
			while (temp) {
				pos->data += temp->data;
				pos = pos->next;
				temp = temp->next;
			}
			while (searchLast()->data == 0) {
				lastRemove();
				polyDegree--;
			}
		}
		return *this;
	}

	ostream& operator<< (ostream& os, const Polynomial& polynomial) {
		vector <int> numCoefficients;
		int power = polynomial.polyDegree;
		Node* temp = polynomial.head;
		while (temp) {
			numCoefficients.push_back(temp->data);
			temp = temp->next;
		}

		if (numCoefficients.size() > 2) {
			os << numCoefficients[numCoefficients.size() - 1] << "x^" << power;
			power--;
			for (size_t i = numCoefficients.size() - 2; i > 1; --i) {
				if (numCoefficients[i] != 0) {
					os << " + " << numCoefficients[i] << "x^" << power;
					power--;
				}
			}
			if (numCoefficients[1] != 0) {
				os << " + " << numCoefficients[1] << 'x';
			}
			if (numCoefficients[0] != 0) {
				os << " + " << numCoefficients[0];
			}
		}

		else if (numCoefficients.size() == 2) {
			os << numCoefficients[1] << 'x';
			if (numCoefficients[0] != 0) {
				os << " + " << numCoefficients[0];
			}
		}

		else {
			os << numCoefficients[0];
		}

		return os;
	}

	Polynomial operator+ (const Polynomial& lhs, const Polynomial& rhs) {
		Polynomial temp = lhs;
		temp += rhs;
		return temp;
	}

	bool operator== (const Polynomial& lhs, const Polynomial& rhs) {
		Node* firstTemp = lhs.getHead();
		Node* secondTemp = rhs.getHead();
		if (lhs.getDegree() != rhs.getDegree()) return false;
		else {
			while (firstTemp) {
				if (firstTemp->data != secondTemp->data) return false;
				else {
					firstTemp = firstTemp->next;
					secondTemp = secondTemp->next;
				}
			}
			return true;
		}
	}

	bool operator != (const Polynomial& lhs, const Polynomial& rhs) {
		return !(lhs == rhs);
	}
}
