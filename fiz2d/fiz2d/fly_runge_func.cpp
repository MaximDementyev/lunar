#include"stdafx.h"
#include"function_header.h"

void fly_acc(state_model *current_model, const koef_of_model * koef_model) {
	current_model->body.Acceleration.x = current_model->wheel.Acceleration.x = 0; //we fly. acc_x = 0
	const auto deformation_susp = deformation_suspension(current_model->body.Coord, current_model->wheel.Coord, koef_model); //find deformatin suspension
	current_model->body.Acceleration.y = (-koef_model->body.mass * koef_model->world.gravity + deformation_susp * koef_model->wheel.rigidity_suspension) / koef_model->body.mass;//solve acc_y body
	current_model->wheel.Acceleration.y = -(koef_model->wheel.mass * koef_model->world.gravity + deformation_susp * koef_model->wheel.rigidity_suspension) / koef_model->wheel.mass;//solve acc_y wheel
}

void fly_runge_koef(const Vector2 Velocity, const Vector2 Acceleration, const double h, runge_K* K) {

	//calculate all koef for runge
	K->kx1.k1 = Velocity * h;
	K->kx2.k1 = Acceleration * h;

	K->kx1.k2 = (Velocity + K->kx1.k1 / 2) * h;
	K->kx2.k2 = (Acceleration + K->kx2.k1 / 2) * h;

	K->kx1.k3 = (Velocity + K->kx1.k2 / 2) * h;
	K->kx2.k3 = (Acceleration + K->kx2.k2 / 2) * h;

	K->kx1.k4 = (Velocity + K->kx1.k3) * h;
	K->kx2.k4 = (Acceleration + K->kx2.k3)* h;
}