#include <iostream>

#include "include.h"


int main() {
    Vec3 test(12,123,4124.23);
    std::cout << test.getMagnitude()<< std::endl ;
    --test;
    std::cout << test.getMagnitude()<< std::endl;

}

