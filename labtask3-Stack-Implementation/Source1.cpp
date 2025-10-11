#include<iostream>
#include"stack.h"
//#include<stack>
int main() {
	//std::cout << "hello";
	stack <char> stk1, stk2;
	stack <int> stk3, stk4;
	stk1.push('a');
	stk1.push('b');
	stk1.push('c');

	stk2.push('a');
	stk2.push('b');
	stk2.push('c');
	 
	stk3.push(1);
	stk3.push(2);
	//stk3.push(3);

	stk4.push(1);
	stk4.push(2);
	stk4.push(3);



	bool LESS = stk1 < stk2;
	bool LESSINT = stk3 < stk4;
	bool COMPARE = ( stk1==stk2);
	
	if (COMPARE) {
		std::cout << "stk1 is equal to stk2 " << std::endl;
	}
	else {
		std::cout << "stk1 is not equal to stk2 ";
	}

	if (LESS ) {
		std::cout << "first stack is LESS THAN second stack \n";
	}
	else {
		std::cout << "first  is not LESS THAN second stack \n";
	}
	if (LESSINT) {
		std::cout << "stack 3 is less than stack stack 4";
	}
	
	return 0;
	
}