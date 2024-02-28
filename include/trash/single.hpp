#include <iostream>
#include <cmath>

namespace reverse_mode {

    class variable {
    public:
        double data;
        double gradient;
        variable();
        variable(double data);
        double forward();
        void backward(double gradient);
    };

    class add {
    public:
        variable *left;
        variable *right;
        add(variable *left, variable *right);
        double forward();
        void backward(double gradient);
    };
};

reverse_mode::variable::variable() {
    this->data = 0.0;
    this->gradient = 0.0;
}

reverse_mode::variable::variable(double data) {
    this->data = data;
    this->gradient = 0.0;
}

double reverse_mode::variable::forward() {
    return this->data;
}

void reverse_mode::variable::backward(double gradient) {
    this->gradient += gradient;
}

reverse_mode::add::add(reverse_mode::variable *left, reverse_mode::variable *right) {
    this->left = left;
    this->right = right;
}

double reverse_mode::add::forward() {
    return this->left->forward() + this->right->forward();
} 

void reverse_mode::add::backward(double gradient) {
    this->left->backward(gradient);
    this->right->backward(gradient);
}

