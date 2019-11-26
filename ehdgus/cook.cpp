#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {
	
	system("clear");
	cout<< " ----O r d e r e d   L I S T---- "<<endl;
	cout<<endl;

	int consumer = 1;
	int end_food;

	cout<< "                    "<<consumer<<"번   손님"<<endl;
	cout<< "김밥     2개"<<endl;
	cout<< "라면     1개 "<<endl;
	cout<< "------------------------------- "<<endl;
	cout<<endl;
	consumer +=1 ;

	cout<< "                    "<<consumer<<"번   손님"<<endl;
	cout<< "순대국밥  1개"<<endl;
	cout<< "------------------------------- "<<endl;
	cout<<endl;
	consumer +=1 ;

	cout<< "                    "<<consumer<<"번   손님"<<endl;
	cout<< "돈까스    1개"<<endl;
	cout<< "떡볶이    1개"<<endl;
	cout<< "------------------------------- "<<endl;
	cout<<endl;
	consumer +=1 ;


	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"조리가 완료된 손님 번호를 입력하세요. : ";
	cin >> end_food;
	/* 입력된 end_food와 같은 손님 번호를 찾아서 삭제 시킨다. */

	return 0;
}
