#pragma once


template <typename T>
class stack {
private:
	int SIZE;
	T TOP;
	T* DATA;
public:
	template<typename T>
	friend bool operator==(const stack<T>&, const stack<T>&);
	template <typename T>
	friend bool operator< (const stack<T>&, const stack<T>&);

	stack(int s = 10) {
		TOP = -1;
		SIZE = s;
		DATA = new T[SIZE];
	}
	~stack() {
		delete[] DATA;

	}

	T top() const {
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
template <typename T>
bool operator == (const stack<T> &lhs, const stack<T> &rhs) {
	bool check = true;
	// will be equal when size and elements are same
	if (lhs.SIZE == rhs.SIZE) {
		for (int i = 0; i < lhs.SIZE; i++) {
			if (lhs.DATA[i] == rhs.DATA[i]) {
				check = true;
			}		
			else {
				return false;	
			}
		return true;	
		}
	}
	else {
		return false;
	}
}
template <typename T>
bool operator< (const stack<T>&lhs , const stack<T>&rhs ) {
	bool check = true;

		for (int i = 0; i < lhs.SIZE; i++) {
			if (lhs.DATA[i] = rhs.DATA[i]) {
				check = true;
			}
			else
				check = false;
		}
		return check;	
}
