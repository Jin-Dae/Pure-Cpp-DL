// src/main.cpp
#include <iostream>
#include "Matrix.h"
#include "Activation.h"

int main() {
    try {
        // 1. 테스트용 2x2 행렬 생성
        Matrix input(2, 2);
        input(0, 0) = 1.0;   // 양수
        input(0, 1) = -2.0;  // 음수
        input(1, 0) = 0.5;   // 작은 양수
        input(1, 1) = -0.1;  // 작은 음수

        std::cout << "=== Original Input ===" << std::endl;
        std::cout << input << std::endl;

        // 2. ReLU 테스트 (음수가 사라져야 함)
        Matrix relu_out = Activation::relu(input);
        std::cout << "=== After ReLU (Negative -> 0) ===" << std::endl;
        std::cout << relu_out << std::endl;

        // 3. Sigmoid 테스트 (모두 0~1 사이로 변해야 함)
        Matrix sigmoid_out = Activation::sigmoid(input);
        std::cout << "=== After Sigmoid (Squeezed 0~1) ===" << std::endl;
        std::cout << sigmoid_out << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}