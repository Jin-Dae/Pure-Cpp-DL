#include <iostream>
#include "Matrix.h"
#include "Activation.h"

int main() {
    try {
        std::cout << "=== Day 3: Forward Propagation Simulation ===" << std::endl;

        // -----------------------------------------
        // 1. 데이터 준비 (Input Layer)
        // -----------------------------------------
        // 입력 데이터 (1x2): [0.9, 0.1]
        Matrix X(1, 2);
        X(0, 0) = 0.9; 
        X(0, 1) = 0.1;

        std::cout << "[Input X]" << std::endl;
        std::cout << X << std::endl;

        // -----------------------------------------
        // 2. 은닉층 계산 (Hidden Layer)
        // -----------------------------------------
        // 가중치 W1 (2x3): 입력 2개를 은닉 3개로 연결
        Matrix W1(2, 3);
        W1(0,0) = 0.5; W1(0,1) = -0.3; W1(0,2) = 0.8;
        W1(1,0) = 0.2; W1(1,1) = 0.4;  W1(1,2) = -0.1;

        // 편향 B1 (1x3): 은닉 뉴런 3개 각각에 더해줄 값
        Matrix B1(1, 3);
        B1(0,0) = 0.1; B1(0,1) = 0.1; B1(0,2) = 0.1;

        // 계산: Z1 = X * W1 + B1
        Matrix Z1 = (X * W1) + B1;
        
        // 활성화: A1 = ReLU(Z1) (음수는 제거)
        Matrix A1 = Activation::relu(Z1);

        std::cout << "[Hidden Layer Output (ReLU)]" << std::endl;
        std::cout << A1 << std::endl;

        // -----------------------------------------
        // 3. 출력층 계산 (Output Layer)
        // -----------------------------------------
        // 가중치 W2 (3x1): 은닉 3개를 출력 1개로 연결
        Matrix W2(3, 1);
        W2(0,0) = 0.5; 
        W2(1,0) = -0.5; 
        W2(2,0) = 1.0;

        // 편향 B2 (1x1)
        Matrix B2(1, 1);
        B2(0,0) = -0.2;

        // 계산: Z2 = A1 * W2 + B2 (은닉층의 결과 A1이 입력이 됨)
        Matrix Z2 = (A1 * W2) + B2;

        // 활성화: Output = Sigmoid(Z2) (0~1 확률값 변환)
        Matrix Output = Activation::sigmoid(Z2);

        std::cout << "[Final Prediction (Sigmoid)]" << std::endl;
        std::cout << Output << std::endl;


    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}