# cpp_module00

> Namespaces, classes, member functions, stdio streams, initialization lists, static, const, and some other basic stuff

- 과제 설명

  class와 객체, 객체의 member attribute와 member function, 표준 입출력 등 c++의 기초적인 개념들에 대해 공부해보는 과제

- 느낀 점


1. 파일 입출력을 stream을 통해서 구현해보면서 c++ 스타일의 입출력 방식에 대해 알 수 있었다.
2. 객체에서 public과 private의 차이, static이 붙었을 때 member function과 member attribute의 차이 등 객체에 대해서 이해할 수 있었다. 
3. c++를 처음 사용해보았는데, 객체에 대한 개념 자체는 이전에 java와 python에서 사용해보았더라도 본격적으로 사용하는 것은 처음이라 많이 공부가 된 것 같다. 특히 그 동안 걸려있던 norminette라는 제약사항이 없어졌고 테스트 코드를 자율적으로 작성한다는 점에서는 좋았다.

---
# cpp_module01

> Memory allocation, pointers to members, references, switch statement

- 과제 설명

  c++에서의 메모리 할당과 해제, pointer 타입과 reference 타입, 파일 입출력 stream에 관련하여 공부해보는 과제

- 느낀 점

1. new와 delete를 통한 메모리 할당과 해제에 대해 이해할 수 있었고, 지역 변수로 객체 선언하여 인스턴스를 생성할 때 생성자와 소멸자의 호출에 대해서도 이해할 수 있었다.
2. 그 동안 사용했었던 언어에서는 reference 타입이라는 개념이 존재하지 않아서 처음 접했을 때 많이 생소했다. reference의 개념과 어떤 경우에 사용하는게 좋은지, 어떤 제약사항이 있는 지에 대해 배워볼 수 있었다.

---
# cpp_module02

> Ad-hoc polymorphism, operator overloading and Orthodox Canonical class form

- 과제 설명

  Orthodox canonical form을 적용하여 객체를 생성해보며, 다형성과 오버로딩에 대해 공부해보는 과제

- 느낀 점

1. 여러 형태의 생성자를 만들어 두고, 생성자 호출 시 자동적으로 형태와 타입이 맞는 생성자를 호출하는 c++의 다형성에 대해서 이해할 수 있었다.
2. 객체에 대한 여러 operator를 구현하여, 객체에 해당 연산자가 호출되면 구현해둔 메소드가 호출되는 overloading 방식에 대해서 이해할 수 있었다.
3. 문제의 취지와 목적 자체는 좋지만, 과제에서 요구하는 고정 소수점 방식을 따라한 특유의 소수점 표현 방식을 구현하는 것은 너무 별로였다. 문제에 충분한 설명이 나와 있어서 개념이 어렵지만 누구나 구현이 가능하다면 모르겠지만, 문제에 충분한 설명도 없이 기존의 고정 소수점과 부동 소수점의 동작 방식과도 다른 새로운 소수점 표현 방식을 만드는 것을 이해하는 것 자체가 쉽지 않았다.

---
# cpp_module03

> Inheritance

- 과제 설명

  c++에서 상속의 개념에 대해 이해하고 여러 상속 형태를 구현해보면서 객체의 상속에 대해 공부해보는 과제

- 느낀 점

1. 객체의 상속 방법과 생성자 호출 시 부모의 생성자를 호출하는 방법, virtual의 특징과 사용법 등 c++ 상속에 대해 기본적인 사항들에 대해 배워볼 수 있었다.
2. 과제의 형태가 ex00부터 ex03까지 이전에 구현한 부분을 기준으로 쌓아가는 스택형 과제였는데, ex02의 경우에는 구현하는 의미를 찾지 못할 정도로 그저 단순한 복사+붙여넣기 식의 과제였고 ex03 또한 다이아몬드 상속이라는 특이 케이스를 제외하면 위와 동일했다. 이후의 cpp_module 과제에서 상속에 대한 여러 특성들을 활용하는 과제들이 많던데 차라리 그런 특성들을 잘 추려서 이 과제에 녹여내는게 더 좋지 않았을까라는 생각이 들었다.

---
# cpp_module04

> Subtype polymorphism, abstract classes, interfaces

- 과제 설명

  다형성과 추상 클래스에 대해 이해하고, 이를 이용해 타 언어에 있는 interface를 구현해보는 과제

- 느낀 점

1. 순수 가상 함수와 추상 클래스에 대해 이해할 수 있었고, 부모 클래스의 포인터에 자식 클래스의 생성자를 호출하는 업 캐스팅 방식에 대해서 배울 수 있었다.
2. 인터페이스를 구현하고 그에 대한 구현체(콘크리트 클래스)를 갈아끼우면서 코드의 수정과 확장성을 용이하게 하는 방식에 대해서 이해할 수 있었다.

---
# cpp_module05

> Repetition and Exceptions

- 과제 설명

  c++에서 특정 상황에 예외를 발생시켜보는 과제

- 느낀 점

1. 클래스 내부에 특정 상황에 발생시킬 예외들과 그에 따른 출력 메세지들을 만들어두고, 테스트 코드에서 해당 상황들을 유발하여 실제 예외가 발생하는지 확인해보면서 c++에서 예외를 처리하는 방법에 대해서 배울 수 있었다.

---
# cpp_module06

> C++ casts

- 과제 설명

  c++의 여러가지 casting 방법에 대해 배워보는 과제

- 느낀 점

1. 명시적 형변환과 const casting에 대해서는 사용해보지 못했지만, c++에서 사용되는 static casting, dynamic casting, reinterpret casting에 대해 이해하고 실습해볼 수 있었다.

---
# cpp_module07

> C++ templates

- 과제 설명

  c++의 template를 사용해보는 과제

- 느낀 점

1. template의 개념과 template을 사용하여 클래스나 함수를 생성하는 방법에 대해 배울 수 있었다.
2. c++ 과제 중 제일 쉬웠다.

---
# cpp_module08

> Templated containers, iterators, algorithms

- 과제 설명

  c++에서 template를 활용해 데이터를 저장할 수 있는 간단한 클래스를 만들고 실제 container와 비교해보는 과제

- 느낀 점

1. iterator가 동작하는 방식을 간단하게 흉내낸 iter 함수와 단순화된 stack을 만들어보면서 container에 대한 개념을 어느정도 잡을 수 있었던 것 같다.
