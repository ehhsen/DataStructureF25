
// forward_list1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"forward_list.h"
template <typename T>
void display(forward_list<T>& f) {
    while (!f.empty()) {
        std::cout << f.front() <<" "<<std::endl;
        f.pop_front();
    }
}
int main()
{
    std::cout << "\nHello World!\n" << std::endl;

    forward_list<int> f, f2;
    //std::cout << f.empty();

    f.push_front(8);
    f.push_front(5);
    f.push_front(2);
    f.push_front(1);
    //std::cout << f.front() << std::endl;

    f2.push_front(9);
    f2.push_front(6);
    f2.push_front(4);
    f2.push_front(3);
    //std::cout << f2.front() << std::endl;
    
 /*   while (!f.empty()) {
        std::cout << f.front();
        f.pop_front();
    }*/
 /*   int NEW_SIZE = 8;
    f.resize(NEW_SIZE);
       while (!f.empty()) {
         std::cout << f.front();
         f.pop_front();
     }*/

       //int N = 3;
       //f.resize(N );
       //std::cout << "\n resizing";
       // while (!f.empty()) {
       //       std::cout << f.front();
       //       f.pop_front();
       //   }
    //display(f);
    //std::cout << std::endl;
    //display(f2);
    f.merge(f2); 
    //std::cout<< f.size() << std::endl;
    //std::cout<<f.
    while (!f.empty()) {
        std::cout << f.front() << std::endl;
        f.pop_front();
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
