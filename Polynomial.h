//hw08
//Shiv Lakhanpal
//svl238
/*
	This is the header file for the Polynomial.cpp file
*/


#include <iostream>
#include <vector>
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

namespace Poly {   //Namespace created is Poly
	struct Node {
		Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
		int data; //data inserted
		Node* next;   //Next available position
	};

	class Polynomial {
	public:
		Polynomial(const std::vector<int>& numCoefficients = {0}); //Constructor
		~Polynomial();  //Destructor
		Polynomial(const Polynomial& rhs); //Assignment Operator
		Polynomial& operator= (const Polynomial& rhs);
		void firstInsert(int numCoefficient);
    int getDegree() const;
    Node* searchLast() const;
		Node* getHead() const;
		void clearList();
		void lastRemove() const; //If one item in the list, has no effect
		int evalPoly(int value) const;
		Polynomial& operator+= (const Polynomial& rhs);
		friend std::ostream& operator<< (std::ostream& os, const Polynomial& polynomial);

	private:
		Node* head;
		int polyDegree;
	};

	Polynomial operator+ (const Polynomial& lhs, const Polynomial& rhs);
	bool operator== (const Polynomial& lhs, const Polynomial& rhs);
	bool operator != (const Polynomial& lhs, const Polynomial& rhs);

}

#endif
