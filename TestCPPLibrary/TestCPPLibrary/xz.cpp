#include"stdafx.h"
const double eps = 1e-5; //The error of touching the wheel of the earth

double find_earth(state_model* current_model, koef_of_model* koef_model, surface* current_surface) {
	double b = tan_deg(current_surface->angle * current_model->Velocity.x - current_model->Velocity.y); //Coefficient before the first power in the quadratic equation
	double D = b * b / 2 * koef_model->gravity * (tan_deg(current_surface->angle) * current_model->Coord.x + koef_model->radius - current_model->Coord.y); //Discriminant
	if (D < 0) return -2; //error! We fell through the texture
	
	double touch_time = (-b + sqrt(D)) / koef_model->gravity; //Surface touch time
	double find_tau = (current_model->Coord.x + current_model->Velocity.x * touch_time) / current_surface->limitation_x; //Touch point
	if (find_tau < 0 || find_tau > 1) return -1; // Touching outside a known surface

	return touch_time;
}

double time_no_N(state_model* current_model, surface* current_surface) {
	if (current_model->Velocity.x > 0)
		return (current_surface->start_x + current_surface->limitation_x - current_model->Coord.x) / current_model->Velocity.x;
	else
		return (current_surface->start_x - current_model->Coord.x) / current_model->Velocity.x;
}

void hit(state_model* current_model, koef_of_model* koef_model, surface* current_surface) {
	struct Vector2 guide_surface; //Surface vector guide
	guide_surface.x = cos_deg(current_surface->angle);
	guide_surface.y = sin_deg(current_surface->angle);

	current_model->Velocity = dotprod(current_model->Velocity, guide_surface) / norm(guide_surface) * guide_surface; //find progection
}

int touch_test(state_model* current_model, surface* current_surface) {
	double �urrent_surface_height = tan_deg(current_surface->angle) * current_model->Coord.x + current_surface->srart_y - current_surface->start_x * tan_deg(current_surface->angle);
	if (�urrent_surface_height > current_model->Coord.y) return -1;
	if (fabs(�urrent_surface_height - current_model->Coord.y) < eps) return 1;
	return 0;
}
