#pragma once
#include<stdexcept>
//implementing array based stack with operator= etc
class stack {
private:
	int SIZE, TOP;
	int* DATA;

public:
	stack(int s = 10) {
		TOP = -1;
		SIZE = s;
		DATA = new int[SIZE];
	}
	~stack() {
		delete[] DATA;
	}
	void push(const int& val) {
		if (TOP + 1 == SIZE){
			//throw("stack overflow");
			throw std::runtime_error("stack overflow");
		}
		else {
			++TOP;
			DATA[TOP] = val;
		}
	}
	void pop() {
		if (TOP == -1) {
			//throw("stack underflow");
			throw std::runtime_error("stack underflow");
		}
		else {
			--TOP;
		}
	}
	int top()const{
		if (TOP == -1) {
			//throw("stack underflow");
			throw std::runtime_error("stack overflow");
		}
		else {
			return DATA[TOP];
		}

	}
	bool empty()const {
		return TOP == -1;
	}
	int size()const {
		return TOP + 1;
	}
	void swap(stack& other) {
		std::swap(SIZE, other.SIZE);
		std::swap(TOP, other.TOP);
		std::swap(DATA, other.DATA);
	}
};