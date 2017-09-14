#include"stdafx.h"
#include"function_header.h"
const double eps = 1e-4; // подобрать
const double max_num_step = 10;

void next_step_no_n(FILE* log,  state_model* current_model, const  koef_of_model* koef_model, const  surface* current_surface, double* time_left, double all_time_step) {
	//we flying
	auto step_time = *time_left;
	auto mass_coord = center_mass(current_model, koef_model);
	fly_acc(current_model, koef_model);
	fprintf(log, "b_acc.y = %lf    w_acc.y = %lf\n", current_model->body.Acceleration.y, current_model->wheel.Acceleration.y);
	while (true) {
		auto step_model = *current_model;
		runge_K Kbody, Kwheel;
		
		fly_runge_koef(step_model.wheel.Velocity, step_model.wheel.Acceleration, step_time, &Kwheel);//solve runge koef for wheel
		step_model.wheel.Coord.x += step_model.wheel.Velocity.x * step_time; // x = x0 + vt;
		step_model.wheel.Coord += solve_koef_coord(&Kwheel);//WARNING cheked change coord_x = 0!!!
		if (touch_test(&step_model, koef_model, current_surface, nullptr) == -1) {
			step_time /= 2;
			continue;
		}else{
			if (fabs(step_model.wheel.Coord.x - current_surface->start_x) > current_surface->limitation_x) {
				print_model(log, &step_model);
				step_time /= 2;
				continue;
			}
		}
		//we dont fall, continue solve
		step_model.wheel.Velocity.y += solve_koef_velocity(&Kwheel).y;

		//solve for body
		fly_runge_koef(step_model.body.Velocity, step_model.body.Acceleration, step_time, &Kbody);//solve runge koef for wheel
		step_model.body.Coord.x += step_model.body.Velocity.x * step_time; // x = x0 + vt;
		step_model.body.Coord.y += solve_koef_coord(&Kbody).y;
		step_model.body.Velocity.y += solve_koef_velocity(&Kbody).y;

		//solve half step time
		auto half_step_model = *current_model;
		//solve wheel
		fly_runge_koef(half_step_model.wheel.Velocity, half_step_model.wheel.Acceleration, step_time / 2, &Kwheel);//solve runge koef for wheel
		half_step_model.wheel.Coord.y += solve_koef_coord(&Kwheel).y;
		half_step_model.wheel.Velocity.y += solve_koef_velocity(&Kwheel).y;

		//solve body
		fly_runge_koef(half_step_model.body.Velocity, half_step_model.body.Acceleration, step_time / 2, &Kbody);//solve runge koef for wheel
		half_step_model.body.Coord.y += solve_koef_coord(&Kbody).y;
		half_step_model.body.Velocity.y += solve_koef_velocity(&Kbody).y;

		
		//second half step
		fly_acc(&half_step_model, koef_model);//solve acceleration

		fly_runge_koef(half_step_model.wheel.Velocity, half_step_model.wheel.Acceleration, step_time / 2, &Kwheel);//solve runge koef for wheel
		half_step_model.wheel.Coord.y += solve_koef_coord(&Kwheel).y;
		half_step_model.wheel.Velocity.y += solve_koef_velocity(&Kwheel).y;
		
		//solve body
		fly_runge_koef(half_step_model.body.Velocity, half_step_model.body.Acceleration, step_time / 2, &Kbody);//solve runge koef for wheel
		half_step_model.body.Coord.y += solve_koef_coord(&Kbody).y;
		half_step_model.body.Velocity.y += solve_koef_velocity(&Kbody).y;

		//find max err
		auto err = err_runge_y(step_model.body.Coord, half_step_model.body.Coord); 
		auto tmp_err = err_runge_y(step_model.body.Velocity, half_step_model.body.Velocity);
		if (tmp_err > err) err = tmp_err;
		tmp_err = err_runge_y(step_model.wheel.Coord, half_step_model.wheel.Coord);
		if (tmp_err > err) err = tmp_err;
		tmp_err = err_runge_y(step_model.wheel.Velocity, half_step_model.wheel.Velocity);
		if (tmp_err > err) err = tmp_err;

		if (err < eps || step_time < all_time_step / max_num_step) { //Error checking
			fprintf(log, "err = %lf\n", err);
			current_model->wheel.Coord.y = (16 * half_step_model.wheel.Coord - step_model.wheel.Coord).y / 15; //solve model
			current_model->wheel.Velocity.y = (16 * half_step_model.wheel.Velocity - step_model.wheel.Velocity).y / 15;
			current_model->wheel.Coord.x += step_model.wheel.Velocity.x * step_time; // x = x0 + vt;
			*time_left -= step_time;
			//int tmp = solve_body(log, current_model, koef_model, step_time);
			current_model->body.Coord.y = (16 * half_step_model.body.Coord - step_model.body.Coord).y / 15;
			current_model->body.Velocity.y = (16 * half_step_model.body.Velocity - step_model.body.Velocity).y / 15;
			current_model->body.Coord.x += step_model.body.Velocity.x * step_time; // x = x0 + vt;
			break;
		}
		else {
			step_time /= 2;//all new calculation with new h
		}
	}
}