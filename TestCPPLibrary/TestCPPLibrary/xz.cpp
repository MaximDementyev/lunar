#include"stdafx.h"
const double eps = 1e-4; //The error of touching the wheel of the earth

double find_earth(const state_model* current_model, const koef_of_model* koef_model, const surface* current_surface) {
	double b = tan(current_surface->angle) * current_model->Velocity.x - current_model->Velocity.y; //Coefficient before the first power in the quadratic equation
	double c = (current_model->Coord.x - current_surface->start_x) * tan(current_surface->angle) - current_model->Coord.y + current_surface->start_y - koef_model->radius;//Coefficient before the zero power in the quadratic equation
	double D = b * b - 2 * koef_model->gravity * c;	
/*	FILE *log = fopen("xz_log.txt", "a");
	fprintf(log, "\n\ncurrent_model\n   Corrd.x = %.4lf\n   Corrd.y = %.4lf\n   Velocity.x = %.4lf\n   Velocity.y = %.4lf\n\n", current_model->Coord.x, current_model->Coord.y, current_model->Velocity.x, current_model->Velocity.y);
	fprintf(log, "current_surface\n   angle = %.4lf\n   lim_x = %.4lf\n   mu = %.4lf\n   start_x = %.4lf\n   start_y = %.4lf\n\n", current_surface->angle, current_surface->limitation_x, current_surface->mu, current_surface->start_x, current_surface->start_y);
	fprintf(log, "b = %.10lf\nc = %.10lf\nD = %.10lf", b,c, D);
	fclose(log);*/
	if (D < 0 && fabs(b) > 1e-7) {
	/*	log = fopen("xz_log.txt", "a");
		fprintf(log, "!!!!!!!!!!!!!!!!!!!!  D < 0   !!!!!!!!!!!!!!!!\n");
		fclose(log);*/
		return -2; //error! We fell through the texture 
	}
	double touch_time;
	if (fabs(b) > 1e-9)
		touch_time = (-b + sqrt(D)) / koef_model->gravity; //Surface touch time
	else
		touch_time = -2 * c / koef_model->gravity;
	/*log = fopen("xz_log.txt", "a");
	fprintf(log, "touch_time = %.10lf\n",touch_time);
	fclose(log);*/
	double find_tau = (current_model->Coord.x + current_model->Velocity.x * touch_time - current_surface->start_x) / current_surface->limitation_x; //Touch point
	if (find_tau < 0 || find_tau > 1) return -1; // Touching outside a known surface

	return touch_time;
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
