#include "Element.h"

Element::Element() {
	this->id = ++currentId;
}

Element::Element(Vector3D size, uint16_t glyphId, const char* name, const uint8_t* font, Action* action) :
	size(size), glyphId(glyphId), name(name), font(font), action(action) {

	this->id = ++currentId;
}

Element::~Element() {
	--currentId;
}

Vector3D Element::GetSize() {
	return this->size;
}

Vector3D Element::GetPosition() {
	return this->position;
}

uint16_t Element::GetGlyphId() {
	return this->glyphId;
}

uint8_t Element::GetId() {
	return this->id;
}

const char* Element::GetName() {
	return this->name;
}

const uint8_t* Element::GetFont() {
	return this->font;
}

bool Element::GetType() {
	return this->isSub;
}

Action* Element::GetAction() {
	return this->action;
}

void Element::SetPosition(Vector3D position) {
	this->position = position;
}
