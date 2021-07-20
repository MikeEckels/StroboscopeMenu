#ifndef INDEXER_H
#define INDEXER_H

#include <Math.h>
#include <stdint.h>

#include "Vector3D.h"

class Indexer {
protected:
	Vector3D size = { 0, 0 };
	uint8_t stroke = 0;

	Vector3D position = { 0, 0 };
	uint8_t currentIndex = 0;

public:

	Indexer() {}

	Indexer(Vector3D size, uint8_t stroke) : size(size), stroke(stroke){
		this->size.z = ((0.5) * (sqrt((pow(this->size.x, 2)) + (pow(this->size.y, 2)))));
	}

	~Indexer() {}

	Vector3D GetSize() {
		return this->size;
	}

	uint8_t GetStroke() {
		return this->stroke;
	}

	Vector3D GetPosition() {
		return this->position;
	}

	uint8_t GetPositionIndex() {
		return this->currentIndex;
	}

	void SetSize(Vector3D size) {
		this->size = size;
	}

	void SetStroke(uint8_t stroke) {
		this->stroke = stroke;
	}

	void SetPosition(Vector3D position) {
		this->position = position;
	}
};

#endif //INDEXER_H
