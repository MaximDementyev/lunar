#include"stdafx.h"

const double eps = 1e-5; // подобрать
const double max_num_step = 100;


void next_step_N(struct state_model* current_model, struct koef_of_model* koef_model, struct surface* current_surface, double* force, double* time_left) {
	Vector2 solve_Acceleration = func_solve_acceleration(&current_model->Velocity, koef_model, force, current_surface); // Acceleration calculation
	double step_time = *time_left;
	while (true) {
		Vector2 Approximate_movement = current_model->Velocity * step_time + solve_Acceleration * step_time*step_time / 2; //Approximate movement calculation in lineral model
		if (current_model->Coord.x + Approximate_movement.x > current_surface->start_x + current_surface->limitation_x ||   //Step reduction
			current_model->Coord.x + Approximate_movement.x < current_surface->start_x) {
			step_time /= 2;
			continue;
		}

		runge_K K;
		runge_koef(&current_model->Velocity, &solve_Acceleration, koef_model, current_surface, force, &step_time, &K); // Calculation koef for step h
		
		if (current_model->Coord.x + solve_koef_coord(&K).x > current_surface->start_x + current_surface->limitation_x ||//Step reduction
			current_model->Coord.x + solve_koef_coord(&K).x < current_surface->start_x ||
			solve_koef_coord(&K).x > current_surface->limitation_x / 2) {
			step_time /= 2;
			continue;
		}

		Vector2 z1, z2; // solve fo step h
		z1 = current_model->Coord + solve_koef_coord(&K);
		z2 = current_model->Velocity + solve_koef_velocity(&K);


		double half_step_time = step_time / 2;
		runge_K Km;
		runge_koef(&current_model->Velocity, &solve_Acceleration, koef_model, current_surface, force, &half_step_time, &Km); //Calculation koef for step h/2
		//solve for step h/2
		Vector2 y1, y2;
		y1 = current_model->Coord + solve_koef_coord(&Km);
		y2 = current_model->Velocity + solve_koef_velocity(&Km);

		
		solve_Acceleration = func_solve_acceleration(&y2, koef_model, force, current_surface); //Calculation of a new acceleration
		runge_koef(&y2, &solve_Acceleration, koef_model, current_surface, force, &half_step_time, &Km); //Calculation koef for time+h and step h/2

		//solve for time+h and step h/2
		y1 = y1 + solve_koef_coord(&Km);
		y2 = y2 + solve_koef_velocity(&Km);

		double err = norm(z1 - y1); //find max err
		double tmp_err = norm(z2 - y2);
		if (err < tmp_err)
			err = tmp_err;

		if (err < eps || step_time < *time_left / max_num_step) { //Error checking
			current_model->Coord = (16 * y1 - z1) / 15; //solve model
			current_model->Velocity = (16 * y2 - z2) / 15;
			*time_left -= step_time;
			break;
		}
		else {
			step_time /= 2;//all new calculation with new h
		}
	}
}

void next_step_no_N(struct state_model* current_model, struct koef_of_model* koef_model, double *time) {
	//Analytical solution

	current_model->Coord.x += current_model->Velocity.x * (*time); // x = x0 + vt
	current_model->Coord.y += current_model->Velocity.y * (*time) - koef_model->gravity * (*time) * (*time) / 2; // y = y0 + vt - (gt^2)/2
	
	// v_x = v_x
	current_model->Velocity.y -= koef_model->gravity * (*time); // v_y = v0_y - gt

	
}