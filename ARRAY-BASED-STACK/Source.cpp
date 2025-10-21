#include<iostream>
#include"stack.h"
int main() {
	stack<int> stk;
	stack<int> stk1;
	
	int v1 =10;
	int v2 = 20;
	int v3 = 30;
	int v4 = 40;
	stk.push(v1);
	stk.push(v2);
	stk.push(v3);
	stk.push(v4);
	
	stk1.push(v2);
	stk1.swap(stk);


	//std::cout << "Size: " << stk.size()<<std::endl;
	//std::cout << "Top: " << stk.top() << std::endl;


	//while (!stk.empty()) {
	//	std::cout << "Top: " << stk.top() << std::endl;
	//	stk.pop();
	//}

	/*std::cout << "Size of 2nd: " << stk1.size() << std::endl;
	std::cout << "Top of 2nd: " << stk1.top() << std::endl;*/
	stack<int> s;
	s.push(v3);
	s = stk1;
	std::cout << "Size of 2nd: " << s.size() << std::endl;
	std::cout << "Top of 2nd: " << s.top() << std::endl;
	return 0;

}