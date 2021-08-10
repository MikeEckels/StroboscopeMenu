#ifndef ICON_H
#define ICON_H

#include <stdint.h>
#include "Element.h"

#include "Vector3D.h"
#include "Action.h"

class Icon : public Element {
private:
	uint8_t id = 0;
	static int8_t currentId;

public:
	Icon();
	Icon(Vector3D size, uint16_t glyphId, const char* name, const uint8_t* font, Action* action);
	~Icon();

	uint8_t GetId() override;
};

#endif //ICON_H
