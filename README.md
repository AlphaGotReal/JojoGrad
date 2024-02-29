# JojoGrad: Automatic Differentiation Library

JojoGrad is a C++ library for automatic differentiation, primarily designed for gradient computation in computational graphs. It allows users to define differentiable variables and perform operations on them, with automatic computation of gradients using the backpropagation algorithm.

## Features

- Define differentiable variables of various data types (e.g., `double`, `float`, etc.).
- Perform common mathematical operations such as addition, multiplication, subtraction, and division on variables.
- Support for unary and binary operations.
- Automatic computation of gradients using the backpropagation algorithm.
- Support for arbitrary computational graphs with multiple inputs and outputs.

## Setup

```zsh
$ git clone https://github.com/AlphaGotReal/JojoGrad.git
$ ~cd JojoGrad

# just to compile and run it fresh
$ rm -rf build/*

$ chmod 777 jomake jorun
$ ./jomake
$ ./jorun
# make your changes to src/main.cpp
```

## Usage

To use JojoGrad in your project, follow these steps:

1. **Include the Library**: Add the `jojograd` directory to your project and include the necessary header files in your source files.

2. **Define Variables**: Define differentiable variables using the `jojo::variable` class. For example:
   ```cpp
   jojo::variable<double> a(5.0);
   jojo::variable<double> b(10.0);

   jojo::variable<double> c = a * b;
   c.backward(1.0); // Compute gradients with respect to a and b

   std::cout << "Gradient of a: " << a.grad << std::endl;
   std::cout << "Gradient of b: " << b.grad << std::endl;

