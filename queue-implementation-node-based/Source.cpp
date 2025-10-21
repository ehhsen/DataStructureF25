#include<iostream>
#include"queue.h"
int main() {
    queue<int> q;

    std::cout << "Queue created. Is empty? " << (q.empty() ? "Yes" : "No") << std::endl;

    // Push elements
    int v = 10, v1 = 20, v2 =30, v4 =40;
    q.push(v);
    q.push(v1);
    q.push(v2);

    std::cout << "After pushing 10, 20, 30:\n";
    std::cout << "Front element: " << q.front() << std::endl;
    std::cout << "Back element: " << q.back() << std::endl;
    std::cout << "Queue size: " << q.size() << std::endl;

    // Pop one element
    q.pop();
    std::cout << "\nAfter one pop:\n"<<std::endl;
    std::cout << "Front element: " << q.front() << std::endl;
    std::cout << "Queue size: " << q.size() << std::endl;

    // Push another element
    q.push(v4);
    std::cout << "\nAfter pushing 40:\n";
    std::cout << "Back element: " << q.back() << std::endl;
    std::cout << "Queue size: " << q.size() << std::endl;

    // Pop all elements
    q.pop();
    q.pop();
    q.pop();

    std::cout << "\nAfter popping all elements:\n";
    std::cout << "Is queue empty? " << (q.empty() ? "Yes" : "No") << std::endl;
}