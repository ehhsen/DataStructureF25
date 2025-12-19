#include<iostream>
#include<unordered_map>
#include<cctype>
int main() {
	std::string s;
	std::unordered_map<char, int> um;
    std::cout << "Enter string : ";
   std::cin >> s;
    
   for (int i = 0; i < s.length(); ++i) {
            s[i] = tolower(s[i]);
            um[s[i]] = um[s[i]] + 1;
    }
   for (int i = 0; i < s.length(); ++i) {
       if (um[s[i]] == 1) {
           std::cout<<s[i];
           return 0;
      }
      
   }
   std::cout << -1;

   return 0;

}