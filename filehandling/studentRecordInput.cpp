#include<iostream>
#include<fstream>
struct students{
	int reg;
	int sem;
	char name[50];
};
int main() {
	students s;
	char choice = 'y';
	std::fstream file("studentRecord.txt", std::ios::app | std::ios::out | std::ios::binary);
	if(file.is_open()){
		std::cout << "File opened successfully\n";
	
		/////entering student details
		std::cout << "Student's Record System";
		do {
			std::cout << "Enter Students Name: ";
			std::cin >> s.name;
			std::cout << "Enter Students Registration Number: ";
			std::cin >> s.reg;
			std::cout << "Enter Students Semester: ";
			std::cin >> s.sem;
			file.write((char*)&s, sizeof(s));
			std::cout << "Do you want to add more records? (y/n): ";
			std::cin >> choice;

		}
		while (choice == 'y' || choice == 'Y');	
	}
	else{
		std::cout << "Error opening file\n";
		return 1;
	}
}