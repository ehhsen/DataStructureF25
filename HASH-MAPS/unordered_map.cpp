#include<iostream>
#include<unordered_map>
#include"unordered_map.h"
int main() {
	unordered_map<int, int > um;
	um.insert({1, 1});
	um.insert({ 2, 4 });
	um.insert({ 3, 9 });
	um.insert({ 4, 16 });
	return 0;


}