// include/Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"
#include <cmath> // 수학 함수(exp 등)를 쓰기 위해 필요

class Activation {
public:
    // 1. Sigmoid: 1 / (1 + e^-x)
    // 결과를 0과 1 사이로 찌그러뜨립니다.
    static Matrix sigmoid(const Matrix& m);

    // 2. ReLU: max(0, x)
    // 0보다 작은 값은 없애버리고(0), 양수는 그대로 둡니다.
    static Matrix relu(const Matrix& m);
    
    // [Day 4] 미분 함수들 (학습용)
    // Sigmoid 미분 공식: x * (1 - x)  (단, x는 이미 Sigmoid를 거친 출력값)
    static Matrix sigmoidDerivative(const Matrix& m);

    // ReLU 미분 공식: x > 0 이면 1, 아니면 0
    static Matrix reluDerivative(const Matrix& m);
};

#endif