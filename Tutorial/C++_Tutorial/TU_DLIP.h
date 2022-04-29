#ifndef _TU_DLIP_H		// same as "#if !define _TU_DLIP_H" (or #pragma once) 
#define _TU_DLIP_H

#include <iostream>

int sum(int val1, int val2);

namespace proj_A {
	class myNum {
	public:
		int val1;
		int val2;

		myNum(); //option 1
		myNum(int in1, int in2);
		int sum();
		void print();
	};
}


#endif // !_TU_DLIP_H