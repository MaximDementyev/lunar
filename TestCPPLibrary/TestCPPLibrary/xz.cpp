#include"stdafx.h"

double find_earth(state_model current_model, koef_of_model koef_model, surface current_surface) {
	double b = tan_deg(current_surface.angle * current_model.Velocity.x - current_model.Velocity.y); //Coefficient before the first power in the quadratic equation
	double D = b * b / 2 * koef_model.gravity * (tan_deg(current_surface.angle) * current_model.Coord.x + koef_model.radius - current_model.Coord.y); //Discriminant
	if (D < 0) return -2; //error! We fell through the texture
	
	double touch_time = (-b + sqrt(D)) / koef_model.gravity; //Surface touch time
	double find_tau = (current_model.Coord.x + current_model.Velocity.x * touch_time) / current_surface.limitation_x; //Touch point
	if (find_tau < 0 || find_tau > 1) return -1; // Touching outside a known surface

	return touch_time;
}

struct Vector2 hit(state_model current_model, koef_of_model koef_model, surface current_surface) {
	struct Vector2 guide_surface;   //Surface vector guide
	guide_surface.x = cos_deg(current_surface.angle);
	guide_surface.y = sin_deg(current_surface.angle);

	double projection = dotprod(current_model.Velocity, guide_surface) / norm(guide_surface);   //Module of the velocity vector projection onto the surface
	
	struct Vector2 Velocity_after_impact = projection * guide_surface; //Velocity after impact :) Accurate to a sign
	Velocity_after_impact *= sign(dotprod(Velocity_after_impact, current_model.Velocity)); //Checked the sign
	return Velocity_after_impact;
}