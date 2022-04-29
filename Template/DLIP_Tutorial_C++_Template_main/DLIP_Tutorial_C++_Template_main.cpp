#include <iostream>


namespace proj_B {

	template<typename T>
	class myNum {
	public:
		T val1;
		T val2;
		T val3;

		myNum() {}
		myNum(T in1, T in2, T in3) {
			val1 = in1;
			val2 = in2;
			val3 = in3;
		}

		T sum() {
			return val1 + val2 + val3;
		}
		
		void print() {
			printf("val1 = %d\n", val1);
			std::cout << "val2 = " << val2 << std::endl;
			std::cout << "val3 = " << val3 << std::endl;
			std::cout << "sum  = " << sum() << std::endl;
			std::cout << "dsize= " << sizeof(sum()) << std::endl;
		}
	};
}

using namespace std;

void main() {

	/// option 1
	//myNum mynum;
	//mynum.val1 = 10;
	//mynum.val2 = 20;

	/// option 2
	//proj_A::myNum mynum(11, 1100);
	proj_B::myNum<int> mynum(11, 1100, 11);

	mynum.print();

	//cout << mynum, sum(10000) << endl;

	system("pause");
}










/*
#include <iostream>

namespace proj_B {

	template<typename T>
	
	class myNum {
	public:
		T val1;   // ���뼺 �ְ� ����ϱ� ���ؼ��� int�� ������ų ���� �ƴ϶�, ���δ� typename���� �ٲ������ �ȴ�!
		T val2;
		T val3;

		myNum() {}
		myNum(T in1, T in2, T in3) {
			val1 = in1;
			val2 = in2;
			val3 = in3;
		}

		T sum() {
			return val1 + val2 + val3;
		}

		void prT() {
			prT("val1 = %d\n", val1);
			std::cout << "val2 = " << val2 << std::endl;
			std::cout << "val3 = " << val3 << std::endl;
			std::cout << "sum  = " << sum() << std::endl;
			std::cout << "dsize= " << sizeof(sum()) << std::endl;
		}
	};
}


void main() {

	/// option 1
	//myNum mynum;
	//mynum.val1 = 10;
	//mynum.val2 = 20;

	/// option 2
	//proj_A::myNum mynum(11, 1100);

	proj_B::myNum<int> mynum(11, 1100);

	mynum.prT();

	system("pause");
}
*/