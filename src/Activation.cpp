// src/Activation.cpp
#include "../include/Activation.h"
#include <algorithm> // std::max를 쓰기 위해 필요

Matrix Activation::sigmoid(const Matrix& m) {
    Matrix result(m.rows, m.cols); // 입력과 똑같은 크기의 빈 행렬 생성

    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.cols; ++j) {
            double x = m(i, j);
            // 공식: 1 / (1 + e^-x)
            // std::exp(-x)는 e^-x를 의미합니다.
            result(i, j) = 1.0 / (1.0 + std::exp(-x));
        }
    }
    return result;
}

Matrix Activation::relu(const Matrix& m) {
    Matrix result(m.rows, m.cols);

    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.cols; ++j) {
            double x = m(i, j);
            // 공식: max(0, x)
            // x가 양수면 x 그대로, 음수면 0
            result(i, j) = std::max(0.0, x);
        }
    }
    return result;
}

Matrix Activation::sigmoidDerivative(const Matrix& m) {
    // 주의: 여기서 입력 m은 이미 sigmoid를 통과한 결과값(A)이라고 가정합니다.
    // 공식: f'(x) = f(x) * (1 - f(x))
    Matrix result(m.rows, m.cols);
    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.cols; ++j) {
            double x = m(i, j);
            result(i, j) = x * (1.0 - x);
        }
    }
    return result;
}

Matrix Activation::reluDerivative(const Matrix& m) {
    // 주의: 여기서 입력 m은 활성화 전의 원본값(Z)이어야 정확합니다.
    // 공식: x > 0 ? 1 : 0
    Matrix result(m.rows, m.cols);
    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.cols; ++j) {
            double x = m(i, j);
            if (x > 0) {
                result(i, j) = 1.0; // 기울기 1 (그대로 통과)
            } else {
                result(i, j) = 0.0; // 기울기 0 (차단)
            }
        }
    }
    return result;
}