// Array（数组）.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Array.hpp"

int main()
{
	/*Array<int> arr(8, 1, 128);
	for (int i = 0; i < 128; ++i) {
		arr.Assign(i+1, i);
	}
	for (int i = 0; i < 128; ++i) {
		cout << arr.Value("ready", i) << " ";
	}*/
	RLSMatrix<int> M(3, 4, 4), N(3, 4, 4);
	M.CreateSMatrix();
	N.CreateSMatrix();
	//N = M.CopySMatrix();
	//tsmx.PrintSMatrix();
	cout << endl <<  M << endl;
	cout << N << endl;
	//cout << endl << M.MultSMatrix(N) << endl; 
	cout << endl << M.AddSMatrix(N) << endl;
	cout << M.SubtMatrix(N) << endl;
	return 0;
}

