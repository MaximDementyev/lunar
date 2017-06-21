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

extern "C" __declspec(dllexport) struct Vector2 TestStruct()
{
	Vector2 res;
	res.x = 5;
	res.y = 7;
	FILE *out = fopen("cpp_out.txt", "w");
	fprintf(out, "Vector2.x = %lf\nVector2.y = %lf", res.x, res.y);
	fclose(out);
	return res;
}

extern "C" __declspec(dllexport) void TestUpdateStruct(struct Vector2* res)
{
	FILE *out = fopen("cpp_out.txt", "a");
	fprintf(out, "\n________\nUpdate in\nVector2.x = %lf\nVector2.y = %lf", res->x, res->y);
	res->x = 1;
	res->y = 10;
	fprintf(out, "\n________\nUpdate out\nVector2.x = %lf\nVector2.y = %lf", res->x, res->y);
	fclose(out);
}