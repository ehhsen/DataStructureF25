#include<iostream>
//#include<unordered_map>
#include"unordered_map.h"
int main() {
	unordered_map<int, int > um, um1;
	um.insert({1, 1});
	um.insert({ 2, 4 });
	um.insert({ 3, 9 });
	um.insert({ 4, 16 });
	//unordered_map<int, int>::iterator it;
	//it = um.begin();
	//++it;
	//um.erase(it);
	//while (it != um.end()) {
	//	std::cout << it->first;
	//	std::cout << it->second<<std::endl;
	//	++it;
	//}

	//um1.swap(um);
	//unordered_map<int, int>::iterator it;
	//it = um1.begin();
	////++it;
	//while (it != um1.end()) {
	//	std::cout << it->first;
	//	std::cout << it->second<<std::endl;
	//	++it;
	//}

	std::cout<<"key 1 : "<<um.at(3);

	
	//um.find(1);
	return 0;
}
