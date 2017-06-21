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

extern "C" __declspec(dllexport) struct state_model TestStruct()
{
	state_model res;
	res.Coord.x = 5;
	res.Coord.y = 7;
	res.Velocity.x = -20;
	res.Velocity.y = -37;
	FILE *out = fopen("cpp_out.txt", "w");
	fprintf(out, "Coord.x = %lf\nCoord.y = %lf\nVelocity.x = %lf\nVelocity.y = %lf", res.Coord.x, res.Coord.y, res.Velocity.x, res.Velocity.y);
	fclose(out);
	return res;
}

extern "C" __declspec(dllexport) void TestUpdateStruct(struct state_model* res)
{
	FILE *out = fopen("cpp_out.txt", "a");
	fprintf(out, "\n________\nUpdate in\nCoord.x = %lf\nCoord.y = %lf\nVelocity.x = %lf\nVelocity.y = %lf", res->Coord.x, res->Coord.y, res->Velocity.x, res->Velocity.y);
	res->Coord.x = 105;
	res->Coord.y = 107;
	res->Velocity.x = -420;
	res->Velocity.y = -337;
	fprintf(out, "\n________\nUpdate out\nCoord.x = %lf\nCoord.y = %lf\nVelocity.x = %lf\nVelocity.y = %lf", res->Coord.x, res->Coord.y, res->Velocity.x, res->Velocity.y);
	fclose(out);
}