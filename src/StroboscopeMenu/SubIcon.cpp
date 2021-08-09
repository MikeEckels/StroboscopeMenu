#include "SubIcon.h"

SubIcon::SubIcon() { this->isSub = true; }

SubIcon::SubIcon(Vector3D size, uint16_t glyphId, const char* name, const uint8_t* font, Action* action) : Element(size, glyphId, name, font, action) { this->isSub = true; }

SubIcon::~SubIcon() {}