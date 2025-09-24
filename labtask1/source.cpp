#include<iostream>
#include<fstream>
#include "stack.h"
int main(int argc, char** argv) {
	int left = 0;
	int right = 0;

	std::ifstream file;
	if (argc == 2) {
		file.open(argv[1], std::ios::in);
		//std::cout << "Two arg passed";
	}
	else {
		std::cout << "Usage: \nfilename.cpp <nameoffile to be checked for {} ";
	}
	
	if (!file) {
		std::cout << "Error in opening file!!!" << std::endl;
		return 0;
	}
	else
	{
		//std:: cout << "in else block";
		
		stack s;
		stack s1;
		stack s2;
		/// loop to read contents of file
		while (!file.eof()) {
			char ch;
			
			file.get(ch);
				if (ch == '{') {
					s.push(1);
					++left;
				}
				else if (ch == '}') {
					s.pop();
					++right;
				}
		}
		file.close();
		if (s.top() == -1) {
			std::cout << "Balanced" << std::endl;
		}
		else {
			std::cout << "Not Balanced" << std::endl;
			std::cout << " left : " << left << " right: " << right;
		}

	}
	return 0;
}