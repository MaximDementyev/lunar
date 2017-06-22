#include "stdafx.h"

const double eps = 1e-3; // ïîäîáðàòü

Vector2 func_solve_acceleration(Vector2* Velocity, koef_of_model* koef_model, double* force, surface* current_surface) {
	Vector2 res;
	double acceleration;
	if (norm(Velocity) > eps) { //check zero speed
		//find acceleration in ñonnected coordinate system
		acceleration = *force - current_surface->mu * koef_model->mass * koef_model->gravity * cos_deg(current_surface->angle) * sign(Velocity->x * cos_deg(current_surface->angle)
			- koef_model->mass * koef_model->gravity * sin_deg(current_surface->angle)) / koef_model->mass;
		
		//Conversion to an inertial coordinate system
		res.x = acceleration * cos_deg(current_surface->angle);
		res.y = acceleration * sin_deg(current_surface->angle);
		return res;
	}else{
		//tmp_force Just a convenient change of coordinates (All forces except friction on the connected x-axis = F-mg*sin(alpha))
		double tmp_force = *force - koef_model->mass * koef_model->gravity * sin_deg(current_surface->angle);
		if (fabs(tmp_force) <= fabs(current_surface->mu * (*force) - koef_model->mass * koef_model->gravity * cos_deg(current_surface->angle))) // body is at rest
			return res;
		else {
			acceleration = (tmp_force - current_surface->mu * koef_model->mass * koef_model->gravity * cos_deg(current_surface->angle) * sign(tmp_force)) / koef_model->mass; //body rested, but began to move (Q>Ftr)
			res.x = acceleration * cos_deg(current_surface->angle);
			res.y = acceleration * sin_deg(current_surface->angle);
			return res;
		}
	}
}

void runge_koef(Vector2* solve_velocity, Vector2* solve_acceleration, koef_of_model* koef_model, surface* current_surface, double* force, double* h, runge_K* K) {
	
	//calculate all koef for runge

	K->kx1.k1 = *solve_velocity * (*h);
	K->kx2.k1 = *solve_acceleration * (*h);
	K->kx3.k1 = func_solve_acceleration(solve_velocity,  koef_model, force, current_surface) * (*h);

	K->kx1.k2 = (*solve_velocity + K->kx1.k1 / 2) * (*h);
	K->kx2.k2 = (*solve_acceleration + K->kx2.k1 / 2) * (*h);
	K->kx3.k2 = (func_solve_acceleration(&(*solve_velocity + K->kx3.k1 / 2), koef_model, force, current_surface)) * (*h);

	K->kx1.k3 = (*solve_velocity + K->kx1.k2 / 2) * (*h);
	K->kx2.k3 = (*solve_acceleration + K->kx2.k2 / 2) * (*h);
	K->kx3.k3 = func_solve_acceleration(&(*solve_velocity + K->kx3.k2 / 2), koef_model, force, current_surface) * (*h);

	K->kx1.k4 = (*solve_velocity + K->kx1.k3) * (*h);
	K->kx2.k4 = (*solve_acceleration + K->kx2.k3) * (*h);
	K->kx3.k4 = func_solve_acceleration(&(*solve_velocity + K->kx3.k3), koef_model, force, current_surface) * (*h);
}

Vector2 solve_koef_coord(runge_K* K) { //Solution function
	return (K->kx1.k1 + 2 * K->kx1.k2 + 2 * K->kx1.k3 + K->kx1.k4) / 6;
}

Vector2 solve_koef_velocity(runge_K* K) {//Solution function
	return (K->kx2.k1 + 2 * K->kx2.k2 + 2 * K->kx2.k3 + K->kx2.k4) / 6;
}