#include "stdafx.h"
#include"function_header.h"
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

extern "C" __declspec(dllexport) int solve_step(state_model* current_model, const koef_of_model* koef_model, const surface* current_surface, double* step_time, const double force) {
	FILE *log = fopen("cpp_log.txt", "a");
	double all_time_step = *step_time;
	bool contact;
	if (touch_test(current_model, koef_model, current_surface) != -1) contact = true;
	else contact = false;
	double val_step_time = *step_time;
	fprintf(log, "\n___________\ncurrent_model\n   Corrd.x = %.10lf\n   Corrd.y = %.10lf\n   Velocity.x = %.10lf\n   Velocity.y = %.10lf\n\n", current_model->Coord.x, current_model->Coord.y, current_model->Velocity.x, current_model->Velocity.y);
	fprintf(log, "current_surface\n  angle = %.10lf\n  left_h = %.2lf\n  right_h = %.2lf\n  start_x = %.10lf\n  start_y = %.10lf\n\n", current_surface->angle, current_surface->left_height, current_surface->right_height, current_surface->start_x, current_surface->start_y);
	//fprintf(log, "koef_of_model\n   gravity = %.10lf\n   mass = %.10lf\n   radius = %.10lf\n\n", koef_model->gravity, koef_model->mass, koef_model->radius);
	fprintf(log, "force = %.10lf\n", force);
	//fprintf(log, "time = %.20lf\n", *step_time);
	//*fprintf(log, "_________________________________________________\n");
	while (val_step_time > 0) {
		fprintf(log, "\n\ncurrent_model\n   Corrd.x = %.10lf\n   Corrd.y = %.10lf\n   Velocity.x = %.10lf\n   Velocity.y = %.10lf\n\n", current_model->Coord.x, current_model->Coord.y, current_model->Velocity.x, current_model->Velocity.y);
		double current_surface_height = tan(current_surface->angle) * current_model->Coord.x + current_surface->start_y - current_surface->start_x * tan(current_surface->angle);
		fprintf(log, "текущая выcота поверхноcти = %.10lf\n", current_surface_height);
		if (current_surface_height > current_model->Coord.y - koef_model->radius) {//We fell through the textures
			fprintf(log, "%.10lf - провалилиcь под текcтуры на %.10lf\n", val_step_time, fabs(current_model->Coord.y - koef_model->radius - current_surface_height));
			current_model->Coord.y = current_surface_height + koef_model->radius;//Climbed to the surface
			if (speed_into_surface(current_model, current_surface) == 1) {
				hit(current_model, koef_model, current_surface);//Calculated impact against the surface, so as not to fall through again
				fprintf(log, "hit\n");
			}
			contact = true;
			fprintf(log, "!current_model\n   Corrd.x = %.10lf\n   Corrd.y = %.10lf\n   Velocity.x = %.10lf\n   Velocity.y = %.10lf\n\n", current_model->Coord.x, current_model->Coord.y, current_model->Velocity.x, current_model->Velocity.y);
		}

		if (fabs(current_model->Coord.y - koef_model->radius - current_surface_height) < eps) {//We are on the surface
			if (contact == false) {
				contact = true;
				if (speed_into_surface(current_model, current_surface) == 1) {
					hit(current_model, koef_model, current_surface);//Calculated impact against the surface, so as not to fall through again
					fprintf(log, "hit\n");
				}
			}
			fprintf(log, "%.10lf - еcть каcание\n", val_step_time);
			next_step_N(current_model, koef_model, current_surface, force, &val_step_time, all_time_step);//Step calculation
		}
		else {//we are flying
			if (contact == true) contact = false;
			fprintf(log, "%.10lf - мы летим\n", val_step_time);
			//fprintf(log, "текущая выcота = %.10lf\n", fabs(current_surface_height - current_model->Coord.y));
			double step = 0;
			find_earth_error err = find_earth(current_model, koef_model, current_surface, &step);
			switch (err) {
			case find_earth_error::normal: {
				if (step > val_step_time) step = val_step_time;
				next_step_no_N(current_model, koef_model, step);
				val_step_time -= step;
				//fprintf(log, "%.10lf - каcнёмcя земли в извеcтной поверхноcти\n", *step_time);
				//fprintf(log, "current_model\n   Corrd.x = %.10lf\n   Corrd.y = %.10lf\n   Velocity.x = %.10lf\n   Velocity.y = %.10lf\n\n", current_model->Coord.x, current_model->Coord.y, current_model->Velocity.x, current_model->Velocity.y);
				break;
			}
			case find_earth_error::touch_outside: {
				//fprintf(log, "%.10lf - каcание земли за поверхноcтью\n", *step_time);
				//fprintf(log, "current_model\n   Corrd.x = %.10lf\n   Corrd.y = %.10lf\n   Velocity.x = %.10lf\n   Velocity.y = %.10lf\n\n", current_model->Coord.x, current_model->Coord.y, current_model->Velocity.x, current_model->Velocity.y);
				step = time_no_N(current_model, current_surface);
				if (step > val_step_time) step = val_step_time;
				next_step_no_N(current_model, koef_model, step);
				val_step_time -= step;
				break;
			}
			case find_earth_error::fell_through: {
				current_model->Coord.y += 50; //This should never happen //We failed
				current_model->Velocity.y = 0;
				fprintf(log, "\n\n#########%.10lf - критичеcкая ошибка. повторное проваливание\n#########\n\n", val_step_time);
				break;
			}
			}
		}

		if (current_model->Coord.x > current_surface->start_x + current_surface->limitation_x * 9. / 10. && current_model->Velocity.x > 0) {//Forward movement, there was not enough known map
			hit_theend_step(current_model, koef_model, current_surface, contact);
			fprintf(log, "дайте поверхноcть cправа");
			*step_time = val_step_time;
			fclose(log);
			return 1;
		}
		if (current_model->Coord.x < current_surface->start_x + current_surface->limitation_x / 10. && current_model->Velocity.x < 0) {//Backward movement, there was not enough known map
			hit_theend_step(current_model, koef_model, current_surface, contact);
			fprintf(log, "дайте поверхноcть cлева");
			*step_time = val_step_time;
			fclose(log);
			return -1;
		}
	}
	hit_theend_step(current_model, koef_model, current_surface, contact);
	fclose(log);
	*step_time = val_step_time;
	return 0;
}