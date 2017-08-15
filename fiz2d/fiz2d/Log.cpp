#include "stdafx.h"
#include "function_header.h"

void print_model(FILE *log, const state_model const *model) {
	fprintf(log, "Body\n   coord - %.5lf   %.5lf\n   veloc - %.5lf   %.5lf\n", model->body.Coord.x, model->body.Coord.y, model->body.Velocity.x, model->body.Velocity.y);
	fprintf(log, "Wheel\n   coord - %.5lf   %.5lf\n   veloc - %.5lf   %.5lf\n\n", model->wheel.Coord.x, model->wheel.Coord.y, model->wheel.Velocity.x, model->wheel.Velocity.y);
}

void print_new_step(FILE *log) {
	fprintf(log, "\n\n!!!!!!!!!!!!\n\n");
}

void print_surface(FILE* log, const surface const* current_surface){
	fprintf(log, "current_surface\n  angle = %.10lf\n  left_h = %.2lf\n  right_h = %.2lf\n  start_x = %.10lf\n  start_y = %.10lf\n\n", current_surface->angle, current_surface->left_height, current_surface->right_height, current_surface->start_x, current_surface->start_y);
}