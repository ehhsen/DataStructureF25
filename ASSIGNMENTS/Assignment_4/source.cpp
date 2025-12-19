#include"list.h"
#include<iostream>
int main() {
	list<int> l, l2;
	l.push_front(1);
	l.push_front(2);
	l.push_front(3);
	l.push_front(4);
	l.push_front(5);
	l.reverse();

	list<int>::iterator it = l.begin();
	while (it != l.end()) {
		std::cout << " val: " << *it << std::endl;
		++it;
	}
	

	/*l.resize(7);*/
	//l2.swap(l);
	

	//l2.push_front(1);
	//l2.push_front(5);
	//l2.push_front(5);
	//l2.push_front(5);
	//l2.push_front(1);
	//l2.push_front(5);

	//l.merge(l2);
	//std::cout << "front of l2: " << l2.front()<<"-----";
	//std::cout << "size: " << l2.size();
	//
	/*bool equal = (l == l2);
	std::cout << equal;*/



	//list<int>::iterator it2 = l2.begin();
	//while (it2 != l2.end()) {
	//	std::cout << " val 2: " << *it2 << std::endl;
	//	++it2;
	//}
	//l2.remove(1);
	//std::cout << "after removing" << std::endl;

	//it2 = l2.begin();
	//while (it2 != l2.end()) {
	//	std::cout << " val 2: " << *it2 << std::endl;
	//	++it2;
	//}

	//l.splice(l.begin(), l2);

	//it = l.begin();
	//while (it != l.end()) {
	//	std::cout << " val: " << *it << std::endl;
	//	++it;
	//}

	//l.push_front(11);
	//l.push_front(8);
	/*
	std::cout<<" front value: "<<l.front();
	std::cout << " back value: " << l.back();
	std::cout << "size: " << l.size();
	l.empty() == true ? std::cout << "Empty" : std::cout << "not empty";*/

	//l.pop_back();
	//std::cout << "size: " << l.size();
	//std::cout << " back value: " << l.back();


	// verify begin and end member functions
	//list<int>::iterator it = l.end();

	/*++it;
	++it;
	std::cout << "value: " << *it;
	return 0;*/

	//verify rbegin and rend 
	//list<int>::reverse_iterator rit = l.rend();
	//std::cout << "value: " << *rit;
	//++rit;
	//std::cout << "value: " << *rit;

	/*l.clear();
	std::cout << "size: " << l.size();
	l.empty() == true ? std::cout << "\nEmpty" : std::cout << "not empty"; */

	//list<int>::iterator it = l.end();
	//
	//list<int>::iterator pos = l.erase(it);
	///*list<int>::iterator it;*/
	////it = l.insert(pos, 22);


	//std::cout << "value: " << *pos;
	return 0;	

}