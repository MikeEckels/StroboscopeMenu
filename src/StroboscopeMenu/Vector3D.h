#ifndef VECTOR_3D_H
#define VECTOR_3D_H

#include <stdint.h>

struct Vector3D {
	uint16_t x = 0;
	uint16_t y = 0;
	uint16_t z = 0;

	Vector3D() {}
	Vector3D(uint16_t x, uint16_t y) : x(x), y(y) {}
	Vector3D(uint16_t x, uint16_t y, uint16_t z) : x(x), y(y), z(z) {}
	~Vector3D() {}
};

#endif //VECTOR_3D_H
