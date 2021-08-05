#include "Icon.h"

Icon::Icon() {
	this->iconId = ++currentIconId;
}

Icon::Icon(Vector3D size, uint16_t glyphId, const char* name, const uint8_t* font) :
	size(size), glyphId(glyphId), name(name), font(font) {

	this->iconId = ++currentIconId;
}

Icon::~Icon() {
	--currentIconId;
}

Vector3D Icon::GetSize() {
	return this->size;
}

Vector3D Icon::GetPosition() {
	return this->position;
}

uint16_t Icon::GetGlyphId() {
	return this->glyphId;
}

uint8_t Icon::GetIconId() {
	return this->iconId;
}

const char* Icon::GetName() {
	return this->name;
}

const uint8_t* Icon::GetFont() {
	return this->font;
}

void Icon::SetPosition(Vector3D position) {
	this->position = position;
}
