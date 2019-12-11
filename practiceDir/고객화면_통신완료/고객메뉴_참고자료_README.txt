g++ -o main.out menuClass.cpp people.cpp main.cpp order.cpp

main.out 만드는 법

***********************************

g++ -o client.out client.cpp

client.out 만드는 법

**********************************

MyMsg.h안에 내용만 보면 됨 ( 다른 구현 팀원들은.. )

MsgList구조체는 메뉴하나, 메뉴당 수량 정보 가지고 있다.

MsgCus는 주문 번호 (num ) , MsgList구조체의 배열, MsgList구조체의 배열이 30개인데 그게 다 메뉴이지는 않으므로, 쓸모있는 정보만 추출
편하도록 하는 menuTotal이있다

menuTotal 까지 for문을 돌리면 쓸모있는 메뉴가 다 등장한다.
만약, 0개인 메뉴를 제외하고 싶으면 내가 client.out 처럼 구현한대로 menuTotal 까지 for문돌린 후, if문으로 0개인 정보 제외하고 출력하면 된다.