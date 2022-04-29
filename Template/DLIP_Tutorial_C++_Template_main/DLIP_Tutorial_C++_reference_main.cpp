///*------------------------------------------------------------------------------------------
//@ Deep Learning Image Processing  by Young-Keun Kim - Handong Global University
//
//
// Description     : Exercise:  C++ reference exercise
//------------------------------------------------------------------------------------------*/

#include <iostream>
using namespace std;

class MyNum {
public:
    MyNum() {};  	// Option 1 
    MyNum(int x); 	// Option 2     
    int num;
    double numinv();
};

// Class Constructor Definition 
MyNum::MyNum(int x){
    num = x;
}


// Problem (1)
double adder(double numin1, double numin2) {
    return numin1 + numin2;
}

double adder(double numin1, double numin2, double numin3) {
    return numin1 + numin2 + numin3;
}


// Problem (2)
void add(int numin1, int numin2, int &numOut) {
    numOut = numin1+ numin2;
}


// Problem (3)
double MyNum::numinv() {
    return 1.0 / num;
}


int main()
{
    // Option 1
    MyNum mynum;
    mynum.num = 10;


    // Problem (1)
    cout << adder(12, 10) << endl;


    // Problem (2)
    int addOut = 0;
    add(12, 10, addOut);
    cout << addOut << endl;


    // Problem (3)
    // print its inverse value using  numinv() 
    cout << mynum.numinv() << endl;

    return 0;
}