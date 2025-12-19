#include<iostream>
#include"set.h"
int main() {
	std::cout << "HEllow";

	set<int> s1;
	int val = 10;
	int val2 = 12;
	
	s1.insert(val);
	s1.insert(val2);
	set<int>::iterator pos;
	pos = s1.begin();
	//std::cout << "value: " << *pos;
	//++pos;
	//std::cout << "value: " << *pos;
	////////////////////////////////
	set<int>::reverse_iterator rit;
	rit = s1.rend();

	std::cout << "value: " << *rit;
	++rit;
	std::cout << "value: " << *rit;

	++rit;
	std::cout << "value: " << *rit;

	return 0;
}