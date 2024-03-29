// Queue（队列）.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Queue.hpp"

void visit(void *data) {
	int *p = reinterpret_cast<int*>(data);
	cout << *p << " ";
}

int main()
{
	Queue_Sq<int> q(256);
	for (int i = 0; i < 32; i++) q.EnQueue(i + 1);
	q.ClearQueue();
	for (int i = 0; i < 32; i++) q.EnQueue(i + 1);
	//while (!q.QueueEmpty()) cout << q.DeQueue() << " ";
	q.QueueTraverse(visit);
	return 0;
}

