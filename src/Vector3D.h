#pragma once

struct Vector3D {
	uint8_t x = 0;
	uint8_t y = 0;
	uint8_t z = 0;

	Vector3D() {}
	Vector3D(uint8_t x, uint8_t y) : x(x), y(y) {}
	Vector3D(uint8_t x, uint8_t y, uint8_t z) : x(x), y(y), z(z) {}
	~Vector3D() {}
};