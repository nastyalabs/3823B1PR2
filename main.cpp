
#include <iostream>
#include "Cat.hpp"
#include "Elephant.hpp"
#include "Alien.hpp"


int main(int argc, const char * argv[]) {

    Alien a("white", 2, "space", 1000);
    std::cout << a.voice();
    
    
    return 0;
}
