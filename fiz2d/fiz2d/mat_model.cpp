#include "stdafx.h"
#include"function_header.h"
const double eps = 1e-5; //The error of touching the wheel of the earth

extern "C" __declspec(dllexport) int solve_step(state_model* current_model, const koef_of_model* koef_model, const surface* current_surface, double* step_time, const double force) {
	
	
	auto *log = fopen("cpp_log.txt", "a");
	const auto all_time_step = *step_time;
	bool contact;
	if (touch_test(current_model, koef_model, current_surface, nullptr) != 1) contact = true;
	else contact = false;
	auto val_step_time = *step_time;


	print_new_step(log);
	print_model(log, current_model);
	print_surface(log, current_surface);
	
	//fprintf(log, "force = %.10lf\n", force);
	//fprintf(log, "time = %.20lf\n", *step_time);

	while (val_step_time > 0) {
		print_model(log, current_model);

		double current_surface_height;
		const auto touch_ground = touch_test(current_model, koef_model, current_surface, &current_surface_height);
		//fprintf(log, "текущая выcота поверхноcти = %.10lf\n", current_surface_height);


		switch (touch_ground) {
			case -1: {//We fell through the textures
				fprintf(log, "%.8lf - провалилиcь на %.10lf\n", val_step_time, fabs(current_model->wheel.Coord.y - koef_model->wheel.radius - current_surface_height));
				current_model->wheel.Coord.y = current_surface_height + koef_model->wheel.radius;//Climbed to the surface
				if (speed_into_surface(current_model, current_surface) == 1) {
					hit(current_model, koef_model, current_surface);//Calculated impact against the surface, so as not to fall through again
				//fprintf(log, "hit\n");
				}
				contact = true;
				//print_model(log, current_model);
			}

			case 0: {//We are on the surface
				if (contact == false) {
					contact = true;
					if (speed_into_surface(current_model, current_surface) == 1) {
						hit(current_model, koef_model, current_surface);//Calculated impact against the surface, so as not to fall through again
						//fprintf(log, "hit\n");
					}
				}
				fprintf(log, "%.5lf - еcть каcание\n", val_step_time);
				auto tmp = next_step_n(log, current_model, koef_model, current_surface, force, &val_step_time, all_time_step);//Step calculation
				break;
			}

			case 1: {//we are flying
				if (contact == true) contact = false;
				fprintf(log, "%.5lf - мы летим\n", val_step_time);
				next_step_no_n(log, current_model, koef_model, current_surface, &val_step_time, all_time_step);
			}
			default:{
				fprintf_s(log, "err switch");
				break;
			}
		}

		if (current_model->wheel.Coord.x > current_surface->start_x + current_surface->limitation_x * 9. / 10. && current_model->wheel.Velocity.x > 0) {//Forward movement, there was not enough known map
			hit_theend_step(current_model, koef_model, current_surface, contact);
			fprintf(log, "дайте поверхноcть cправа");
			*step_time = val_step_time;
			fclose(log);
			return 1;
		}
		if (current_model->wheel.Coord.x < current_surface->start_x + current_surface->limitation_x / 10. && current_model->wheel.Velocity.x < 0) {//Backward movement, there was not enough known map
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