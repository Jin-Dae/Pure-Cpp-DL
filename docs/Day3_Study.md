# 📘 [Day 3] 순전파(Forward Propagation)와 신경망 조립

**작성일:** 2026-01-21
**주제:** 신경망의 데이터 흐름(Inference) 구현 및 예외 처리

---

## 1. 딥러닝 이론: 순전파 (Forward Propagation)

### 1.1 핵심 개념
순전파는 입력 데이터가 신경망의 층(Layer)을 통과하며 최종 예측값(Output)으로 변환되는 과정이다. 수도꼭지(Input)에서 나온 물이 여러 파이프(Weights)와 밸브(Bias)를 거쳐 나오는 것에 비유할 수 있다.

### 1.2 핵심 공식
신경망의 한 층은 다음과 같은 수식으로 작동한다.

$$A = \sigma(X \cdot W + B)$$

* **$X$ (Input):** 입력 데이터
* **$W$ (Weight):** 가중치 (입력의 중요도 조절)
* **$B$ (Bias):** 편향 (뉴런의 활성화 기준점 조절)
* **$\sigma$ (Activation):** 활성화 함수 (ReLU, Sigmoid 등)

---

## 2. 구현 구조 (Architecture)

이번 실습에서는 **2층 신경망(2-Layer Neural Network)**을 시뮬레이션했다.

### 2.1 네트워크 형태
* **입력층 (Input Layer):** 뉴런 **2개** (예: 공부시간, 수면시간)
* **은닉층 (Hidden Layer):** 뉴런 **3개** (특징 추출)
    * 활성화 함수: **ReLU** (음수 제거)
* **출력층 (Output Layer):** 뉴런 **1개** (최종 예측)
    * 활성화 함수: **Sigmoid** (0~1 확률값 변환)

### 2.2 행렬 차원(Dimension) 분석
* Input ($1 \times 2$) $\times$ $W1$ ($2 \times 3$) + $B1$ ($1 \times 3$) $\rightarrow$ Hidden ($1 \times 3$)
* Hidden ($1 \times 3$) $\times$ $W2$ ($3 \times 1$) + $B2$ ($1 \times 1$) $\rightarrow$ Output ($1 \times 1$)

---

## 3. C++ 프로그래밍 기법

### 3.1 예외 처리 (Exception Handling)
행렬 연산 시 크기(Shape)가 맞지 않으면 프로그램이 강제 종료될 수 있다. 이를 방지하기 위해 `try-catch` 구문을 적용했다.

* **Throw (Matrix.cpp):** 문제 발생 시 에러 객체를 던짐.
* **Catch (main.cpp):** 에러를 받아서 안전하게 메시지를 출력하고 종료.

```cpp
try {
    Matrix Z = X * W; 
} catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}