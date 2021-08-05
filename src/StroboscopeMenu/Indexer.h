#ifndef INDEXER_H
#define INDEXER_H

#include <math.h>
#include <stdint.h>

#include "Vector3D.h"

class Indexer {
protected:
	Vector3D size = { 0, 0 };
	uint8_t stroke = 0;

	Vector3D position = { 0, 0 };
	uint8_t currentIndex = 0;
	uint8_t previousIndex = 0;

public:
	Indexer();
	Indexer(Vector3D size, uint8_t stroke);
	~Indexer();

	Vector3D GetSize();
	uint8_t GetStroke();
	Vector3D GetPosition();
	uint8_t GetPositionIndex();
	uint8_t GetPreviousPositionIndex();

	void SetSize(Vector3D size);
	void SetStroke(uint8_t stroke);
	void SetPosition(Vector3D position);
};

#endif //INDEXER_H
