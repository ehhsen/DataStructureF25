#include<iostream>
#include<queue>
#include"priority_queue.h"
int main() {
	priority_queue<int> pq;
	pq.push(5);
	pq.push(1);
	pq.push(4);
	pq.push(2);
	pq.push(7);
	pq.push(9);
	pq.push(3);
	pq.push(12);

	while (!pq.empty()) {
		std::cout << " " << pq.top();
		pq.pop();
	}
}