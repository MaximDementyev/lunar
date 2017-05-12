#include "Header.h"
#include <stdexcept>

namespace all_Body
{
	void body::print() const
	{
		printf_s("Hello mzfucka!\n");
	}

	double body::sum()
	{
		x += step;
		y += step;
		return x + y;
	}
}