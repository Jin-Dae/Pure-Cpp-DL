#include <iostream>
#include "Matrix.h"
#include "Activation.h"

int main() {
    try {
        std::cout << "=== Day 4: Backprop Tools Check ===" << std::endl;

        // 1. Transpose 테스트
        Matrix A(2, 3);
        A(0,0)=1; A(0,1)=2; A(0,2)=3;
        A(1,0)=4; A(1,1)=5; A(1,2)=6;
        
        std::cout << "Original Matrix (2x3):" << std::endl;
        std::cout << A << std::endl;

        std::cout << "Transposed Matrix (3x2):" << std::endl;
        // 행과 열이 뒤집혀야 함
        std::cout << A.transpose() << std::endl;

        // 2. 미분 함수 테스트
        std::cout << "ReLU Derivative (Input: -1, 2):" << std::endl;
        Matrix B(1, 2);
        B(0,0) = -1.0; B(0,1) = 2.0;
        // -1은 0이 되고, 2는 1이 되어야 함
        std::cout << Activation::reluDerivative(B) << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}