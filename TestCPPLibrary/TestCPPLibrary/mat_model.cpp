#include "stdafx.h"
const double eps = 1e-5; //The error of touching the wheel of the earth

extern "C" __declspec(dllexport) koef_of_model  initialization_koef_model() {
	koef_of_model koef_model;

	FILE *in;
	if ((in = fopen("model_koef.ini", "r")) == NULL) {
		printf("Cannot open file model_koef.txt");
		return koef_model;
	}

	fscanf_s(in, "%lf", &koef_model.mass);
	fscanf_s(in, "%lf", &koef_model.gravity);
	fscanf_s(in, "%lf", &koef_model.radius);
	
	fclose(in);
	return koef_model;
}

extern "C" __declspec(dllexport) int solve_step(state_model* current_model, koef_of_model* koef_model, surface* current_surface, double* step_time, double* force) {

	while (step_time > 0) {

		//int touch = touch_test(current_model, current_surface);

		double current_surface_height = tan_deg(current_surface->angle) * current_model->Coord.x + current_surface->srart_y - current_surface->start_x * tan_deg(current_surface->angle);

		if (current_surface_height > current_model->Coord.y) {//We fell through the textures
			current_model->Coord.y = current_surface_height;//Climbed to the surface
			hit(current_model, koef_model, current_surface);//Calculated impact against the surface, so as not to fall through again
		}

		if (fabs(current_surface_height - current_model->Coord.y) < eps) {//We are on the surface
			hit(current_model, koef_model, current_surface);//Calculated impact against the surface, so as not to fall through again
			next_step_N(current_model, koef_model, current_surface, force, step_time);//Step calculation
		
		} else {//we are flying
			double step = find_earth(current_model, koef_model, current_surface);
			if (step > 0) { //Touching a surface within a known surface
				if (step > *step_time) step = *step_time;
				next_step_no_N(current_model, koef_model, &step);
				*step_time -= step;
			} else {
				if (step == -1) { //Touching a surface outside a known surface
					step = time_no_N(current_model, current_surface);
					if (step > *step_time) step = *step_time;
					next_step_no_N(current_model, koef_model, &step);
					*step_time -= step;
				} else
					current_model->Coord.y += 50; //This should never happen //We failed
			}
		}

		if (current_model->Coord.x > current_surface->start_x + current_surface->limitation_x * 9. / 10. && current_model->Velocity.x > 0) {//Forward movement, there was not enough known map
			return 1;
		}
		if (current_model->Coord.x < current_surface->start_x + current_surface->limitation_x / 10. && current_model->Velocity.x < 0) {//Backward movement, there was not enough known map
			return -1;
		}
	}
	return 0;
}