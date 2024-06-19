# basic-TCP-IP-2024
TCP/IP 소켓 프로그래밍

## 1일차 (2024-06-11)
- cmd에서 ipconfig를 치면 Windows IP 구성 창이 뜸

- 전송방식 : TCP / UDP

- 소 -> 소켓(socket)
- 말 -> 바인더(bind)
- 리 -> 리슨(listen)
- 아 -> 엑셉트(accept)

- Part1
    - 네트워크 프로그래밍
        - 소켓이라는 것을 기반으로 프로그래밍을 하기 때문에 소켓 프로그래밍이라고도 함.
        - 네트워크로 연결된 둘 이상의 컴퓨터 사이에서의 데이터 송수신 프로그램의 작성을 의미
    - 소켓
        - 네트워크(인터넷)의 연결 도구
        - 운영체제에 의해 제공이 되는 소프트웨어적인 장치
        - 소켓은 프로그래머에게 데이터 송수신에 대한 물리적, 소프트웨어적 세세한 내용을 신경x

    - 연결요청을 허용하는 소켓의 생성과정
        1. 소켓의 생성 - socket 함수호출
        2. IP와 PORT번호의 할당 - bind 함수호출
        3. 연결요청 가능상태로 변경 - listen 함수호출
        4. 연결요청에 대한 수락 - accept함수호출

    - 리눅스 기반에서의 실행방법
        - 컴파일 및 실행방법
            - gcc hello_server.c -o hserver
            : hello_server.c 파일을 컴파일해서 hserver라는 이름의 실행파일을 만드는 문장
            - ./hserver
            : 현재 디렉터리에 있는 hserver라는 이름의 파일을 실행시키라는 의미

    - O_CREAT : 필요하면 파일을 생성
    - O_TRUNC : 기존 데이터 전부 삭제
    - O_APPEND : 기존 데이터 보존하고, 뒤에 이어서 저장
    - O_RDONLY : 읽기 전용으로 파일 오픈
    - O_WRONLY : 쓰기 전용으로 파일 오픈
    - O_RDWR : 읽기, 쓰기 겸용으로 파일 오픈 

- Part2
    - 프로토콜이란?
        - 개념적으로 약속의 의미
        - 컴퓨터 상호간의 데이터 송수신에 필요한 통신규약
        - 소켓을 생성할 때 기본적인 프로토콜을 지정
    
    - int socket(int domain, int type, int protocol);
        - domain : 소켓이 사용할 프로토콜 체계 정보 전달
        - type : 소켓의 데이터 전송방식에 대한 정보 전달
        - protocol : 두 컴퓨터간 통신에 사용되는 프로토콜 정보 전달

    - 프로토콜 체계
        - 프로토콜도 그 종류에 따라서 부류가 나뉘는데, 그 부류를 가리켜 프로토콜 체계라고 함
        - PF_INET은 IPv4 인터넷 프로토콜 체계를 의미
        - PF_INET6 IPv6 인터넷 프로토콜 체계를 의미

    - 소켓의 타입
        - 데이터 전송방식을 의미
        - 소켓이 생성될 때 소켓의 타입도 결정

    - 프로토콜 체계 PF_INET의 대표적인 소켓 타입 둘
        - 연결 지향형 소켓 타입 (TCP)
            - 중간에 데이터 소멸되지 않는다.
            - 전송 순서대로 데이터가 수신
            - 데이터의 경계가 존재하지 x
            - 소켓 대 소켓의 연결을 반드시 1대1의 구조
        - 비 연결 지향형 소켓 타입 (UDP)
            - 전송순서 상관없이 빠른 속도의 전송을 지향
            - 데이터 손실 및 파손의 우려
            - 데이터의 경계가 존재
            - 한번에 전송할 수 있는 데이터의 크기가 제한

