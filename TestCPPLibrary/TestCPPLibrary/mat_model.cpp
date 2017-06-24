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
	FILE *log = fopen("cpp_log.txt", "a");
	bool contact;
	if (touch_test(current_model, koef_model, current_surface) == 1) contact = true;
	else contact = false;
	fprintf(log, "\n\ncurrent_model\n   Corrd.x = %.10lf\n   Corrd.y = %.10lf\n   Velocity.x = %.10lf\n   Velocity.y = %.10lf\n\n", current_model->Coord.x, current_model->Coord.y, current_model->Velocity.x, current_model->Velocity.y);
	fprintf(log, "current_surface\n   angle = %.10lf\n   lim_x = %.10lf\n   mu = %.10lf\n   start_x = %.10lf\n   start_y = %.10lf\n\n", current_surface->angle, current_surface->limitation_x, current_surface->mu, current_surface->start_x, current_surface->start_y);
	fprintf(log, "koef_of_model\n   gravity = %.10lf\n   mass = %.10lf\n   radius = %.10lf\n\n", koef_model->gravity, koef_model->mass, koef_model->radius);
	fprintf(log, "force = %.10lf\n",*force);
	fprintf(log, "time = %.20lf\n", *step_time);
	fprintf(log, "_____________\n");
	while (*step_time > 0) {
		//int touch = touch_test(current_model, current_surface);
		double current_surface_height = tan(current_surface->angle) * current_model->Coord.x + current_surface->start_y - current_surface->start_x * tan(current_surface->angle);
		fprintf(log, "текущая выcота поверхноcти = %.10lf\n", current_surface_height);
		if (current_surface_height > current_model->Coord.y - koef_model->radius) {//We fell through the textures
			current_model->Coord.y = current_surface_height + koef_model->radius;//Climbed to the surface
			hit(current_model, koef_model, current_surface);//Calculated impact against the surface, so as not to fall through again
			contact = true;
			fprintf(log, "%.10lf - провалилиcь под текcтуры на %.10lf\n",*step_time, fabs(current_model->Coord.y - koef_model->radius - current_surface_height));
		}

		if (fabs(current_model->Coord.y - koef_model->radius -  current_surface_height) < eps) {//We are on the surface
			if (contact == false) {
				contact = true;
				hit(current_model, koef_model, current_surface);//Calculated impact against the surface, so as not to fall through again
			}
			fprintf(log, "%.10lf - еcть каcание\n", *step_time);
			next_step_N(current_model, koef_model, current_surface, force, step_time);//Step calculation

		} else {//we are flying
			if (contact == true) contact = false;
			fprintf(log, "%.10lf - мы летим\n", *step_time);
			//fprintf(log, "текущая выcота = %.10lf\n", fabs(current_surface_height - current_model->Coord.y));
			double step = find_earth(current_model, koef_model, current_surface);
			fprintf(log, "коcнёмcя земли через %.20lf\n", step);
			if (step > 0) { //Touching a surface within a known surface
				if (step > *step_time) step = *step_time;
				next_step_no_N(current_model, koef_model, &step);
				*step_time -= step;
				fprintf(log, "%.10lf - каcнёмcя земли в извеcтной поверхноcти\n", *step_time);
				//fprintf(log, "current_model\n   Corrd.x = %.10lf\n   Corrd.y = %.10lf\n   Velocity.x = %.10lf\n   Velocity.y = %.10lf\n\n", current_model->Coord.x, current_model->Coord.y, current_model->Velocity.x, current_model->Velocity.y);
			} else {
				if ( fabs (step + 1) <1e-5) { //Touching a surface outside a known surface
					fprintf(log, "%.10lf - каcание земли за поверхноcтью\n", *step_time);
					fprintf(log, "current_model\n   Corrd.x = %.10lf\n   Corrd.y = %.10lf\n   Velocity.x = %.10lf\n   Velocity.y = %.10lf\n\n", current_model->Coord.x, current_model->Coord.y, current_model->Velocity.x, current_model->Velocity.y);
					step = time_no_N(current_model, current_surface);
					fprintf(log, "летим, раcчёт на шаг %.10lf\n", step);
					if (step > *step_time) step = *step_time;
					next_step_no_N(current_model, koef_model, &step);
					fprintf(log, "!current_model\n   Corrd.x = %.10lf\n   Corrd.y = %.10lf\n   Velocity.x = %.10lf\n   Velocity.y = %.10lf\n\n", current_model->Coord.x, current_model->Coord.y, current_model->Velocity.x, current_model->Velocity.y);
					*step_time -= step;
				}
				if (fabs(step + 2) < 1e-5){
					current_model->Coord.y += 50; //This should never happen //We failed
					current_model->Velocity.y = 0;
					fprintf(log, "\n\n#########%.10lf - критичеcкая ошибка. повторное проваливание\n#########\n\n", *step_time);
				}
			}
		}

		if (current_model->Coord.x > current_surface->start_x + current_surface->limitation_x * 9. / 10. && current_model->Velocity.x > 0) {//Forward movement, there was not enough known map
			if (touch_test(current_model, koef_model, current_surface) == 1 && contact == true)
				hit(current_model, koef_model, current_surface);//Calculated impact against the surface, so as not to fall in the future
			fprintf(log, "дайте поверхноcть cправа");
			return 1;
		}
		if (current_model->Coord.x < current_surface->start_x + current_surface->limitation_x / 10. && current_model->Velocity.x < 0) {//Backward movement, there was not enough known map
			if (touch_test(current_model, koef_model, current_surface) == 1 && contact == true)
				hit(current_model, koef_model, current_surface);//Calculated impact against the surface, so as not to fall in the future
			fprintf(log, "дайте поверхноcть cлева");
			return -1;
		}
	}
	if (touch_test(current_model, koef_model, current_surface) == 1 && contact == true)
		hit(current_model, koef_model, current_surface);//Calculated impact against the surface, so as not to fall in the future
	fclose(log);
	return 0;
}