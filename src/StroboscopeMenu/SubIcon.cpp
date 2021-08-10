#include "SubIcon.h"

SubIcon::SubIcon() {
	this->id = ++currentId;
}

SubIcon::SubIcon(Vector3D size, uint16_t glyphId, const char* name, const uint8_t* font, Action* action) : Element(size, glyphId, name, font, action) {
	this->id = ++currentId;
}

SubIcon::~SubIcon() {
	--currentId;
}

uint8_t SubIcon::GetId() {
	return this->id;
}