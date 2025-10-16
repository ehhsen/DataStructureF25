#pragma once
template< typename T>
class queue {
private:
	int F, B;
	int SIZE;
	T* DATA;
	int n;
public:
	queue(int s = 10) {
		F = B = n = 0;
		SIZE = s + 1;
		DATA = new T[SIZE];
	}
	~queue() {
		delete[] DATA;
	}
	T front()const {
		if (empty()) {
			throw("Queue Underflow");
		}
		else {
			return DATA[(F + 1) % SIZE];
		}
	}
	T back()const {
		if (empty()) {
			throw("Queue Underflow");
		}
		else {
			return DATA[B];
		}
	}


	void push(const T& val) {
		if ((B + 1 == SIZE) || ((B + 1) % SIZE == F)) {
			throw("Queue Overerflow");
		}
		else {
			B = B + 1 % SIZE;
			DATA[B] = val;
			n++;
			SIZE++;
		}
	}
	void pop(){
		if (empty()) {
			throw("Queue Underflow");
		}
		else {
			F = F + 1 % SIZE;
			--n;
		}
	}
	bool empty()const {
		return F == B;
	}
	int size()const {
		return n;
	}
	void swap(queue<T>& other) {
		std::swap(F, other.F);
		std::swap(B, other.B);
		std::swap(SIZE, other.SIZE);
		std::swap(DATA, other.DATA);
	}
};