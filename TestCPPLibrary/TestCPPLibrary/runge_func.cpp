#include "stdafx.h"

const double eps = 1e-3; // ïîäîáðàòü

inline Vector2 func_solve_acceleration(const Vector2* Velocity, const koef_of_model* koef_model, const double force, const surface* current_surface) {
	double acceleration;
	if (norm(Velocity) > eps) { //check zero speed
		//find acceleration in connected coordinate system
		acceleration = force - current_surface->mu * koef_model->mass * koef_model->gravity * cos(current_surface->angle) * sign(Velocity->x * cos(current_surface->angle)
			- koef_model->mass * koef_model->gravity * sin(current_surface->angle)) / koef_model->mass;
		return ñonversion_inertial_coordinate_system(acceleration, current_surface);
	}
	else {
		//tmp_force Just a convenient change of coordinates (All forces except friction on the connected x-axis = F-mg*sin(alpha))
		double tmp_force = force - koef_model->mass * koef_model->gravity * sin(current_surface->angle);
		if (fabs(tmp_force) <= fabs(current_surface->mu * koef_model->mass * koef_model->gravity * cos(current_surface->angle))) {// body is at rest
			Vector2 res;
			return res;
		} else {
			acceleration = (tmp_force - current_surface->mu * koef_model->mass * koef_model->gravity * cos(current_surface->angle) * sign(tmp_force)) / koef_model->mass; //body rested, but began to move (Q>Ftr)
			return ñonversion_inertial_coordinate_system(acceleration, current_surface);
		}
	}
}

inline struct Vector2 ñonversion_inertial_coordinate_system(const double val, const struct surface* current_surface) {
	Vector2 res;
	res.x = val * cos(current_surface->angle);
	res.y = val * sin(current_surface->angle);
	return res;
}

inline void runge_koef(const Vector2* solve_velocity, const Vector2* solve_acceleration, const koef_of_model* koef_model, const surface* current_surface, const double force, const double h, runge_K* K) {
	
	//calculate all koef for runge

	K->kx1.k1 = *solve_velocity * h;
	K->kx2.k1 = *solve_acceleration * h;
	K->kx3.k1 = func_solve_acceleration(solve_velocity,  koef_model, force, current_surface) * h;

	K->kx1.k2 = (*solve_velocity + K->kx1.k1 / 2) * h;
	K->kx2.k2 = (*solve_acceleration + K->kx2.k1 / 2) * h;
	K->kx3.k2 = (func_solve_acceleration(&(*solve_velocity + K->kx3.k1 / 2), koef_model, force, current_surface)) * h;

	K->kx1.k3 = (*solve_velocity + K->kx1.k2 / 2) * h;
	K->kx2.k3 = (*solve_acceleration + K->kx2.k2 / 2) * h;
	K->kx3.k3 = func_solve_acceleration(&(*solve_velocity + K->kx3.k2 / 2), koef_model, force, current_surface) * h;

	K->kx1.k4 = (*solve_velocity + K->kx1.k3) * h;
	K->kx2.k4 = (*solve_acceleration + K->kx2.k3) * h;
	K->kx3.k4 = func_solve_acceleration(&(*solve_velocity + K->kx3.k3), koef_model, force, current_surface) * h;
}

inline Vector2 solve_koef_coord(const runge_K* K) { //Solution function
	return (K->kx1.k1 + 2 * K->kx1.k2 + 2 * K->kx1.k3 + K->kx1.k4) / 6;
}

inline Vector2 solve_koef_velocity(const runge_K* K) {//Solution function
	return (K->kx2.k1 + 2 * K->kx2.k2 + 2 * K->kx2.k3 + K->kx2.k4) / 6;
}