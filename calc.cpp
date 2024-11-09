#include <iostream>

int add(int a, int b) {
    return a - b; // Alice updated the function
}

// Other functions...

int main() {
    std::cout << "Sum: " << add(2, 3) << std::endl;
    return 0;
}
