#include <cmath>
#include <vector>
#include <exception>
#include <stdexcept>

namespace jojo {

    /*
        invalid operation class
        just a custom exception class
    */
    class invalid_operation: public std::exception {
    public:
        const char *what() const noexcept override {
            return "an invalid operation was performed!\n";
        }
    };

    /*
        operation class
        maps tokens to the respective operations
    */
    class operation {
    public:
        int token;
        /*
            token: operation
            0: +
            1: *
            2: -
            3: /
        */
        operation();
        operation(int token);
        
        template<typename T>
        T perform(T v1, T v2);
    };

    operation::operation() {
        this->token = -1;
    }

    operation::operation(int token) {
        this->token = token;
    }

    template<typename T> 
    T operation::perform(T v1, T v2) {
        switch (this->token) {
            case 0: return v1 + v2;
            case 1: return v1 * v2;
            case 2: return v1 - v2;
            case 3: return v1 / v2;
            default: throw invalid_operation();
        }
    }

    /*
        variable class
        the main class that acts as the node class for the computational graph
    */
    template<typename T>
    class variable {
    public:
        T data;
        double grad;
        
        variable();
        variable(T data);
        
        variable operator+(variable<T> &var);
        variable operator*(variable<T> &var);
        variable operator-(variable<T> &var);
        variable operator-();
        variable operator/(variable<T> &var);

        void backward(double gradient);

    // private:
        /*
            Every complex variable can be broken into a binary operation of other two variable at least
        */
        std::vector<variable<T> *> children; // children.size() <= 2
        operation op; // operation performed on children[0] and children[1] to get (*this)
    };

    template<typename T>
    variable<T>::variable() {
        this->data = (T)0;
        this->grad = 0.0;
    }

    template<typename T>
    variable<T>::variable(T data) {
        this->data = data;
        this->grad = 0.0;
    }

    template<typename T>
    variable<T> variable<T>::operator+(variable<T> &var) {
        variable<T> res(this->data + var.data);

        res.children.push_back(this);
        res.children.push_back(&var);
        res.op.token = 0;
        
        return res;
    }

    template<typename T>
    variable<T> variable<T>::operator*(variable<T> &var) {
        variable<T> res(this->data * var.data);

        res.children.push_back(this);
        res.children.push_back(&var);
        res.op.token = 1;
        
        return res;
    }
    
    template<typename T>
    variable<T> variable<T>::operator-(variable<T> &var) {
        variable<T> res(this->data - var.data);
        
        res.children.push_back(this);
        res.children.push_back(&var);
        res.op.token = 2;
        
        return res;
    }
    template<typename T>
    variable<T> variable<T>::operator/(variable<T> &var) {
        variable<T> res(this->data / var.data);
        
        res.children.push_back(this);
        res.children.push_back(&var);
        res.op.token = 3;
        
        return res;
    }
    
    template<typename T>
    variable<T> variable<T>::operator-() {
        variable<T> res(-this->data);
        
        res.children.push_back(this);
        res.op.token = 2;
        
        return res;
    }

    // The automatic differentiation...........
    template<typename T>
    void variable<T>::backward(double gradient) {
        this->grad += gradient;

        if (this->children.size() == 0) return ;

        if (this->children.size() == 1) {
            // this is the case where f(x) = x or f(x) = -x;

            double prev_gradient;
            if (this->op.token == -1) {          // case: f(x) = x
                prev_gradient = this->grad;
            }else if (this->op.token == 2) {     // case: f(x) = -x
                prev_gradient = -this->grad;
            }

            this->children[0]->backward(prev_gradient);
            return ;
        }

        // case of binary operation
    
        if (this->op.token == 0) {
            this->children[0]->backward(this->grad);
            this->children[1]->backward(this->grad);
        }else if (this->op.token == 1) {
            this->children[0]->backward(this->grad * this->children[1]->data);
            this->children[1]->backward(this->grad * this->children[0]->data);
        }else if (this->op.token == 2) {
            this->children[0]->backward(this->grad);
            this->children[1]->backward(-this->grad);
        }else if (this->op.token == 3) {

            if (this->children[1]->data == 0) {
                throw std::runtime_error("division by zero!");
            }

            this->children[0]->backward(this->grad * (double) (1 / this->children[1]->data));
            this->children[1]->backward(-this->grad * (double) (this->children[0]->data / (this->children[1]->data * this->children[1]->data)));
        }else {
            throw invalid_operation();
        }

    }
};