## 2일차 (2024-06-12)
- Part3
    - 인터넷 주소란 
        - 인터넷상에서 컴퓨터를 구분하는 목적으로 사용되느 주소.
        - 4바이트 주소체계인 IPv4와 16바이트 주소체계인 IPv6가 존재
        - 소켓을 생성할 떄 기본적인 프로토콜을 지정
        - 네트워크 주소와 호스트 주소로 나뉜다. 네트워크 주소를 이용해서 네트워크를 찾고, 호스트 주소를 이용해서 호스트를 구분
    
    - PORT 번호
        - IP는 컴퓨터를 구분하는 용도로 사용, PORT번호는 소켓을 구분하는 용도로 사용
        - 하나의 프로그램 내에서는 둘 이상의 소켓이 존재할 수 있으므로, 둘 이상의 PORT가 하나의 프로그램에 의해 할당
        - PORT번호는 16비트로 표현, 따라서 그 값은 0~65535이하

    - IP주소와 PORT번호는 구조체 sockaddr_in의 변수에 담아서 표현

    - 구조체 sockaddr_in의 멤버에 대한 분석
        - 멤버 sin_family
            - 주소체계 정보 저장
        - 멤버 sin_port
            - 16비트 PORT번호 저장
            - 네트워크 바이트 순서로 저장
        - 멤버 sin_addr
            - 32비트IP주소정보 저장
            - 네트워크 바이트 순서로 저장
            - 멤버 sin_addr의 구조체 자료형 in_addr 사실상 32비트 정수자료형
        - 멤버 sin_zero
            - 특별한 의미를 지니지 않는 멤버
            - 반드시 0으로 채워야함
        - AF_INET : IPv4 인터넷 프로토콜에 적용
        - AF_INET6 : IPv6인터넷 프로토콜에 적용

    - 바이트 순서와 네트워크 바이트 순서
        - 빅 엔디안
            - 상위 바이트의 값을 작은 번지수에 저장
        - 리틀 엔디안
            - 상위 바이트의 값을 큰 번지수에 저장

    - 바이트의 변환함수
        - htons에서 h는 호스트(host) 바이트 순서를 의미
        - htons에서 n은 네트워크(network) 바이트  순서를 의미 
        - htons에서 s는 자료형 short를 의미
        - htonl에서 l은 자료형 long을 의미

    - INADDR_ANY
        - 현재 실행중인 컴퓨터의 IP를 소켓에 부여할 때 사용되는 것 

- Part4
    - TCP/IP 프로토콜 스택이란?
        - 인터넷 기반의 데이터 송수신을 목적으로 설계된 스택
        - 큰 문제를 작게 나눠서 계층화한 결과
        - 데이터 송수신의 과정을 네 개의 영역으로 계층화 한 결과
        - 각 스택 별 영역을 전문화하고 표준화 함
        - 7계층으로 세분화가 되며, 4계층으로도 표현함

    - TCP/UDP 계층
        - 실제 데이터의 송수신과 관련 있는 계층
        - 그래서 전송 계층이라고도 함
        - TCP는 데이터의 전송을 보장하는 프로토콜, UDP는 보장하지 않는 프로토콜
        - TCP는 신뢰성을 보장하기 때문에 UDP에 비해 복잡한 프로토콜이다.

    - TCP 서버의 기본적인 함수 호출 순서
        - socket() 소켓생성
        - bind() 소켓 주소할당
        - listen() 연결요청 대기상태
        - accept() 연결허용
        - read()/write() 데이터 송수신
        - close() 연결종료

- Part5
    - TCP 소켓에 존재하는 입출력 버퍼
        - 입출력 버퍼는 TCP 소켓 각각에 대해 별도로 존재
        - 입출력 버퍼는 소켓생성시 자동으로 생성
        - 소켓을 닫아도 출력버퍼에 남아있는 데이터는 계속해서 전송이 이루어짐
        - 소켓을 닫으면 입력버퍼에 남아있는 데이터는 소멸
    
    - TCP 내부동작 원리
        - 상대 소켓과의 연결
        - 상대 소켓과의 데이터 송수신
        - 상대 소켓과의 연결종료

## 3일차(2024-06-13)

- PART6
    - UDP 소켓의 특성과 동작 원리
        - UDP 소켓은 SEQ,ACK와 같은 메시지 전달을 하지 않음
        - 연결의 설정과 해제의 과정도 존재하지 x
        - 데이터의 분실 및 손실의 위험
        - 확인의 과정이 존재하지 않기 때문에 데이터의 전송이 빠름
        - 안전성보다 성능이 중요시 될 때에는 UDP 사용

    - UDP의 데이터 송수신
        - TCP는 1대 1의 연결을 필요로 하지만, UDP는 연결의 개념이 존재하지x
        - 서버 소켓과 클라이언트 소켓의 구분이 없음
        - 연결의 개념이 존재하지 않음 -> 하나의 소켓으로 둘 이상의 영역과 데이터 송수신이 가능

    - UDP 기반의 에코서버와 클라이언트
        - UDP 에코 서버 코드에서는 수신한 데이터의 전송지를 참조하여 데이터를 에코
        - UDP는 데이터의 경계가 존재하기 때문에 한번의 recvfrom 함수후출을 통해서 하나의 메시지를 완전히 읽음
        - sendito 함수호출 시 IP와 PORT 번호가 자동으로 할당

