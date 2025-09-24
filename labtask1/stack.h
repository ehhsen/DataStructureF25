#pragma once
#include<stack>
#include<iostream>
class stack {
private:
	int SIZE, TOP, *DATA;
public:
	stack( int s  =10) {
		TOP = -1;
		SIZE = s;
		DATA = new int[SIZE];
	}
	~stack() {
		delete[] DATA;

	}

	int top() {
		return DATA[TOP];
	}
	bool empty() {
		return TOP == -1;
	}
	int size() {
		return TOP + 1;
	}
	void push(const int& v) {
		++TOP;
		DATA[TOP] = v;
	}
	void pop() {
		--TOP;
	}
	void swap(stack& other) {
		std::swap(SIZE, other.SIZE);
		std::swap(TOP, other.TOP);
		std::swap(DATA, other.DATA);
	}
};
