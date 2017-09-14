#include"stdafx.h"
#include"function_header.h"

const double eps = 1e-4; // подобрать
const double max_num_step = 10;


int next_step_N(FILE* log, struct state_model* current_model, const struct koef_of_model* koef_model, const struct surface* current_surface, const double force, double* time_left, double all_time_step) {
	fprintf(log, "! ! !runge_N\n");
	func_solve_acc_wheel(current_model, &current_model->wheel.Velocity, koef_model, force, current_surface, true); // Acceleration calculation
	double step_time = *time_left;
	while (true) {
		Vector2 Approximate_movement = current_model->wheel.Velocity * step_time + current_model->wheel.Acceleration * step_time*step_time / 2; //Approximate movement calculation in lineral model
		if (current_model->wheel.Coord.x + Approximate_movement.x > current_surface->start_x + current_surface->limitation_x ||   //Step reduction
			current_model->wheel.Coord.x + Approximate_movement.x < current_surface->start_x) {
			step_time /= 2;
			continue;
		}

		runge_K K;
		runge_koef(current_model, current_model->wheel.Velocity, current_model->wheel.Acceleration, koef_model, current_surface, force, step_time, &K); // Calculation koef for step h


		if (current_model->wheel.Coord.x + solve_koef_coord(&K).x > current_surface->start_x + current_surface->limitation_x ||//Step reduction
			current_model->wheel.Coord.x + solve_koef_coord(&K).x < current_surface->start_x ||
			solve_koef_coord(&K).x > current_surface->limitation_x / 2) {
			step_time /= 2;
			continue;
		}

		Vector2 Rcoord, Rvelocity; // solve fo step h
		Rcoord = current_model->wheel.Coord + solve_koef_coord(&K);
		Rvelocity = current_model->wheel.Velocity + solve_koef_velocity(&K);

		double half_step_time = step_time / 2;
		runge_K Km;
		runge_koef(current_model, current_model->wheel.Velocity, current_model->wheel.Acceleration, koef_model, current_surface, force, half_step_time, &Km); //Calculation koef for step h/2
		//solve for step h/2
		Vector2 Rcoord_half, Rvelocity_half;
		Rcoord_half = current_model->wheel.Coord + solve_koef_coord(&Km);
		Rvelocity_half = current_model->wheel.Velocity + solve_koef_velocity(&Km);

		Vector2 solve_Acceleration = func_solve_acc_wheel(current_model, &Rvelocity_half, koef_model, force, current_surface, false); //Calculation of a new acceleration
		runge_koef(current_model, Rvelocity_half, solve_Acceleration, koef_model, current_surface, force, half_step_time, &Km); //Calculation koef for time+h and step h/2

		//solve for time+h and step h/2
		Rcoord_half += solve_koef_coord(&Km);
		Rvelocity_half += solve_koef_velocity(&Km);

		double err = err_runge(Rcoord, Rcoord_half); //find max err
		double tmp_err = err_runge(Rvelocity, Rvelocity_half);
		if (err < tmp_err) err = tmp_err;

		if (err < eps || step_time < all_time_step / max_num_step) { //Error checking
			current_model->wheel.Coord = (16 * Rcoord_half - Rcoord) / 15; //solve model
			current_model->wheel.Velocity = (16 * Rvelocity_half - Rvelocity) / 15;
			*time_left -= step_time;
			int tmp = solve_body(log, current_model, koef_model, step_time);
			current_model->body.Coord.x = current_model->wheel.Coord.x;
			current_model->body.Velocity.x = current_model->wheel.Velocity.x;
			break;
		}
		else {
			step_time /= 2;//all new calculation with new h
		}
	}
	return 0;
}


int solve_body(FILE* log, state_model *current_model, const koef_of_model *koef_model, double all_time_step) {
	//At the moment, we integrate simply with a given step
	double step_time = all_time_step;
	double time_left = all_time_step;
	fprintf(log, "all_time_step = %.10lf\n", all_time_step);
	while (time_left > 0) {
		func_solve_acc_body(current_model->body.Coord, current_model->wheel.Coord, koef_model, current_model); //solv acceleration
		fprintf(log, "acc_body - %lf   %lf\n", current_model->body.Acceleration.x, current_model->body.Acceleration.y);
		runge_K K;
		runge_koef_body(current_model->body.Velocity, current_model->body.Acceleration, koef_model, step_time, &K);//solve koef

		Vector2 Rcoord, Rvelocity; // solve fo step h
		Rcoord = current_model->body.Coord + solve_koef_coord(&K);
		Rvelocity = current_model->body.Velocity + solve_koef_velocity(&K);

		double half_step_time = step_time / 2;
		runge_K Km;
		runge_koef_body(current_model->body.Velocity, current_model->body.Acceleration, koef_model, half_step_time, &K);//Calculation koef for step 
		//solve for step h/2
		Vector2 Rcoord_half, Rvelocity_half;
		Rcoord_half = current_model->body.Coord + solve_koef_coord(&Km);
		Rvelocity_half = current_model->body.Velocity + solve_koef_velocity(&Km);

		//next half step
		Vector2 half_acceleration = func_solve_acc_body(Rcoord_half, current_model->wheel.Coord, koef_model, NULL); //solv acceleration
		runge_koef_body(Rvelocity_half, half_acceleration, koef_model, half_step_time, &K);//Calculation koef for step
		Rcoord_half += solve_koef_coord(&Km);
		Rvelocity_half += solve_koef_velocity(&Km);

		double err = err_runge_y(Rcoord, Rcoord_half); //find max err
		double tmp_err = err_runge_y(Rvelocity, Rvelocity_half);
		if (err < tmp_err) err = tmp_err;
		fprintf(log, "step_time = %.10lf,   err = %.10lf\n", step_time, err);

		if (err < eps || step_time < all_time_step / (max_num_step / 5.)) { //Error checking
			current_model->body.Coord = (16 * Rcoord_half - Rcoord) / 15; //solve model
			current_model->body.Velocity = (16 * Rvelocity_half - Rvelocity) / 15;
			time_left -= step_time;
			break;
		}
		else step_time /= 2;//all new calculation with new h
	}
	return 0;
}