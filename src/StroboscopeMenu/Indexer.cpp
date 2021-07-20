#include "Indexer.h"

Indexer::Indexer() {}

Indexer::Indexer(Vector3D size, uint8_t stroke) : size(size), stroke(stroke) {
	this->size.z = ((0.5) * (sqrt((pow(this->size.x, 2)) + (pow(this->size.y, 2)))));
}

Indexer::~Indexer() {}

Vector3D Indexer::GetSize() {
	return this->size;
}

uint8_t Indexer::GetStroke() {
	return this->stroke;
}

Vector3D Indexer::GetPosition() {
	return this->position;
}

uint8_t Indexer::GetPositionIndex() {
	return this->currentIndex;
}

void Indexer::SetSize(Vector3D size) {
	this->size = size;
}

void Indexer::SetStroke(uint8_t stroke) {
	this->stroke = stroke;
}

void Indexer::SetPosition(Vector3D position) {
	this->position = position;
}