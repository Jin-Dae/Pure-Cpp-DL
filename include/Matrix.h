#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <random>
#include <cmath>
#include <stdexcept>

class Matrix {
private:
    int rows;
    int cols;
    std::vector<double> data; // 1차원으로 펴서 저장

public:
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
    
    // 전치 (Transpose)
    Matrix transpose() const;
};

#endif