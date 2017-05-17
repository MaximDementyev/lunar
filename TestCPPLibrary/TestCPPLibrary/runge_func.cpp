#include "stdafx.h"

const double eps = 1e-3; // ïîäîáðàòü

Vector2 func_solve_acceleration(Vector2 Velocity, koef_of_model koef_model, double alpha, double mu) {
	Vector2 res;
	double acceleration;
	if (norm(Velocity) > eps) { //check zero speed
		//find acceleration in ñonnected coordinate system
		acceleration = koef_model.force - mu * koef_model.mass * koef_model.gravity * cos_deg(alpha) * sign(Velocity.x * cos_deg(alpha)
			- koef_model.mass * koef_model.gravity * sin_deg(alpha)) / koef_model.mass;
		
		//Conversion to an inertial coordinate system
		res.x = acceleration * cos_deg(alpha);
		res.y = acceleration * sin_deg(alpha);
		return res;
	}else{
		//tmp_force Just a convenient change of coordinates (All forces except friction on the connected x-axis = F-mg*sin(alpha))
		double tmp_force = koef_model.force - koef_model.mass * koef_model.gravity * sin_deg(alpha);
		if (fabs(tmp_force) <= fabs(mu * koef_model.force - koef_model.mass * koef_model.gravity * cos_deg(alpha))) // body is at rest
			return res;
		else {
			acceleration = (tmp_force - mu * koef_model.mass * koef_model.gravity * cos_deg(alpha) * sign(tmp_force)) / koef_model.mass; //body rested, but began to move (Q>Ftr)
			res.x = acceleration * cos_deg(alpha);
			res.y = acceleration * sin_deg(alpha);
			return res;
		}
	}
}

runge_K runge_koef(Vector2 solve_velocity, Vector2 solve_acceleration, double h, koef_of_model koef_model, double alpha, double mu) {
	
	//calculate all koef for runge
	runge_K K;

	K.kx1.k1 = solve_velocity * h;
	K.kx2.k1 = solve_acceleration * h;
	K.kx3.k1 = func_solve_acceleration(solve_velocity,  koef_model, alpha,  mu) * h;

	K.kx1.k2 = (solve_velocity + K.kx1.k1 / 2) * h;
	K.kx2.k2 = (solve_acceleration + K.kx2.k1 / 2) * h;
	K.kx3.k2 = (func_solve_acceleration(solve_velocity + K.kx3.k1 / 2, koef_model, alpha, mu))*h;

	K.kx1.k3 = (solve_velocity + K.kx1.k2 / 2)*h;
	K.kx2.k3 = (solve_acceleration + K.kx2.k2 / 2)*h;
	K.kx3.k3 = func_solve_acceleration(solve_velocity + K.kx3.k2 / 2, koef_model, alpha, mu)*h;

	K.kx1.k4 = (solve_velocity + K.kx1.k3)*h;
	K.kx2.k4 = (solve_acceleration + K.kx2.k3)*h;
	K.kx3.k4 = func_solve_acceleration(solve_velocity + K.kx3.k3, koef_model, alpha, mu)*h;

}

Vector2 solve_koef_coord(runge_K K) { //Solution function
	return (K.kx1.k1 + 2 * K.kx1.k2 + 2 * K.kx1.k3 + K.kx1.k4) / 6;
}

Vector2 solve_koef_velocity(runge_K K) {//Solution function
	return (K.kx2.k1 + 2 * K.kx2.k2 + 2 * K.kx2.k3 + K.kx2.k4) / 6;
}