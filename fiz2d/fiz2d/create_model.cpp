#include "stdafx.h"

extern "C" __declspec(dllexport) state_model*  initialization_koef_model(const Vector2 body_coord, const Vector2 *const wheel_coord) {
	auto current_model = new state_model();

	FILE *in;
	if ((in = fopen("model_koef.ini", "r")) == nullptr) {
		printf("Cannot open file model_koef.txt");
		return current_model;
	}
	//initialization koef of body
	fscanf_s(in, "%lf", current_model->body.k_body.mass);
	//initialization state body
	current_model->body.state_body.coord = body_coord;


	//initialization number of wheel
	fscanf_s(in, "%lf", current_model->number_wheel);
	current_model->wheel = new object_wheel[current_model->number_wheel];
	for (auto i = 0; i <current_model->number_wheel; ++i) {
		//initialization koef of wheel
		fscanf_s(in, "%lf", current_model->wheel[i].k_wheel.mass);
		fscanf_s(in, "%lf", current_model->wheel[i].k_wheel.radius);
		fscanf_s(in, "%lf", current_model->wheel[i].k_wheel.position);
		fscanf_s(in, "%lf", current_model->wheel[i].k_wheel.rigidity_suspension);
		//initialization state wheel
		current_model->wheel[i].state_wheel.coord = wheel_coord[i];
	}
	//initialization koef of world
	fscanf_s(in, "%lf", current_model->world.gravity);

	fclose(in);
	return current_model;
}

extern "C" __declspec(dllexport) void destroy_model (state_model *current_model){
	if (current_model->wheel != nullptr) {
		delete[] current_model->wheel;
		current_model->wheel = nullptr;
	}
	if (current_model != nullptr) delete current_model;
}

extern "C" __declspec(dllexport) Vector2 get_coord_body(state_model *current_model) {
	return current_model->body.state_body.coord;
}

extern "C" __declspec(dllexport) Vector2 get_coord_wheel(state_model *current_model, int wheel_number) {
	if (wheel_number < current_model->number_wheel) return current_model->wheel[wheel_number].state_wheel.coord;
	else return Vector2(0,0);
}
