#include <iostream>

int add(int a, int b);
int mul(int a, int b);
int sub(int a, int b);
int div(int a, int b);

int main() {
    int result = add(4, 5);
    int result_mul = mul(4, 5);
    int result_sub = sub(4, 5);
    int result_div = div(4, 5);

    std::cout << "The result of add is " << result << std::endl;
    std::cout << "The result of mul is " << result_mul << std::endl;
    std::cout << "The result of sub is " << result_sub << std::endl;
    std::cout << "The result of div is " << result_div << std::endl;

    return 0;
}
// Wrapper functions for sine and cosine using std::sin and std::cos
double sine(double x) {
    return std::sin(x);
}

// Function definitions
int add(int a, int b) {
    return a + b;
}


int mul(int a, int b) {
    return a * b;
}

int sub(int a, int b) {
    return a - b;
}

int div(int a, int b) {
    if (b != 0) {
        return a / b;
    } else {
        std::cerr << "Division by zero error!" << std::endl;
        return 0;  // Handle division by zero appropriately
    }
}
