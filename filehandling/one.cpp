#include<iostream>
#include<fstream>
int main() {
	std::ofstream file("one.bin", std::ios::binary);
	//file << "Hello, World!" << std::endl;
	char data[50] = "hello jee";
	file.write((char*)&data, sizeof(data);
	file.close();
	return 0;
}