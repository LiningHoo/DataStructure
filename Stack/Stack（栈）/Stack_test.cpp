// Stack（栈）.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Stack.hpp"

using namespace std;

void visit(void *p) {
	int *temp = (int*)(p);
	cout << *temp << " ";
}

int main()
{
	//Stack<int> stk;
	/*try {
		int t = stk.GetTop();
	}
	catch (const char *err) {
		cout << err << endl;
	}*/
	/*for (int i = 1; i <= 16; i++) stk.Push(i);
	stk.Pop();*/
	//stk.ClearStack();
	//cout << stk << endl;
	//stk.StackTraverse(visit);
	StackApplication stkapp;
	stkapp.LineEdit();
	//stkapp.conversion(1348);
	//cout << stkapp.IsBracketsMatch("((([])))") << endl;
	/*double rst = stkapp.EvaluateExpression("3*(7-2)*6/(1-5+3*6-(1+3))#");
	cout << rst << endl;
	stkapp.hanoi(8, 'x', 'y', 'z');*/
	return 0;
}

