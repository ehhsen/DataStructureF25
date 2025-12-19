#include<iostream>
#include"map.h"
int main() {
	std::cout << "meow";
	map<int, int> m;
	m.insert({1,1});
	m.insert({ 2,4 });
	m.insert({ 3,9 });
	std::cout <<" value: " << m.at(2) << std::endl;
	m[3] = 10;

}

