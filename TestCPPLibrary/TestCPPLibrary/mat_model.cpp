#include "stdafx.h"
const double eps = 1e-7; //The error of touching the wheel of the earth

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
	FILE *log = fopen("cpp_log.txt", "w");
	bool contact;
	if (touch_test(current_model, current_surface) == 1) contact = true;
	else contact = false;
	//fprintf(log, "current_model\n   Corrd.x = %.4lf\n   Corrd.y = %.4lf\n   Velocity.x = %.4lf\n   Velocity.y = %.4lf\n\n", current_model->Coord.x, current_model->Coord.y, current_model->Velocity.x, current_model->Velocity.y);
	//fprintf(log, "current_surface\n   angle = %.4lf\n   lim_x = %.4lf\n   mu = %.4lf\n   start_x = %.4lf\n   start_y = %.4lf\n\n", current_surface->angle, current_surface->limitation_x, current_surface->mu, current_surface->start_x, current_surface->start_y);
	//fprintf(log, "koef_of_model\n   gravity = %.4lf\n   mass = %.4lf\n   radius = %.4lf\n\n", koef_model->gravity, koef_model->mass, koef_model->radius);
	//fprintf(log, "force = %.4lf\n",*force);
	//fprintf(log, "_____________\n");
	while (*step_time > 0) {
		//int touch = touch_test(current_model, current_surface);

		double current_surface_height = tan(current_surface->angle) * current_model->Coord.x + current_surface->start_y - current_surface->start_x * tan(current_surface->angle);
		fprintf(log, "текущая высота поверхности = %.4lf\n", current_surface_height);
		if (current_surface_height > current_model->Coord.y) {//We fell through the textures
			current_model->Coord.y = current_surface_height;//Climbed to the surface
			hit(current_model, koef_model, current_surface);//Calculated impact against the surface, so as not to fall through again
			contact = true;
			fprintf(log, "%.4lf - провалились под текстуры на %.10lf\n",*step_time, fabs(current_surface_height - current_model->Coord.y));
		}

		if (fabs(current_surface_height - current_model->Coord.y) < eps) {//We are on the surface
			if (contact == false) {
				contact = true;
				hit(current_model, koef_model, current_surface);//Calculated impact against the surface, so as not to fall through again
			}
			next_step_N(current_model, koef_model, current_surface, force, step_time);//Step calculation
			fprintf(log, "%.4lf - есть касание\n", *step_time);
		} else {//we are flying
			if (contact == true) contact = false;
			fprintf(log, "%.4lf - мы летим\n", *step_time);
			fprintf(log, "текущая высота = %.4lf\n", fabs(current_surface_height - current_model->Coord.y));
			double step = find_earth(current_model, koef_model, current_surface);
			fprintf(log, "коснёмся земли через %.4lf\n", step);
			if (step > 0) { //Touching a surface within a known surface
				if (step > *step_time) step = *step_time;
				next_step_no_N(current_model, koef_model, &step);
				*step_time -= step;
				fprintf(log, "%.4lf - каснёмся земли в известной поверхности\n", *step_time);
				fprintf(log, "current_model\n   Corrd.x = %.4lf\n   Corrd.y = %.4lf\n   Velocity.x = %.4lf\n   Velocity.y = %.4lf\n\n", current_model->Coord.x, current_model->Coord.y, current_model->Velocity.x, current_model->Velocity.y);
			} else {
				if (step == -1) { //Touching a surface outside a known surface
					fprintf(log, "%.4lf - касание земли за поверхностью\n", *step_time);
					fprintf(log, "current_model\n   Corrd.x = %.4lf\n   Corrd.y = %.4lf\n   Velocity.x = %.4lf\n   Velocity.y = %.4lf\n\n", current_model->Coord.x, current_model->Coord.y, current_model->Velocity.x, current_model->Velocity.y);
					step = time_no_N(current_model, current_surface);
					fprintf(log, "летим, расчёт на шаг %.4lf\n", step);
					if (step > *step_time) step = *step_time;
					next_step_no_N(current_model, koef_model, &step);
					*step_time -= step;
				} else {
					current_model->Coord.y += 50; //This should never happen //We failed
					fprintf(log, "%.4lf - критическая ошибка. повторное проваливание\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n", *step_time);
				}
			}
		}

		if (current_model->Coord.x > current_surface->start_x + current_surface->limitation_x * 9. / 10. && current_model->Velocity.x > 0) {//Forward movement, there was not enough known map
			if (touch_test(current_model, current_surface) == 1 && contact == true)
				hit(current_model, koef_model, current_surface);//Calculated impact against the surface, so as not to fall in the future
			fprintf(log, "дайте поверхность справа");
			fprintf(log, "%.4lf current_model\n   Corrd.x = %.4lf\n   Corrd.y = %.4lf\n   Velocity.x = %.4lf\n   Velocity.y = %.4lf\n\n", *step_time, current_model->Coord.x, current_model->Coord.y, current_model->Velocity.x, current_model->Velocity.y);
			return 1;
		}
		if (current_model->Coord.x < current_surface->start_x + current_surface->limitation_x / 10. && current_model->Velocity.x < 0) {//Backward movement, there was not enough known map
			if (touch_test(current_model, current_surface) == 1 && contact == true)
				hit(current_model, koef_model, current_surface);//Calculated impact against the surface, so as not to fall in the future
			fprintf(log, "дайте поверхность слева");
			fprintf(log, "%.4lf current_model\n   Corrd.x = %.4lf\n   Corrd.y = %.4lf\n   Velocity.x = %.4lf\n   Velocity.y = %.4lf\n\n", *step_time, current_model->Coord.x, current_model->Coord.y, current_model->Velocity.x, current_model->Velocity.y);
			return -1;
		}
		fprintf(log, "%.4lf current_model\n   Corrd.x = %.4lf\n   Corrd.y = %.4lf\n   Velocity.x = %.4lf\n   Velocity.y = %.4lf\n\n\n\n", *step_time, current_model->Coord.x, current_model->Coord.y, current_model->Velocity.x, current_model->Velocity.y);
	}
	if (touch_test(current_model, current_surface) == 1 && contact == true)
		hit(current_model, koef_model, current_surface);//Calculated impact against the surface, so as not to fall in the future
	fclose(log);
	return 0;
}