#include "stdafx.h"
const double eps = 1e-3; //The error of touching the wheel of the earth

extern "C" __declspec(dllexport) koef_of_model  initialization_koef_model() {
	koef_of_model koef_model;

	FILE *in;
	if ((in = fopen("model_koef.txt", "r")) == NULL) {
		printf("Cannot open file model_koef.txt");
		return koef_model;
	}

	fscanf(in, "%lf", &koef_model.mass);
	fscanf(in, "%lf", &koef_model.gravity);
	fscanf(in, "%lf", &koef_model.radius);
	
	fclose(in);
	return koef_model;
}

extern "C" __declspec(dllexport) data_model solve_step(state_model current_model, koef_of_model koef_model, surface current_surface, double current_time, double step_time) {
	
	
	//соударение!!!!!!!!!!!!!!
	
	// проверка касания.
	if (fabs(current_surface.distance_to_earth - koef_model.radius) < eps) { //There is a touch
		if (current_surface.distance_to_earth < koef_model.radius) // Fell a little under the texture
			current_model.Coord.y += fabs(current_surface.distance_to_earth - koef_model.radius);  //Surface elevation
													// вызов next_step_N
	}else{
		if (current_surface.distance_to_earth < koef_model.radius) // This should not be!!!
			current_model.Coord.y += fabs(current_surface.distance_to_earth - koef_model.radius);//Surface elevation
													// вызов next_step_no_N
	}
	data_model a;
	return a;
}