- PART7
    - close 및 closesocket함수의 기능
        - 소켓의 완전 소멸을 의미
        - 소켓이 소멸되므로 더 이상의 입출력은 불가능
        - 상대방의 상태에 상관 없이 일방적인 종료의 형태를 띰
        - 상대 호스트의 데이터 송수신이 아직 완료되지 않은 상황이라면, 문제가 발생
        - 이러한 문제의 대안으로 Half-close 기법이 존재

    - Half-close
        - 종료를 원한다는 것은, 더이상 전송할 데이터가 존재하지 않는 상황
        - 출력 스트림은 종료를 시켜도 됨
        - 상대방도 종료를 원하는지 확인되지 않은 상황이므로, 출력 스트림은 종료시키지 않을 필요가 있다.
        - 일반적으로 Half-close라 하면, 입력 스트림만 종료하는 것을 의미
        - '우아한 종료'라고도 함

    - 우아한 종료를 위한 Shut-down 함수
        - SHUT_RD : 입력 스트림 종료
        - SHUT_WR : 출력 스트림 종료
        - SHUT_RDWR : 입출력 스트림 종료

        - close 함수가 호출되면 상대 호스트(소켓)으로 EFO가 전달. 이는 모든 데이터의 전송이 끝났다는 신호의 의미를 갖는다. 이것이 종료 이외의 close 함수를 호출하는 목적
        출력 스트림만 종료를 해도 EOF가 전달이 됨 -> close 함수의 호출을 대체하고도, 상대 호스트의 종료를 기다릴 수 있음.

- PART8
    - 도메인 이름
        - IP를 대신하는 서버의 주소 ex) www.naver.com
        - 실제 접속에 사용되는 주소는 아니다. 이 정보는 IP로 변환이 되어야 접속이 가능

    - DNS 서버
        - 도메인 이름을 IP로 변환해주는 서버
        - DNS는 일종의 분산 데이터베이스 시스템

    - 도메인 이름을 이용해서 IP주소 얻어오기
        - getrhostbyname 함수의 인자로 도메인 이름 정보를 전달하면 해당 도메인의 서버 장보가 hostent 구조체 변수에 채워지고, 그 변수의 주소 값이 반환
        - 상대적으로 변동이 덜한 도메인 이름을 이용해서 서버가 실행될 때마다 IP를 얻어오게 구현한다면, 서버의 코드를 재 컴파일 할 필요가 없다.

    - 구조체 hostent에 채워지는 정보의 형태
        - h_name : 공식 도메인 이름
        - h_aliases : 별칭의 도메인 이름
        - h_addrtype: 변환된 IP의 정보가 IPv4인 경우, AF_INET이 반환
        - h_length : 반환된 IP 정보의 크기, IPv6인 경우, 16이 저장
        - h_addr_list : IP의 주소정보, 둘 이상의 경우 모두 반환

- PART9
    - 옵션정보의 참조에 사용되는 함수
    - intgetsockopt(int sock, int level, int optname, void *optval, socklen_t *optlen);
        - sock : 옵션확인을 위한 소켓의 파일 디스크립터 전달
        - level : 확인할 옵션의 프로토콜 레벨 전달
        - optname : 확인할 옵션의 이름 전달
        - optval : 확인결과의 저장을 위한 버퍼의 주소 값 전달

    - 소켓의 입출력 버퍼 크기 확인
        - 입력버퍼의 크기를 참조 및 변경할 때에는 SO_SNDBUF
        -출력버퍼의 크기를 참조 및 변경할 때에는 SO_RCVBUF를 사용

- PART10
    - 멀티프로세스 기반 서버 : 다수의 프로세스를 생성하는 방식으로 서비스 제공
    - 멀티플렝식 기반 서버 : 입출력 대상을 묶어서 관리하는 방식으로 서비스 제공
    - 멀티쓰레딩 기반 서버 : 클라이언트의 수만큼 쓰레드를 생성하는 방식으로 서비스 제공

    - 프로세스와 프로세스의 ID
    - 프로세스란?
        - 간단하게는 실행 중인 프로그램을 뜻함
        - 실행중인 프로그램에 관련된 메모리, 리소스 등을 총칭하는 의미
        - 멀티프로세스 운영체제는 둘 이상의 프로세스를 동시에 생성 가능
    - 프로세스 ID
        - 운영체제는 생성되는 모든 프로세스에 ID를 할당한다.

    - fork 함수
        - fork 함수가 호출되면, 호출한 프로세스가 복사되어 fork 함수 호출 이후를 각각의
        프로세스가 독립적으로 실행하게 된다.

    - 좀비 프로세스란?
        - 실행이 완료되었음에도 불구하고, 소멸되지 않은 프로세스
        - 프로세스도 main 함수가 반환되면 소멸되어야 한다.
        - 소멸되지 않았다는 것은 프로세스가 사용한 리소스가 메모리 공간에 여전히 존재한다는 의미
    - 좀비 프로세스의 생성 원인
        - 자식 프로세스가 종료되면서 반환하는 상태 값이 부모 프로세스에게 전달되지 않으면 해당 프로세스는 소멸되지 않고 좀비가 된다.

