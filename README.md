# 학교 수업 관련 실습 코드 정리 (SangMyung University Coursework)

이 레포지토리는 상명대학교에서 수강한 과목들의 실습 코드를 정리한 공간입니다. 각 폴더는 특정 과목의 실습 내용을 담고 있습니다.

## 과목 및 실습 내용

### lisherU/AdvancedOOP
- **고급 객체지향 프로그래밍 (Advanced Object-Oriented Programming)**
    - `MP01code`: 문서 변환 및 처리 (Document conversion and processing).
    - `MP03code`: 소수 생성 관련 멀티스레딩 및 Observer 패턴 활용 (Multithreading and Observer pattern for prime number generation).
    - `MP04code`: Decorator 패턴을 이용한 다양한 디스플레이 요소 구현 (Various display elements using Decorator pattern).
    - `MP05code`: Factory 패턴을 이용한 도형 생성 (Shape creation using Factory pattern).
    - `MP07Code`: 사용자 정의 DynamicArray 구현 및 Adapter 패턴 (Custom DynamicArray implementation and Adapter pattern).
    - `MP08Code`: Command 패턴을 활용한 계산기 구현 (Calculator implementation using Command pattern).
    - `MP09code`: State 패턴을 활용한 계산기 구현 (Calculator implementation using State pattern).
    - `MP10code`: 다양한 정렬 알고리즘 (Bubble sort) 및 전략 패턴 활용 (Various sorting algorithms like Bubble Sort and Strategy pattern).

### lisherU/DB_12week
- **데이터베이스 (Database)**
    - `MySQLPython.py`: Python을 이용한 MySQL 데이터베이스 연동 (Python and MySQL database integration).
    - `create_table.txt`, `movie_data.txt`, `script.txt`: 테이블 생성, 데이터 삽입 등 SQL 스크립트 (SQL scripts for table creation, data insertion, etc.).

### lisherU/Octave
- **Octave/MATLAB을 활용한 프로그래밍 (Programming using Octave/MATLAB)**
    - `MultimediaSignalProcessing/`: Haar 웨이블릿, Otsu 이진화 방법 등 이미지 처리 및 신호 처리 기법 실습 (Image processing and signal processing techniques like Haar Wavelet, Otsu's method).
    - `PatternRecognition/`: 다층 퍼셉트론(MLP) 학습, 시그모이드, 선형/로지스틱 회귀 등 패턴 인식 알고리즘 구현 (Pattern recognition algorithms including MLP training, sigmoid, linear/logistic regression).

### lisherU/PatternRecognition
- **패턴 인식 (Pattern Recognition)**
    - `ImageCut/`: 이미지 자르기, 이름 변경, 데이터셋 구축 등 이미지 전처리 작업 (Image preprocessing tasks like cutting, renaming, and dataset construction, including a handwritten alphabet dataset).
    - `Mnist/`: MNIST 데이터셋을 활용한 CNN (Convolutional Neural Networks) 및 Softmax 회귀 모델 구현 (Implementation of CNN and Softmax regression models using the MNIST dataset).

### lisherU/RealTimeKernel
- **실시간 커널 (Real-Time Kernel)**
    - `lab01`: 태스크 생성 및 우선순위 기반 스케줄링 (Task creation and priority-based scheduling).
    - `lab02`: 상호 배제, 임계 구역 문제, 세마포어를 이용한 동기화 (Mutual exclusion, critical section problems, and synchronization using semaphores).
    - `lab03`: 실시간 시계 또는 타이머 구현 (Implementation of a real-time clock or timer).
    - `lab04`: 식사하는 철학자 문제, 생산자-소비자 문제 등 고전적 동기화 문제 해결 (Solving classical synchronization problems like Dining Philosophers and Producer-Consumer).

### lisherU/UnixSystem
- **유닉스 시스템 프로그래밍 (Unix System Programming)**
    - `lab03`: `cat`, `cp`, `append`, `create` 등 기본적인 파일 처리 유틸리티 구현 (Implementation of basic file utilities like `cat`, `cp`, `append`, `create`).
    - `lab04`: `mv`, `rm`, 파일 크기/타입 확인, 권한 변경 등 파일 시스템 관련 유틸리티 구현 (File system utilities like `mv`, `rm`, checking file size/type, changing permissions).
    - `lab05`: `date`, `uname`, `whoami` 등 시스템 정보 관련 유틸리티 구현 (System information utilities like `date`, `uname`, `whoami`).
    - `lab06`: 프로세스 종료 처리 (`atexit`), 환경 변수, `setjmp`/`longjmp` 활용 (Process termination handling (`atexit`), environment variables, `setjmp`/`longjmp`).
    - `lab07`: `fork`, `exec`, `wait`, PID를 이용한 프로세스 생성 및 관리 (Process creation and management using `fork`, `exec`, `wait`, PID).
    - `lab08`: `alarm`, `signal`을 이용한 시그널 처리 (Signal handling using `alarm` and `signal`).
    - `lab09`: 스레드 생성, 동기화 (Thread creation and synchronization).
    - `lab10`: FIFO, 파이프, 메모리 맵, 메시지 큐를 이용한 프로세스 간 통신 (Inter-process communication using FIFO, pipes, memory maps, message queues).

### lisherU/uCOS-II-2.92.10-tm4c1294xl
- **임베디드 시스템 / 실시간 운영체제 (Embedded Systems / RTOS)**
    - Micriµm의 uC/OS-II RTOS 커널 (V2.92.10) 관련 자료 및 코드.
    - ARM-Cortex-M4 (TM4C1294XL 타겟보드) 포팅 버전.
    - `Config/`: OS 설정 파일.
    - `Ports/`: ARM-Cortex-M4 포팅 관련 코드.
    - `Source/`: uC/OS-II 전체 소스 코드.
    - 교육 및 연구 목적으로 사용 가능 (상업적 사용 시 라이선스 필요).
