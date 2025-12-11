#pragma once
#include<stdexcept>

template <typename T>
struct node {
	T val;
	node<T> *link;
};

template <typename T>
class queue {
private:
	node<T>  *F, *B;
	int n;///size
public:
	//////////////////////////
	queue(){
	F = B = nullptr;
	n = 0;
	}
	///////////////////////////
	T& front()const {
		if (F == nullptr) {
			throw std::runtime_error("queue underflow");
		}
		else {
			return F->val;
		}
	}
	//////////////////////////////////
	T& back()const {
		if (B == nullptr) {
		throw std::runtime_error("queue underflow");
		}
		else {
			return B->val;
		}
	}
	///////////////////////////////////////
	bool empty()const {
		return n==0;
	}
	//////////////////////////////////////////
	int size()const {
		return n;
	}
	//////////////////////////////////////////
	void push(T& val) {
		node<T> *temp;
		temp = new node<T>;
		temp->val = val;
		temp->link = nullptr;
		if (n == 0) {
			//////for first value
			F = temp;
			B = temp;
			++n;
		}
		else {
			B->link = temp;
			B = temp;
			++n;
		}
	}
	////////////////////////////////////
	void pop() {
		if (F == nullptr) {
			throw("queue underflow");
		}
		else {
			node<T> *temp;
			temp = F->link;
			delete F;
			F = temp;
			if (F == nullptr) {
				B = nullptr;
			}
			--n;
		}
	}
	////////////////////////////////////////


};
