# 📘 [Day 2] 활성화 함수와 C++ 설계 이슈 정리

**작성일:** 2026-01-18
**주제:** 비선형성(ReLU/Sigmoid) 구현 및 C++ 문법 심화 (friend, linking error)

---

## 1. 딥러닝 이론: 활성화 함수 (Activation Function)

### 1.1 필요성
* 단순 행렬 곱($Y = WX$)은 직선(선형)만 표현 가능함.
* 신경망이 곡선과 복잡한 패턴을 익히려면 **비선형성(Non-linearity)**을 주는 함수가 필수적임.

### 1.2 주요 함수 비교

| 이름 | 수식 | 특징 | 용도 |
| :--- | :--- | :--- | :--- |
| **Sigmoid** | $\frac{1}{1 + e^{-x}}$ | 값을 **0~1**로 압축 | 이진 분류, 확률 (과거 방식) |
| **ReLU** | $\max(0, x)$ | 음수는 **0**, 양수는 **그대로** | **최신 표준**, 연산 빠름, 학습 잘됨 |

---

## 2. C++ 구현 및 설계 전략

### 2.1 Static Method 사용
* 활성화 함수는 상태(변수) 저장 없이 계산만 수행함.
* 객체 생성 비용을 아끼기 위해 `static`으로 선언.
    * 사용: `Activation::relu(input)`

### 2.2 접근 제어자(Access Control) 변경 이슈
* **`rows`, `cols` (Private → Public)**
    * 딥러닝 특성상 행렬 크기(Shape) 확인이 매우 빈번함.
    * 실무적 편의성과 성능을 위해 Public으로 공개 (PyTorch 방식 차용).
* **`data` (Private 유지)**
    * `vector`를 2차원처럼 다루는 추상화가 깨지지 않도록 보호.
    * 데이터 무결성(실수로 삭제 방지)을 위해 접근 제한.

---

## 3. 트러블 슈팅 (Troubleshooting)

### 3.1 `friend` 키워드 (VS Java)
* **문제:** `std::cout << matrix` 구현 시, 연산자 함수가 외부 함수라 `private data`에 접근 불가.
* **해결:** `Matrix` 클래스 내에 `friend` 선언을 하여 해당 외부 함수에 접근 권한 부여.
* **Java와 차이:** Java `toString()`은 내부 메소드라 권한이 필요 없지만, C++ `operator<<`는 문법상 외부 함수여야 함.

### 3.2 링킹 에러 (Undefined Reference)
* **증상:** 빌드 시 `undefined reference to Activation::...` 에러 발생.
* **원인:** `CMake`가 새로 생성된 `.cpp` 파일을 실시간으로 인지하지 못함 (`GLOB` 방식의 단점).
* **해결:** `CMakeLists.txt` 파일을 열어서 **저장(Save)** 하여 캐시 갱신.

---

## 4. Git 관리 (Best Practice)

### 4.1 커밋 전략
* **기능(Feat)**과 **테스트(Test)**를 분리하여 커밋하는 것이 깔끔함.

### 4.2 커밋 메시지 컨벤션
* `feat`: 새로운 기능 (예: 활성화 함수 구현)
* `test`: 테스트 코드 (예: 시뮬레이션 코드)
* `fix`: 버그 수정
* `docs`: 문서 수정
* `refactor`: 기능 변경 없는 코드 정리