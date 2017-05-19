#include"stdafx.h"

const double eps = 1e-6; // ���������


state_model next_step_N(state_model current_model, koef_of_model koef_model, surface current_surface, double force, double time, double limitation_x) {
	double h = 5;
	Vector2 solve_Acceleration = func_solve_acceleration(current_model.Velocity, koef_model, force, current_surface); // Acceleration calculation
	
	Vector2 Approximate_movement = current_model.Velocity * time + solve_Acceleration * time*time / 2; //Approximate movement calculation in lineral model

	runge_K K = runge_koef(current_model.Velocity, solve_Acceleration, koef_model, current_surface, force, h); // Calculation koef for step h
	if ((solve_koef_coord(K)).x > limitation_x) {
		h = h / 2;
		//continue; // ������ ���������
	}

	Vector2 z1, z2; // solve fo step h
	z1 = current_model.Coord + solve_koef_coord(K);
	z2 = current_model.Velocity + solve_koef_velocity(K);
	

	runge_K Km = runge_koef(current_model.Velocity, solve_Acceleration, koef_model, current_surface, force, h/2); //Calculation koef for step h/2
	//solve for step h/2
	Vector2 y1, y2;
	y1 = current_model.Coord + solve_koef_coord(Km);
	y2 = current_model.Velocity + solve_koef_velocity(Km);

	solve_Acceleration = func_solve_acceleration(y2, koef_model, force, current_surface); //Calculation of a new acceleration
	Km = runge_koef(y2, solve_Acceleration, koef_model, current_surface, force, h/2); //Calculation koef for time+h and step h/2

	//solve for time+h and step h/2
	y1 = y1 + solve_koef_coord(Km);
	y2 = y2 + solve_koef_velocity(Km);

	double err = norm(z1 - y1); //find max err
	double tmp_err = norm(z2 - y2);
	if (err < tmp_err)
		err = tmp_err;

	if (err < eps) { //Error checking
		current_model.Coord = (16 * y1 - z1) / 15; //solve model
		current_model.Velocity = (16 * y2 - z2) / 15;
		time = time + h;
		//return;
	}else{
		h = h / 2;//all new calculation with new h
	}
	//return;
}

state_model next_step_no_N(state_model current_model, double limitation_x, koef_of_model koef_model) {
	//return;
}