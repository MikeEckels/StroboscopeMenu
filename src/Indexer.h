#pragma once
#include"Vector3D.h"

class Indexer {
private:
	Vector3D size = { 0, 0 };
	Vector3D position = { 0, 0 };

public:
	Indexer() {}
	Indexer(Vector3D size, Vector3D position) : size(size), position(position) {}
	~Indexer() {}

};
