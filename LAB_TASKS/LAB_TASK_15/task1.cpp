#include<iostream>
#include<unordered_map>
#include<string>
using namespace std;
int main() {
	unordered_map<int, std::string> m;
	pair<int, std::string> p;
	/*for (int i = 0; i < 3; ++i) {
		m.insert({ i, i*i });
	}*/
	m.insert({ 1, "zubair ali" });
	m.insert({ 2, "ahsan" });
	m.insert({ 3,"anas" });
	//updating existing key
	pair<unordered_map<int, std::string>::iterator, bool> UE_key;

	UE_key = m.insert(pair<int, string>{ 3, "anas" });
	if (UE_key.second == false) {
		UE_key.first->second = "mohsi";
	}
	unordered_map<int, std::string>::iterator it;
	for (it = m.begin(); it != m.end(); it++) {
		cout << it->first << ":" << it->second << endl;
	}
	//m.find(3);
	if (m.find(3) == m.end()) {
		cout << "\nnot exist";
	}
	else {
		cout << "exist";
	}