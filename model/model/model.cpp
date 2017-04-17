#include "Header.h"
#include <stdexcept>


namespace all_Body {
	class body{
		public:
			body(struct point start_coord, double h);
			~body();
			struct point solve(struct point delta);
			//______
			struct point coord;
		private:
			//______
			double step;
	};

	body::body(struct point start_coord, double delta){
		coord = start_coord;
		step = delta;
	}

	body::~body()
	{
	}

	point body::solve(point h){
		coord.x += h.x * step;
		coord.y += h.y * step;
		return point(coord);
	}

}