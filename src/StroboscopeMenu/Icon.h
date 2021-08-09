#ifndef ICON_H
#define ICON_H

#include <stdint.h>
#include "Element.h"

#include "Vector3D.h"
#include "Action.h"

class Icon : public Element {
public:
	Icon();
	Icon(Vector3D size, uint16_t glyphId, const char* name, const uint8_t* font, Action* action);
	~Icon();
};

#endif //ICON_H
