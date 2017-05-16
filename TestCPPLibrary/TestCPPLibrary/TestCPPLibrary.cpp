// TestCPPLibrary.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"


extern "C" __declspec(dllexport) float TestMultiply(float a, float b)
{
	return a * b;
}

extern "C" __declspec(dllexport) float TestDivide(float a, float b)
{
	if (b == 0) {
		return 0;
		//throw invalid_argument("b cannot be zero!");
	}
		return a / b;
}

extern "C" __declspec(dllexport) float TestSum(float a, float b)
{
	return a + b;
}