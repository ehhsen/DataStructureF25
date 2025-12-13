#include<iostream>
#include"set.h"
int main() {
	std::cout<< "hello";
	
	set<int> s, s1;
	std::pair<set<int>::iterator, bool> added = s.insert(12);
	std::pair<set<int>::iterator, bool> added1 = s.insert(16);
	std::pair<set<int>::iterator, bool> added2 = s.insert(10);
	std::pair<set<int>::iterator, bool> added3 = s.insert(8);
	std::pair<set<int>::iterator, bool> added4 = s.insert(20);

	s1 = s;
	//std::cout << s.size() << std::endl;


	//std::pair<set<int>::iterator, bool> added2 = s.insert(12);
	//added.second == true ? std::cout << "jio jee add ho geya" : std::cout << " nahee hua:( ";
	//added2.second == true ? std::cout << "jio jee add ho geya" : std::cout << " nahee hua:( ";

	//check case 2.1
	//auto it = s.erase(added2.first);
	//std::cout << " value " << *it;
	////check case 2.2
	//auto it1 = s.erase(added4.first);
	//std::cout << " value " << *it;

	// print full tree
	auto itr = s1.begin();
	while ( itr != s1.end() )
	{
		std::cout << " val " << *itr;
		++itr;

	}
	//auto eras = s.erase(added3.first);
	//std::cout << "meow "<< *eras<<std::endl;
	//auto  itr= s.begin();
	//while (itr != s.end())
	//{
	//	std::cout << " val " << *itr;
	//	++itr;

	//}
	//s.clear();
	//std::cout << " size: " << s.size();

	return 0;
}
