#include"stdafx.h"
#include "function_header.h"

bool transform_local_coord_to_global(state_model const* current_model) {
	for (auto i = 0; i < current_model->number_wheel; ++i) {
		current_model->wheel[i].state_wheel.coord = current_model->body.state_body.coord + rotate_vec(current_model->wheel->state_wheel.local_coord, current_model->body.state_body.pitch);
	}
	return true;
}

