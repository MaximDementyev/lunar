#include"stdafx.h"
#include"function_header.h"

const double eps = 1e-4; //The error of touching the wheel of the earth

find_earth_error find_earth(const state_model* current_model, const koef_of_model* koef_model, const surface* current_surface, double* res) {
	double b = tan(current_surface->angle) * current_model->Velocity.x - current_model->Velocity.y; //Coefficient before the first power in the quadratic equation
	double c = (current_model->Coord.x - current_surface->start_x) * tan(current_surface->angle) - current_model->Coord.y + current_surface->start_y - koef_model->radius;//Coefficient before the zero power in the quadratic equation
	double D = b * b - 2 * koef_model->gravity * c;
	if (D < 0) return find_earth_error::fell_through; //error! We fell through the texture 

	double touch_time = (-b + sqrt(D)) / koef_model->gravity; //Surface touch time
	double find_tau = (current_model->Coord.x + current_model->Velocity.x * touch_time - current_surface->start_x) / current_surface->limitation_x; //Touch point
	if (find_tau < 0 || find_tau > 1) return find_earth_error::touch_outside; // Touching outside a known surface
	*res = touch_time;
	return find_earth_error::normal;
}

double time_no_N(const state_model* current_model, const surface* current_surface) {
	if (current_model->Velocity.x > 0)
		return (current_surface->start_x + current_surface->limitation_x - current_model->Coord.x) / current_model->Velocity.x;
	else
		return (current_surface->start_x - current_model->Coord.x) / current_model->Velocity.x;
}

void hit(state_model* current_model, const koef_of_model* koef_model, const surface* current_surface) {
	struct Vector2 guide_surface; //Surface vector guide
	guide_surface.x = cos(current_surface->angle);
	guide_surface.y = sin(current_surface->angle);

	current_model->Velocity = dotprod(current_model->Velocity, guide_surface) / norm(guide_surface) * guide_surface; //find progection
}

int touch_test(const state_model* current_model, const struct koef_of_model* koef_model, const surface* current_surface) {
	double current_surface_height = tan(current_surface->angle) * current_model->Coord.x + current_surface->start_y - current_surface->start_x * tan(current_surface->angle);
	if (current_surface_height > current_model->Coord.y - koef_model->radius) return -1;
	if (fabs(current_model->Coord.y - koef_model->radius - current_surface_height) < eps) return 1;
	return 0;
}


int speed_into_surface(const struct state_model* current_model, const struct surface* current_surface) {
	if (current_model->Velocity.y / norm(current_model->Velocity) > sin(current_surface->angle)) return 0;
	else return 1;
}

void hit_theend_step(struct state_model* const current_model, const struct koef_of_model* koef_model, const surface* current_surface, const bool contact) {
	if (touch_test(current_model, koef_model, current_surface) == 1 && contact == true) {
		if (speed_into_surface(current_model, current_surface) == 1) {
			hit(current_model, koef_model, current_surface);//Calculated impact against the surface, so as not to fall through again
		}
	}
}