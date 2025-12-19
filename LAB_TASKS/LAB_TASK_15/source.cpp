//#include<iostream>
//#include<unordered_map>
//#include<cctype>
//int main() {
//
//	//PART 2
//	std::unordered_map<int, int> um;
//	
//	int x;
//	unsigned int SIZE;
//
//	int greatest = 0;  // element with most freq
//	
//
//
//	std::cin >> SIZE;
//
//	for (int i = 0; i < SIZE; ++i) {
//		std::cin >> x;
//		um[x] = um[x] + 1;		
//	}
//	for (int i = 0; i < SIZE; ++i) {
//		if (um[i] > greatest) {
//			greatest = um[i];
//			x = i;
//		}
//		else if (um[i] == greatest) {
//			if (um[x] > um[i]) {
//				greatest = um[i];
//				x = i;
//			}
//		}
//	}
//	std::cout << x;
//
//}