## 4일차(2024-06-14)
- PART10
    - wait 함수
        - 자식 프로세스가 종료되지 않은 상황에서는 반환하지 않고 블로킹 상태에 놓인다는 특징
    - waitpid 함수
        - pid_t waitpid(pid_t pid, int * statloc, int options);
            - pid : 종료를 확인하고자 하는 자식 프로세스의 ID전달
            - statloc : wait함수의 매개변수 staloc과 동일한 의미로 사용
    - wait 함수는 블로킹 상태에 빠질 수 있는 반면, wairpid함수는 블로킹 상태에 놓이지 않게끔 할 수있다는 장점!

    - 시그널이란?
        - 특정 상황이 되었을 때 운영체제가 프로세스에게 해당 상황이 발생했음을 알리는 일종의 메시지
        - SIGALRM : alarm 함수호출을 통해서 등록된 시간이 된 상황
        - SIGINT : CTRL+C가 입력된 상황
        - SIGCHLD : 자식 프로세스가 종료된 상황

    - 시그널 등록이란?
        - 특정 상황에서 운영체제로부터 프로세스가 시그널을 받기 위해서는 해당 상황에 대해서 등록의 과정을 거쳐야 함




- PART11




- PART12




## 5일차(2024-06-17)
- PART13
    - ssize_t sent(int sockfd, const coid * buf, size_t nbytes, int flags);
        - sockfd : 데이터 전송 대상과의 연결을 의미하는 소켓을 파일 디스크립터 전달
        - buf : 전송할 데이터를 저장하고 있는 버퍼의 주소 값 전달
        - nbytes : 전송할 바이트 수 전달
        - flags : 데이터 전송 시 적용할 다양한 옵션 정보 전달

    - ssize_t recv(int sockfd, const coid * buf, size_t nbytes, int flags);
        - sockfd : 데이터 수신 대상과의 연결을 의미하는 소켓을 파일 디스크립터 전달
        - buf : 수신된 데이터를 저장하고 있는 버퍼의 주소 값 전달
        - nbytes : 수신할 수 있는 최대 바이트 수 전달
        - flags : 데이터 수신 시 적용할 다양한 옵션 정보 전달

    - send & recv 함수의 옵션
        - MSG_OOB : 긴급 데이터의 전송을 위한 옵션 - send, recv
        - MSG_PEEK : 입력버퍼에 수신된 데이터의 존재유무 확인을 위한 옵션 - recv
        - MSG_DONTROUTE : 데이터 전송과정에서 라우팅 테이블을 참조하지 않을 것을 요구하는 옵션 - send
        - MSG_DONTWAIT : 넌-블로킹 IO의 요구에 사용되는 옵션 - send, recv
        - MSG_WQITALL : 요청한 바이트 수에 해당하는 데이터 전부 수신될 때까지 호출된 함수가 반환되는 것을 막기 위한 옵션 - recv

    - writev 함수 사용
        - 둘 이상의 영역에 나뉘어 저장된 데이터를 묶어서 한번의 함수호출을 통해서 보냄
        - 함수의 호출횟수를 줄일 수 있다.
        - 잘게 나뉜 데이터들을 추력버퍼에 한번에 밀어 넣기 때문에 하나의 패킷으로 구성되어서 전송될 확률이 높아지고 이는 전송속도의 향상으로도 이어질 수 있음.

    -readv 함수 사용
        - 단 한번의 함수호출을 통해서 입력되는 데이터를 둘 이상의 영역에 나눠서 저장 가능

- PART15
    - 표준 입출력 함수
        - 장점
            - 표준 입출력 함수는 이식성이 좋음
            - 표준 입출력 함수는 버퍼링을 통한 성능의 향상에 도움
        - 단점
            - 양방향 통신이 쉽지 않다
            - 상황에 따라서 fflush 함수의 호출이 빈번히 등장
            - 파일 디스크립터를 FILE 구조체의 포인터로 변환



- miniproject
    - webpage 배열을 전송하는 웹서버를 구현
    - 클라이언트 인터넷 브라우저로 서버 접속 -> HTTP request 형식의 메세지로 서버에 전달 -> GET/POST 요청 방식에 따른 서버 동작

    <img src="https://raw.githubusercontent.com/HeoYongmin/basic-TCP-IP-2024/main/day07/miniproject/webserver.png" width="730">





        