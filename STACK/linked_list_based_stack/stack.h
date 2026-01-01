#pragma once
// implementing linked list based stack
#include<iostream>
struct node {
	int val;
	node* link;
};
class stack {
private:
	node* TOP;
	int n;
public:
	//constructor
	stack() {
		TOP = nullptr;
		n = 0;
	}
	//destructor
	~stack() {
		//TODO: deallocate memory
		while (TOP != nullptr) {
			node* temp;
			temp = TOP;
			TOP = temp->link;
			delete temp;
		}
	}
	int top() {
		try {
			if (TOP == nullptr) {
				throw("stack underflow");
				return -1;
			}
		
			else {
				return TOP->val;
			}
		}
		catch (const char* msg) {
			std::cout << msg << std::endl;
		}

	}
	void push(int& val) {
		
		node* temp;
		temp = new node;
		temp->val = val;
		temp->link = TOP; // nullptr for first iteration
		TOP = temp;
		++n;
	}
	int size()const {
		return n;
	}
	bool empty()const {
		return TOP == nullptr;
	}
	void pop() {
		if (TOP == nullptr) {
			throw("Stack Underflow");
		}
		else {
			node* temp;
			temp = TOP->link;
			delete TOP;
			TOP = temp;
			--n;
		}
	}

	//operator overloading
	//stack& operator= (const stack& other) {
	//	// delete memory of *this stack
	//	~stack();

	//	//////////

	//	node *temp, * prev;
	//	temp = other.TOP;
	//	while (temp != nullptr) {
	//		node* temp2;
	//		temp2 = new node;
	//		//TODO: delete

	//	}

	//}	
};