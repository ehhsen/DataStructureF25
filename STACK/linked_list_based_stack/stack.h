//which is better?  array based implememtation or linked list based?
// answer: depends on our requirements
// linked list based implememtation provides ---flexibility where size of stack can vary greatly. Prefereable where size of stack is unpedictable cuz it will save memory there
// array based implememtation is === short, simple, and efficient. If pushing and popping occur frequently, the array-based implementation executes faster because it does not
// incur the run-time overhead of the new and delete operations. (when MAX_ITEMS in the ADT specification) is small and we can be sure that we do not need
// to exceed the declared stack size, the array-based implementation is a good choice. 
#pragma once
// implementing linked list based stack
#include<iostream>
template <typename T>
struct node {
	T val;
	node* link;
};
class stack {
private:
	node<T>* TOP;
	int n;
public:
	template<typename T>
	friend bool operator==(const stack<T>&, const stack<T>&);
	template <typename T>
	friend bool operator< (const stack<T>&, const stack<T>&);

	//constructor
	stack() {
		TOP = nullptr;
		n = 0;
	}
stack(const stack<T>& other ){
	TOP = nullptr;
	operator=(other);
}

	//destructor
	~stack() {
		//TODO: deallocate memory
		while (TOP != nullptr) {
			node<T>* temp;
			temp = TOP;
			TOP = temp->link;
			delete temp;
		}
	}
	T top() {
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
		
		node<T>* temp;
		temp = new node<T>;
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
			node<T>* temp;
			temp = TOP->link;
			delete TOP;
			TOP = temp;
			--n;
		}
	}

	//operator overloading
	stack& operator= (const stack& other) {
		// check if both are equal 
		// if(this == &other){
		// 	return *this;
			
		//clear current stack; 
		node<T>* temp;
		while( TOP != nullptr ){
			temp = TOP;
			TOP = TOP->link;
			delete temp;
		}
		n =0;
		//check if other stack is empty
		if(other.TOP == nullptr){
			return *this;

		//copy first node, take 2 pointers one for both stacks and then traverse
		TOP = new node<T>;
		TOP->val = other.TOP->val;
		TOP->link = nullptr;

		//pointer to this stack
		node<T>* curr_stack_ptr = TOP;
		//pointer to other stack
		node<T>* other_stack_ptr = other.TOP->link;
		++n;

		//loop to copy all nodes
			while(other_stack_ptr != nullptr){
				//create new node
				node<T>*nn ;
				nn = new node<T>;
				nn->val = other_stack_ptr->val;
				nn->link = nullptr;

				//update ptr's
				other_stack_ptr = other_stack_ptr->link;		

				curr_stack_ptr->link = nn;
				curr_stack_ptr = nn;
				++n;
				
			}
		return *this;
	}//end of function=
	
	void swap( stack<T>& other ){
		std::swap(TOP, other.TOP);
		std::swap(size, other.size);// this code will explode if copy constructor or operator= is buggy, cuz destuctor will try to free same space twice
	}

	
};





