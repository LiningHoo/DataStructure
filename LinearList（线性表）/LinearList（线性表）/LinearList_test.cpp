// LinearList（线性表）.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"
#include "cstdio"
#include "LinearList.hpp"


Status visit(int temp) {
	std::cout << temp << " ";
	return OK;
}

int main()
{
    
	LinkList<int> lkt;
	for (int i = 0; i < 32; i++) {
		LNode<int> *temp = new LNode<int>;
		temp->data = i + 1;
		lkt.InsFirst(temp);
	}
	lkt.ListTraverse(visit);
	return 0;
}

