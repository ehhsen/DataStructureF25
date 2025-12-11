// stack-pactise.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "stack.h"

int main(){

    std::cout << "Hello World!\n";
    stack stk(5);
    stack stk1(2);
    stk1.push(9);
    stk1.push(6);
    
    stk.push(5);
    stk.push(4);
    stk.push(3);
    stk.push(2);
    stk.push(1);
    stk1.swap(stk);
    while (!stk.empty()) {
        std::cout <<"  "<<stk.top();
        stk.pop();
    }
    
    std::cout << "swapping\n";
    while (!stk1.empty()) {
        std::cout << "  " << stk1.top();
        stk1.pop();
    }
    return 0;
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
