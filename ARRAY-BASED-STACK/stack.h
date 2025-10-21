#pragma once
template<typename T>
class stack {
private:
	T TOP;
	int SIZE; //of array
	T *DATA;
public:
	stack() {
		SIZE = 10;
		DATA = new T[SIZE];
		TOP = -1;
	}
	////////////////////////////////////////////////
	~stack() {
		delete[] DATA;
	}
	////////////////////////////////////////////////
	T top()const {
		if (TOP == -1) 
			throw("stack underflow");
		else
			return DATA[TOP];
	}
	////////////////////////////////////////////////
	void push(T& val) {
		if (TOP > SIZE) {
			throw("stack overflow");
		}
		else {
			++TOP;
			DATA[TOP] = val;
		}
	}
	////////////////////////////////////////////////
	void pop() {
		if (TOP == -1) {
			throw("Stack Underflow");
		}
		else {
			--TOP;
		}
	}
	/////////////////////////////////////////////
	bool empty()const {
		return TOP == -1;
	}
	///////////////////////////////////////////////////
	int size()const {
		return TOP + 1;
	}
	/////////////////////////////////////////////////
	void swap(stack& other) {
		std::swap(*this, other);
	}
	/////////////////////////////////////////////////
	stack<T>& operator= (const stack<T> other) {
		delete[] DATA;
		TOP = other.TOP;
		SIZE = other.SIZE;
		DATA = new T[SIZE];
		for (int i = 0; i <= TOP; ++i) {
			DATA[i] = other.DATA[i];
		}
		return *this;
	}
};