#include"stdafx.h"
#include"function_header.h"

const double eps = 1e-4; // подобрать
const double max_num_step = 10;


void next_step_N(FILE* log, struct state_model* const current_model, const struct koef_of_model* koef_model, const struct surface* current_surface, const double force, double* time_left, double all_time_step) {
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
		Rcoord_half = Rcoord_half + solve_koef_coord(&Km);
		Rvelocity_half = Rvelocity_half + solve_koef_velocity(&Km);

		double err = norm(Rcoord - Rcoord_half); //find max err
		double tmp_err = norm(Rvelocity - Rvelocity_half);
		if (err < tmp_err)
			err = tmp_err;

		if (err < eps || step_time < all_time_step / max_num_step) { //Error checking
			current_model->wheel.Coord = (16 * Rcoord_half - Rcoord) / 15; //solve model
			current_model->wheel.Velocity = (16 * Rvelocity_half - Rvelocity) / 15;
			*time_left -= step_time;
			solve_body(current_model, koef_model, step_time);
			break;
		}
		else {
			step_time /= 2;//all new calculation with new h
		}
	}
}

void solve_body(state_model *current_model, const koef_of_model *koef_model, double step_time) {
	//At the moment, we integrate simply with a given step

	func_solve_acc_body(current_model, koef_model, true); //solv acceleration

	runge_K K;
	runge_koef_body(current_model->body.Velocity, current_model->body.Acceleration, koef_model, step_time, &K);//solve koef

	current_model->body.Coord + solve_koef_coord(&K);       //solve coord and velocity
	current_model->body.Velocity + solve_koef_velocity(&K);
}






//very BAD
void next_step_no_N(FILE* log, struct state_model* const current_model, const struct koef_of_model* koef_model, const struct surface* current_surface, double* time_left) {
	//we flying
	double time = *time_left;
	Vector2 tmp_coord;
	double height_above_ground = -100 * koef_model->wheel.radius;
	while (true) {
		tmp_coord = current_model->wheel.Coord;
		tmp_coord.x += current_model->wheel.Velocity.x * time; // x = x0 + vt
		tmp_coord.y += current_model->wheel.Velocity.y * time - koef_model->world.gravity * time * time / 2; // y = y0 + vt - (gt^2)/2
		double current_surface_height = tan(current_surface->angle) * tmp_coord.x + current_surface->start_y - current_surface->start_x * tan(current_surface->angle);
		height_above_ground = tmp_coord.y - koef_model->wheel.radius - current_surface_height;
		
		if (fabs(height_above_ground) > eps*0.1 || height_above_ground > 0) break;
		time /= 2;
	}
	//solve wheel without body
	current_model->wheel.Coord.x += current_model->wheel.Velocity.x * time; // x = x0 + vt
	current_model->wheel.Coord.y += current_model->wheel.Velocity.y * time - koef_model->world.gravity * time * time / 2; // y = y0 + vt - (gt^2)/2
	current_model->wheel.Velocity.y -= koef_model->world.gravity * time; // v_y = v0_y - gt
	
	//solve body The shift is the same as that of the wheel
	current_model->body.Coord.x += current_model->wheel.Velocity.x * time; // x = x0 + vt
	current_model->body.Coord.y += current_model->wheel.Velocity.y * time - koef_model->world.gravity * time * time / 2; // y = y0 + vt - (gt^2)/2
	current_model->body.Velocity.y -= koef_model->world.gravity * time; // v_y = v0_y - gt

	*time_left -= time;
}