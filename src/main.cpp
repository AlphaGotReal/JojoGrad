#include <iostream>
#include "jojograd/variable.hpp"

int main(int argc, char **argv) {

    jojo::variable<double> a(10);
    jojo::variable<double> b(2);
   
    jojo::variable<double> c = a * b;
    jojo::variable<double> d = c / b;

    d.backward(1.0);

    std::cout << d.grad << std::endl;
    std::cout << c.grad << std::endl;
    std::cout << b.grad << std::endl;
    std::cout << a.grad << std::endl;

    return 0;
}

