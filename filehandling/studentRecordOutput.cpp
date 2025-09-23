#include<iostream>
#include<fstream>
struct students {
	int reg;
	int sem;
	char name[50];
};

int main() {
	students s;
	char choice = 'y';
	std::fstream file("studentRecord.txt", std::ios::app | std::ios::in | std::ios::binary);
	if (file.is_open()) {
		std::cout << "File opened successfully\n";
		/////reading student details
		std::cout << "Student's Record System\n";
		std::cout << "The records in the file are:\n";
		while (file.read((char*)&s, sizeof(s))) {
			std::cout << "Name: " << s.name << "\n";
			std::cout << "Registration Number: " << s.reg << "\n";
			std::cout << "Semester: " << s.sem << "\n";
			std::cout << "--------------------------\n";
		}
	}
	else {
		std::cout << "Error opening file\n";
		return 1;
	}
}