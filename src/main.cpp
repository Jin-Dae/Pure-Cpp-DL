// src/main.cpp
#include <iostream>
#include <chrono> // 시간을 재기 위한 헤더 (스톱워치)
#include "Matrix.h"

int main() {
    try {
        // 행렬 크기 설정 (1000 x 1000)
        // 너무 금방 끝나면 2000으로 늘려보세요.
        const int SIZE = 1000; 

        std::cout << "=== Performance Test Start ===" << std::endl;
        std::cout << "Generating " << SIZE << "x" << SIZE << " matrices..." << std::endl;

        // 1. 거대 행렬 생성 및 초기화
        Matrix A(SIZE, SIZE);
        A.initRandom();

        Matrix B(SIZE, SIZE);
        B.initRandom();

        std::cout << "Multiplication started... (Please wait)" << std::endl;

        // 2. 타이머 시작 (스톱워치 누름!)
        auto start = std::chrono::high_resolution_clock::now();

        // 3. 행렬 곱셈 실행 (여기가 테스트 구간)
        Matrix C = A * B;

        // 4. 타이머 종료 (스톱워치 멈춤!)
        auto end = std::chrono::high_resolution_clock::now();

        // 5. 걸린 시간 계산 (밀리초 단위)
        std::chrono::duration<double, std::milli> elapsed = end - start;

        std::cout << "=== Test Finished ===" << std::endl;
        std::cout << "Time taken: " << elapsed.count() << " ms (" 
                  << elapsed.count() / 1000.0 << " seconds)" << std::endl;
        
        // (참고) C의 값을 하나라도 출력해야 컴파일러가 "아 이 변수 쓰는구나" 하고
        // 계산 코드를 생략(최적화 삭제)하지 않음
        std::cout << "Verification Check C(0,0): " << C(0, 0) << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}