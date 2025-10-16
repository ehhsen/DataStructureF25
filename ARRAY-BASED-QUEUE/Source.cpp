#include<iostream>
#include"queue.h"
int main() {
	queue<int> q, q1;
	q.push(10);
	q.push(20);

	q1.push(11);
	q1.push(22);

	std::cout<<q.empty();
	std::cout<<"front: "<<q.front();
	q.pop();
	std::cout<<"after pop: "<<q.front();
	q.swap(q1);
	while (!q.empty()) {
		std::cout <<"printing value: " <<q.front();
		q.pop();
	}
}