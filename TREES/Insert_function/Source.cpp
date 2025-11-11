#include<iostream>
#include"set.h"
int main() {
	std::cout << "HEllow";

	set<int> s1;
	int key = 10;
	int key1 = 12;
	s1.insert(key);
	s1.insert(key1);

	return 0;
}