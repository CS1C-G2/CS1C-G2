#include <iostream>
#include "vector.h"
#include <string>


int main() {
    myStd::vector<int> intVec;
    myStd::vector<double> doubVec;
    myStd::vector<int> intVecCopy;
    myStd::vector<double> doubVecMove;
    myStd::vector<std::string> strVec;

    //Testing push_back and copy constructor

    std::cout << "Testing push_back and copy assignment\n";

    for(int i = 0; i < 10; i++) {
        intVec.push_back(i);
    }

    intVecCopy = intVec;

    for(int i = 0; i < intVec.size(); i++) {
        std::cout << "Vector 1 at index " << i << ": " << intVec[i] << std::endl;
        std::cout << "Vector 2 at index " << i << ": " << intVecCopy[i] << std::endl;
    }

    //Testing copy constructor

    std::cout << "\nTesting push_back and copy constructor\n";

    myStd::vector<int> intVecCopyCstr(intVec);

    for(int i = 0; i < intVec.size(); i++) {
        std::cout << "Vector 1 at index " << i << ": " << intVec[i] << std::endl;
        std::cout << "Vector 2 at index " << i << ": " << intVecCopyCstr[i] << std::endl;
    }

    //Testing move assignment

    std::cout << "\nTesting move assignment\n";

    for(int i = 0; i < 5; i++) {
        doubVecMove.push_back(i + .5);
    }

   // testMoveAssgn(doubVecMove, doubVec);

   std::cout << "Assignee values pre-copy: \n";
    for(int i = 0; i < doubVec.size(); i++) {
        std::cout << doubVec[i] << std::endl;
    }
    std::cout << "Assigner values pre-copy: \n";
    for(int i = 0; i < doubVecMove.size(); i++) {
        std::cout << doubVecMove[i] << std::endl;
    }
    doubVec = std::move(doubVecMove);
    std::cout << "Assignee values post-copy: \n";
    for(int i = 0; i < doubVec.size(); i++) {
        std::cout << doubVec[i] << std::endl;
    }
    std::cout << "Assigner values post-copy: \n";
    for(int i = 0; i < doubVecMove.size(); i++) {
        std::cout << doubVecMove[i] << std::endl;
    }

    std::cout << "\nTesting that it works with different types (string)\n";

    for (int i = 65; i < 71; i++) {  // ASCII values for uppercase letters
            char ch = static_cast<char>(i);  // Convert ASCII value to character
            strVec.push_back(std::string(1, ch));  // Enqueue the character as a string
        }

    for(int i = 0; i < strVec.size(); i++) {
        std::cout << strVec[i] << std::endl;
    }


    // Test iterators in vector class
    std::cout << "\nTesting iterators in vector\n";

    std::cout << "intVec: ";
    for(int i = 0; i < intVec.size(); i++) {
        std::cout << intVec[i] << " ";
    }
    std::cout << std::endl;

    myStd::vector<int>::iterator it = intVec.begin();

    std::cout << "Vector elements after iterator: ";
    while (it != intVec.end()) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;


}
