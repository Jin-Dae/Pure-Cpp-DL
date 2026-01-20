#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <random>
#include <cmath>
#include <stdexcept>

class Matrix {
private:

    std::vector<double> data; // 1차원으로 펴서 저장

public:    
    int rows;
    int cols;
    // 생성자
    Matrix(int rows, int cols);

    // 값 접근 (Indexing)
    double& operator()(int r, int c);
    double operator()(int r, int c) const;

    // Getter
    int getRows() const { return rows; }
    int getCols() const { return cols; }

    // 유틸리티
    void print() const;
    void initRandom();

    // 연산 (Operator Overloading)
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const; // 행렬 곱
    Matrix operator*(double scalar) const;       // 스칼라 곱
    Matrix hadamard(const Matrix& other) const;       // 원소별 곱셈 (Element-wise)
    
    // 전치 (Transpose)
    Matrix transpose() const;

    // 출력
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
};

#endif