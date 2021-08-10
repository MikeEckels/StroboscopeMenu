#include "Element.h"

Element::Element() {}

Element::Element(Vector3D size, uint16_t glyphId, const char* name, const uint8_t* font, Action* action) :
	size(size), glyphId(glyphId), name(name), font(font), action(action) {}

Element::~Element() {}

Vector3D Element::GetSize() {
	return this->size;
}

Vector3D Element::GetPosition() {
	return this->position;
}

uint16_t Element::GetGlyphId() {
	return this->glyphId;
}

const char* Element::GetName() {
	return this->name;
}

const uint8_t* Element::GetFont() {
	return this->font;
}

Action* Element::GetAction() {
	return this->action;
}

void Element::SetPosition(Vector3D position) {
	this->position = position;
}
