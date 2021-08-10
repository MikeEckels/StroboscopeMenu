#include "Icon.h"

Icon::Icon() {
	this->id = ++currentId;
}

Icon::Icon(Vector3D size, uint16_t glyphId, const char* name, const uint8_t* font, Action* action) : Element(size, glyphId, name, font, action) {
	this->id = ++currentId;
}

Icon::~Icon() {
	--currentId;
}

uint8_t Icon::GetId() {
	return this->id;
}