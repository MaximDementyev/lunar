#include "stdafx.h"
#include "function_header.h"

const double eps = 1e-2; // подобрать

Vector2 func_solve_acc_wheel(state_model* current_model, const Vector2* Velocity, const koef_of_model* koef_model, const double force, const surface* current_surface, const bool flag_record) {
	double deformation_suspension = koef_model->wheel.position - norm(current_model->body.Coord, current_model->wheel.Coord);//We assume the deformation of the spring
	double acceleration;
	struct Vector2 related_acc;
	if (deformation_suspension * koef_model->wheel.rigidity_suspension + koef_model->wheel.mass * koef_model->world.gravity >= 0) {//The spring presses against the ground
		if (norm(*Velocity) > eps) { //check zero speed
			// We are moving. Resistance is directed against speed
			//find acceleration in connected coordinate system
			acceleration = (force -
				current_surface->mu * (koef_model->wheel.mass * koef_model->world.gravity + deformation_suspension * koef_model->wheel.rigidity_suspension) * cos(current_surface->angle) * sign(Velocity->x) -
				(koef_model->wheel.mass * koef_model->world.gravity + deformation_suspension * koef_model->wheel.rigidity_suspension) * sin(current_surface-> angle)
				) / koef_model->wheel.mass;
			related_acc = rotate_vec(Vector2(acceleration, 0), current_surface->angle);
		} else {
			//tmp_force Just a convenient change of coordinates (All forces except friction on the connected x-axis = F-mg*sin(alpha))
			double tmp_force = force - (koef_model->wheel.mass * koef_model->world.gravity + deformation_suspension * koef_model->wheel.rigidity_suspension) * sin(current_surface->angle);
			if (fabs(tmp_force) <= fabs(current_surface->mu * (koef_model->wheel.mass * koef_model->world.gravity + deformation_suspension * koef_model->wheel.rigidity_suspension) * cos(current_surface->angle)))
				related_acc.set0();// body is at rest
			else {
				//body rested, but began to move (Q>Ftr)
				acceleration = (tmp_force - current_surface->mu * (koef_model->wheel.mass * koef_model->world.gravity + deformation_suspension * koef_model-> wheel.rigidity_suspension) * cos(current_surface->angle) * sign(tmp_force)) / koef_model->wheel.mass;
				related_acc = rotate_vec(Vector2(acceleration, 0), current_surface->angle);
			}
		}
	} else {
		related_acc.x = (force - koef_model->wheel.mass * koef_model->world.gravity * sin(current_surface->angle)) / koef_model->wheel.mass;
		related_acc.y = (-(koef_model->wheel.mass * koef_model->world.gravity + deformation_suspension * koef_model-> wheel.rigidity_suspension) * cos(koef_model->wheel.mass)) / koef_model->wheel.mass;
		related_acc = rotate_vec(related_acc, current_surface->angle);
	}
	if (flag_record == true) current_model->wheel.Acceleration = related_acc;
	return related_acc;
}


void runge_koef(state_model *current_model, const Vector2 Velocity, const Vector2 Acceleration, const koef_of_model* koef_model, const surface* current_surface, const double force, const double h, runge_K* K) {

	//calculate all koef for runge
	Vector2 tmp_velocity = Velocity;
	K->kx1.k1 = Velocity * h;
	K->kx2.k1 = func_solve_acc_wheel(current_model, &tmp_velocity, koef_model, force, current_surface,false) * h;

	tmp_velocity = Velocity + K->kx1.k1 / 2;
	K->kx1.k2 = tmp_velocity * h;
	K->kx2.k2 = (func_solve_acc_wheel(current_model, &tmp_velocity, koef_model, force, current_surface,false) + K->kx2.k1 / 2) * h;

	tmp_velocity = Velocity + K->kx1.k2 / 2;
	K->kx1.k3 = tmp_velocity * h;
	K->kx2.k3 = (func_solve_acc_wheel(current_model, &tmp_velocity, koef_model, force, current_surface,false) + K->kx2.k2 / 2) * h;

	tmp_velocity = Velocity + K->kx1.k3;
	K->kx1.k4 = tmp_velocity * h;
	K->kx2.k4 = (func_solve_acc_wheel(current_model, &tmp_velocity, koef_model, force, current_surface, false) + K->kx2.k3)* h;
}

Vector2 solve_koef_coord(const runge_K* K) { //Solution function
	return (K->kx1.k1 + 2 * K->kx1.k2 + 2 * K->kx1.k3 + K->kx1.k4) / 6.;
}

Vector2 solve_koef_velocity(const runge_K* K) {//Solution function
	return (K->kx2.k1 + 2 * K->kx2.k2 + 2 * K->kx2.k3 + K->kx2.k4) / 6.;
}

double err_runge(const Vector2 Yh, const Vector2 Yh_2) {
	Vector2 err = (Yh_2 - Yh) * 16 / 15.;
	return max(err.x, err.y);
}

double err_runge_body(const Vector2 Yh, const Vector2 Yh_2) {
	Vector2 err = (Yh_2 - Yh) * 16 / 15.;
	return err.y;
}