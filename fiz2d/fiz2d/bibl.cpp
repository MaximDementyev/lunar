#include "stdafx.h"
#include"function_header.h"

double norm(const  Vector2& a, const  Vector2& b) {
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

double norm(const  Vector2& a) {
	return sqrt(a.x*a.x + a.y*a.y);
}

double sign(const double a) {
	if (a > 0) return 1;
	if (fabs(a) < 1e-18) return 0;
	else return -1;
}

double dotprod(const  Vector2 a, const  Vector2 b) {
	return a.x * b.x + a.y * b.y;
}

 Vector2 rotate_vec(const  Vector2 vec, const double phi) {
	return Vector2(vec.x * cos(phi) - vec.y * sin(phi), vec.x * sin(phi) + vec.y * cos(phi));
}


 bool transform_local_coord_to_global(state_model const* current_model) {
	 for (auto i = 0; i < current_model->number_wheel; ++i) {
		 current_model->wheel[i].state_wheel.coord = current_model->body.state_body.coord + rotate_vec(current_model->wheel->state_wheel.local_coord, current_model->body.state_body.pitch);
	 }
	 return true;
 }
