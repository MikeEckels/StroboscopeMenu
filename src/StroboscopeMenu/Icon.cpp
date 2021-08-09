#include "Icon.h"

Icon::Icon() { this->isSub = false; }

Icon::Icon(Vector3D size, uint16_t glyphId, const char* name, const uint8_t* font, Action* action) : Element(size, glyphId, name, font, action) { this->isSub = false; }

Icon::~Icon() {}
