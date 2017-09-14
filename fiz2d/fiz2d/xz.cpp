#include"stdafx.h"
#include"function_header.h"

const double eps = 1e-4; //The error of touching the wheel of the earth

void hit(state_model* current_model, const koef_of_model* koef_model, const surface* current_surface) {
	struct Vector2 guide_surface; //Surface vector guide
	guide_surface.x = cos(current_surface->angle);
	guide_surface.y = sin(current_surface->angle);

	current_model->wheel.Velocity = dotprod(current_model->wheel.Velocity, guide_surface) / norm(guide_surface) * guide_surface; //find progection
	current_model->body.Velocity.x = current_model->wheel.Velocity.x; //The body from above along the x axis is rigidly connected to the wheel
}

int touch_test(state_model* current_model, const struct koef_of_model* koef_model, const surface* current_surface, double *current_surface_height) {
	//Find the height of the surface under the body
	double cur_surface_height = tan(current_surface->angle) * current_model->wheel.Coord.x + current_surface->start_y - current_surface->start_x * tan(current_surface->angle);
	if (current_surface_height != NULL)
		*current_surface_height = cur_surface_height;

	if (cur_surface_height > current_model->wheel.Coord.y - koef_model->wheel.radius) return -1;//Failed
	if (fabs(current_model->wheel.Coord.y - koef_model->wheel.radius - cur_surface_height) < eps) return 0;//Touch
	return 1;//Fly
}


int speed_into_surface(const struct state_model* current_model, const struct surface* current_surface) {//Determine the speed is directed into the surface of it
	if (current_model->wheel.Velocity.y / norm(current_model->wheel.Velocity) > sin(current_surface->angle)) return 0;//out
	else return 1; //in
}

void hit_theend_step(struct state_model* const current_model, const struct koef_of_model* koef_model, const surface* current_surface, const bool contact) {
	if (touch_test(current_model, koef_model, current_surface, NULL) == 1 && contact == true) {
		if (speed_into_surface(current_model, current_surface) == 1) {
			hit(current_model, koef_model, current_surface);//Calculated impact against the surface, so as not to fall through again
		}
	}
}

Vector2 center_mass(const state_model *current_model, const koef_of_model *koef_model) {
	Vector2 center; //center = 1/M * SUM(m_i*r_i); i = 1...N
	center = current_model->body.Coord * koef_model->body.mass + current_model->wheel.Coord * koef_model->wheel.mass;
	center /= koef_model->body.mass + koef_model->wheel.mass;
	return center;
}

double deformation_suspension(const Vector2 body, const Vector2 wheel, const koef_of_model *const koef_model) {
	double distance = norm(body, wheel);
	if (body.y < wheel.y) distance = -distance;
	double deformation = koef_model->wheel.position - distance;//We assume the deformation of the spring
	return deformation;
}