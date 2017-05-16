#include "stdafx.h"

extern "C" __declspec(dllexport) koef_of_model  initialization() {
	koef_of_model koef_model;

	FILE *in;
	if ((in = fopen("model_koef.txt", "r")) == NULL) {
		printf("Cannot open file model_koef.txt");
		return koef_model;
	}

	fscanf(in, "%lf", &koef_model.mass);
	fscanf(in, "%lf", &koef_model.gravity);
	fscanf(in, "%lf", &koef_model.force);
	
	fclose(in);
	return koef_model;
}

