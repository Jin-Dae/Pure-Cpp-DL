#include <iostream>
#include <vector>
#include "Matrix.h"
#include "Activation.h"

int main() {
    try {
        std::cout << "=== Day 4 Final: Training Simulation ===" << std::endl;

        // 1. 데이터 설정
        // ------------------------------------
        Matrix X(1, 2);      // 입력: [0.9, 0.1]
        X(0,0)=0.9; X(0,1)=0.1;

        Matrix Y(1, 1);      // 정답(Target): [0.9]
        Y(0,0)=0.9;

        // 2. 가중치 초기화 (랜덤 대신 고정값 사용)
        // ------------------------------------
        Matrix W1(2, 3);     // Input -> Hidden
        W1(0,0)=0.5; W1(0,1)=-0.1; W1(0,2)=0.3;
        W1(1,0)=0.1; W1(1,1)= 0.7; W1(1,2)=0.2;

        Matrix B1(1, 3);
        B1(0,0)=0.0; B1(0,1)=0.0; B1(0,2)=0.0;

        Matrix W2(3, 1);     // Hidden -> Output
        W2(0,0)=0.6; 
        W2(1,0)=-0.2; 
        W2(2,0)=0.4;

        Matrix B2(1, 1);
        B2(0,0)=0.0;

        // 학습률 (Learning Rate): 한 번에 얼마나 수정할지
        double learningRate = 0.05;

        // 3. 학습 루프 (Epochs)
        // ------------------------------------
        for (int epoch = 0; epoch < 10000; ++epoch) {
            
            // === [Step 1] 순전파 (Forward) ===
            // 예측값 구하기: 입력 -> 은닉 -> 출력
            Matrix Z1 = (X * W1) + B1;
            Matrix A1 = Activation::relu(Z1); // 은닉층 출력

            Matrix Z2 = (A1 * W2) + B2;
            Matrix A2 = Activation::sigmoid(Z2); // 최종 예측값

            // === [Step 2] 오차 계산 (Error) ===
            // Error = 정답 - 예측값
            Matrix Error = Y - A2;

            // 1000번마다 진행상황 출력
            if (epoch % 1000 == 0) {
                std::cout << "Epoch " << epoch << " | Prediction: " << A2(0,0) 
                          << " | Error: " << Error(0,0) << std::endl;
            }

            // === [Step 3] 역전파 (Backpropagation) ===
            // 미분(Derivative)을 사용해 누구 때문에 틀렸는지 계산

            // 3-1. 출력층 기울기 (Output Gradient)
            // 공식: 오차 * Sigmoid미분(A2)
            // hadamard: 원소끼리 곱하기
            Matrix d2 = Error.hadamard(Activation::sigmoidDerivative(A2));

            // 3-2. 은닉층 오차 (Hidden Error)
            // 출력층의 책임을 거꾸로 배분 (Transpose 사용!)
            Matrix E1 = d2 * W2.transpose();

            // 3-3. 은닉층 기울기 (Hidden Gradient)
            // 공식: 은닉오차 * ReLU미분(Z1)
            Matrix d1 = E1.hadamard(Activation::reluDerivative(Z1));

            // === [Step 4] 가중치 업데이트 (Update) ===
            // W_new = W_old + (Input_T * Gradient * LR)
            
            // Output Layer 수정
            W2 = W2 + (A1.transpose() * d2) * learningRate;
            B2 = B2 + d2 * learningRate; // 편향은 입력이 1이라고 가정

            // Hidden Layer 수정
            W1 = W1 + (X.transpose() * d1) * learningRate;
            B1 = B1 + d1 * learningRate;
        }

        // 4. 최종 결과 확인
        // ------------------------------------
        std::cout << "------------------------------------" << std::endl;
        std::cout << "Training Complete!" << std::endl;
        
        Matrix FinalZ1 = (X * W1) + B1;
        Matrix FinalA1 = Activation::relu(FinalZ1);
        Matrix FinalZ2 = (FinalA1 * W2) + B2;
        Matrix FinalOutput = Activation::sigmoid(FinalZ2);

        std::cout << "Target: " << Y(0,0) << std::endl;
        std::cout << "Final Prediction: " << FinalOutput << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}