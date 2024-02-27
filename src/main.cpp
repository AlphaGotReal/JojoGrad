#include <iostream>
#include "single.hpp"

int main(int argc, char **argv) {

    reverse_mode::variable u(2);
    reverse_mode::variable v(10);

    reverse_mode::add a(&u, &v);
    a.backward(1.0);

    std::cout << a.forward() << std::endl;

    std::cout << "gradients wrt u and v: ";
    std::cout << u.gradient << ", ";
    std::cout << v.gradient << std::endl;

    return 0;
}


