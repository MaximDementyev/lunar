#include"stdafx.h"
#include"function_header.h"

Vector2 func_solve_acc_body(state_model* current_model, const koef_of_model* koef_model, const bool flag_record) {
	double deformation_suspension = koef_model->wheel.position - norm(current_model->body.Coord, current_model->wheel.Coord);//We assume the deformation of the spring

	Vector2 res_acc(0, (koef_model->wheel.rigidity_suspension * deformation_suspension - koef_model->body.mass * koef_model->world.gravity) / koef_model->body.mass);
	if (flag_record == true)
		current_model->body.Acceleration = res_acc;
	return res_acc;
} 

Vector2 func_solve_acc_wheel_noN(state_model* current_model, const koef_of_model* koef_model, const bool flag_record) {
	double deformation_suspension = koef_model->wheel.position - norm(current_model->body.Coord, current_model->wheel.Coord);//We assume the deformation of the spring

	Vector2 res_acc(0, (-koef_model->wheel.rigidity_suspension * deformation_suspension - koef_model->body.mass * koef_model->world.gravity) / koef_model->body.mass);
	if (flag_record == true)
		current_model->wheel.Acceleration = res_acc;
	return res_acc;
}



void runge_koef_body(const Vector2 Velocity, const Vector2 Acceleration, const koef_of_model* koef_model, const double h, runge_K* K) {
	//calculate all koef for runge
	K->kx1.k1 = Velocity * h;
	K->kx2.k1 = Acceleration * h;

	K->kx1.k2 = (Velocity + K->kx1.k1 / 2) * h;
	K->kx2.k2 = (Acceleration + K->kx2.k1 / 2) * h;
	
	K->kx1.k3 = (Velocity + K->kx1.k2 / 2) * h;
	K->kx2.k3 = (Acceleration + K->kx2.k2 / 2) * h;
	
	K->kx1.k4 = (Velocity + K->kx1.k3) * h;
	K->kx2.k4 = (Acceleration + K->kx2.k3) * h;
}