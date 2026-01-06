#pragma once
#include<queue>
template <typename T>
class priority_queue {
private:
	int n;
	int SIZE;
	T* data;
	void ReheapDown(T data[], int first, int last) {
		int lc, rc, mc;
		rc = (2 * first) + 2;
		lc = (2 * first) + 1;
		mc = lc;
		while (lc <= last) {
			if (rc <= last && data[rc] > data[lc]) {
				mc = rc;
			}
			if (data[first] < data[mc]) {
				std::swap(data[first], data[mc]);
				first = mc;
				rc = (2 * first) + 2;
				lc = (2 * first) + 1;
				mc = lc;
			}
			else {
				break;
			}
		}

	}
	void ReheapUp(T data[], int first, int last)  {
		
		while (last > first) {
			int p = (last - 1) / 2;
			if (data[p] < data[last]) {
				std::swap(data[p], data[last]);
				last = p;
			}
			else {
				break;
			}
		}
	}
public:
	priority_queue(int s = 100) {
		SIZE = s;
		data = new T[SIZE];
		n = 0;
	}
	~priority_queue() {
		delete[]data;
	}
	// operator = will be copying array from other to this object
	T top()const {return data[0];}

	bool empty()const {return n == 0;}

	int size()const {return n;}

	void push(const T& val) {
		if (n == SIZE) {
			throw("PQ overflow");
		}
		data[n] = val;
		ReheapUp(data, 0, n); 
		++n;
	}
	void pop() {
		if (empty()) {
			throw("PQ underflow");
		}
		data[0] = data[n-1];
		ReheapDown(data, 0, n - 2);
		--n;
	}
};