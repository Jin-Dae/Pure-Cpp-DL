#include <iostream>
#include "Matrix.h"

int main() {
    try {
        std::cout << "=== Day 4-2: Math Operators Check ===" << std::endl;

        Matrix A(2, 2);
        A(0,0)=1.0; A(0,1)=2.0;
        A(1,0)=3.0; A(1,1)=4.0;

        Matrix B(2, 2);
        B(0,0)=0.5; B(0,1)=0.5;
        B(1,0)=0.5; B(1,1)=0.5;

        // 1. 뺄셈 테스트 (1 - 0.5 = 0.5)
        std::cout << "1. Subtraction (A - B):" << std::endl;
        std::cout << (A - B) << std::endl;

        // 2. 스칼라 곱 테스트 (A * 0.1) -> [0.1, 0.2 ...]
        std::cout << "2. Scalar Multiply (A * 0.1):" << std::endl;
        std::cout << A*0.1 << std::endl;

        // 3. 아다마르 곱 테스트 (같은 위치끼리 곱하기)
        // [1*0.5, 2*0.5] -> [0.5, 1.0]
        std::cout << "3. Hadamard (A * B element-wise):" << std::endl;
        std::cout << A.hadamard(B) << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}