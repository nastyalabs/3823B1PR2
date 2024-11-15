// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
//
//
//
//
#include <iostream>


#ifndef SAMPLE1 //

#include "prefixModule.h"

int main() {
    try {
        setlocale(LC_ALL, "Russian");
        normalArith temp;
        std::cin >> temp;
        PrefixModule a(temp);
        std::cout << std::endl << a.get_prefix();
        std::cout << std::endl;
        std::cout << "Enter the amount of steps" << std::endl;
        size_t n;
        std::cin >> n;
        for (size_t i = 0; i < n; i++) {
            std::cout << std::endl << a.step_push();
        }
    }
    catch (const char* str) {
        for (int i = 0; i < 3; i++) {
            std::cout << str[i];
        }
    }

}
#endif
