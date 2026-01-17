// src/Matrix.cpp
#include "Matrix.h"
#include <iostream>
#include <stdexcept> // 예외 처리용
#include <iomanip>   // 출력 줄맞춤용

// 1. 생성자: 0으로 초기화
Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols)
{
    if (rows <= 0 || cols <= 0)
    {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }
    data.resize(rows * cols, 0.0); // 1차원으로 펴서 할당
}

// 2. 값 접근 (Indexing)
double &Matrix::operator()(int r, int c)
{
    if (r < 0 || r >= rows || c < 0 || c >= cols)
    {
        throw std::out_of_range("Matrix index out of bounds");
    }
    return data[r * cols + c];
}

double Matrix::operator()(int r, int c) const
{
    if (r < 0 || r >= rows || c < 0 || c >= cols)
    {
        throw std::out_of_range("Matrix index out of bounds");
    }
    return data[r * cols + c];
}

// 3. 출력 유틸리티
void Matrix::print() const
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            std::cout << std::setw(8) << std::fixed << std::setprecision(4) << (*this)(i, j) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// 4. 랜덤 초기화 (Xavier Initialization 등은 나중에, 일단 표준정규분포 사용)
void Matrix::initRandom()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> d(0.0, 1.0); // 평균 0, 표준편차 1

    for (auto &val : data)
    {
        val = d(gen);
    }
}

// 5. 행렬 덧셈
Matrix Matrix::operator+(const Matrix &other) const
{
    if (rows != other.rows || cols != other.cols)
    {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }
    Matrix result(rows, cols);
    for (size_t i = 0; i < data.size(); ++i)
    {
        result.data[i] = data[i] + other.data[i];
    }
    return result;
}

// 6. 행렬 뺄셈
Matrix Matrix::operator-(const Matrix &other) const
{
    if (rows != other.rows || cols != other.cols)
    {
        throw std::invalid_argument("Matrix dimensions must match for subtraction");
    }
    Matrix result(rows, cols);
    for (size_t i = 0; i < data.size(); ++i)
    {
        result.data[i] = data[i] - other.data[i];
    }
    return result;
}

// 7. 스칼라 곱
Matrix Matrix::operator*(double scalar) const
{
    Matrix result(rows, cols);
    for (size_t i = 0; i < data.size(); ++i)
    {
        result.data[i] = data[i] * scalar;
    }
    return result;
}

// ★★★ 8. 행렬 곱셈 (가장 중요) ★★★
// (M x K) * (K x N) = (M x N)
Matrix Matrix::operator*(const Matrix &other) const
{
    if (cols != other.rows)
    {
        throw std::invalid_argument("Matrix dimensions mismatch for multiplication");
    }

    Matrix result(rows, other.cols);

    // 3중 for문: O(N^3)
    // 추후 최적화 포인트: 반복문 순서를 i -> k -> j 로 바꾸면 캐시 효율이 좋아짐
    // for (int i = 0; i < rows; ++i) {
    //     for (int j = 0; j < other.cols; ++j) {
    //         double sum = 0.0;
    //         for (int k = 0; k < cols; ++k) {
    //             sum += (*this)(i, k) * other(k, j);
    //         }
    //         result(i, j) = sum;
    //     }
    // }
    for (int i = 0; i < rows; i++)
    {
        for (int k = 0; k < cols; ++k)
        {
            // ★ 핵심 최적화: 안쪽 루프(j)가 돌기 전에 값을 미리 '고정'해둠
            double r = (*this)(i, k);

            for (int j = 0; j < other.cols; ++j)
            {
                // r은 이미 CPU 레지스터에 있음 (메모리 갈 필요 X)
                // other(k, j)와 result(i, j)는 옆 칸으로 스르륵 이동 (연속 접근)
                result(i, j) += r * other(k, j);
            }
        }
    }
    return result;
}

// 9. 전치 행렬 (Transpose) - 역전파 때 필수
Matrix Matrix::transpose() const
{
    Matrix result(cols, rows); // 행과 열 뒤집기
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            result(j, i) = (*this)(i, j);
        }
    }
    return result;
}

// 10. 행렬 출력 기능 
std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for (int i = 0; i < m.rows; ++i) {
        os << "[ ";
        for (int j = 0; j < m.cols; ++j) {
            os << m(i, j) << " ";
        }
        os << "]\n";
    }
    return os;
}