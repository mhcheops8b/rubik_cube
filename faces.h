#pragma once
#ifndef __FACES_H__
#define __FACES_H__

namespace rubik_cube {

	struct Faces {
		enum faces {U = 0, L = 1, F = 2, R = 3, B = 4, D = 5};

		static const char labels[];
	};
}
#endif
