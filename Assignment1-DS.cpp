// Assignment1-DS.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>

void wrongss(int arr[], const int SIZE1) {
  
    for (int i = 0; i < SIZE1-1; i++) {
        for (int j = i+1; j < SIZE1; j++) {
             if (arr[j] < arr[i]) {
                std::swap(arr[j], arr[i]);
            }
        }
    }
    for (int i = 0; i < SIZE1; i++) {
        std::cout << arr[i] << " ";
    }
    
}
void correctss(int arr[], const int SIZE1){

    for (int i = 0; i < SIZE1-1; i++){
        int MININDEX = i;
        for (int j = i + 1; j < SIZE1; j++) {
            if (arr[j] < arr[MININDEX]) {
                MININDEX = j;
            }

        }
        if (MININDEX != i) {
            std::swap(arr[i], arr[MININDEX]);
        }
    } 
    for (int i = 0; i < SIZE1; i++) {
        std::cout << arr[i] << " ";
    }
}
//c.Bubble sort(stop sorting, if there is no swap in an iteration)
void bubble(int arr[], const int SIZE1) {
    for (int i = 0; i < SIZE1 - 1; i++) {
        bool SWAPING = false;
        for (int j = 0; j < SIZE1 - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                SWAPING = true;
                std::swap(arr[j], arr[j + 1]);

            }
        }
        if (!SWAPING)
            break;
    }
    for (int i = 0; i < SIZE1; i++) {
        std::cout << arr[i] << " ";
    }

}
//d.Insertion sort(do not do any swapping, 
// just shift the values to appropriate positions)
void insertion( int arr[], const int SIZE1) {
    for (int i = 1; i < SIZE1; i++) {
        int MOV = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > MOV) {
            arr[j + 1] = arr[j];
           j--;

        }
        arr[j + 1] = MOV;
   }
    for (int i = 0; i < SIZE1; i++) {
        std::cout << arr[i] << " ";
    }

}
void printArray(int arr[], int SIZE) {
    for (int i = 0; i < SIZE; i++) {
        std::cout << arr[i] << " ";
    }
}


int main()
{
   /*const int SIZE1 = 5;
    int arr[SIZE1] = { 1,6,5,7,0 };*/
    //std::cout << "Hello World!\n";
    //wrongss(arr, SIZE1);
    //correctss(arr, SIZE1);
    //bubble(arr, SIZE1);
    //insertion(arr, SIZE1); 
    // 
    //e.For having average, best, and worst cases, create three arrays A, B and C.
    const int SIZEA = 10;
    int A[SIZEA];
    for (int i = 0; i < SIZEA; i++) {
        A[i] = std::rand() % 100;
    }
    printArray(A, SIZEA);
    int B[SIZEA] = { 0,1,2,3,4,5,6,7,8,9 };
    int C[SIZEA] = { 9,8,7,6,5,4,3,2,1,0 };



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

