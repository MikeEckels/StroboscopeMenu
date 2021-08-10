#ifndef SUB_ICON_H
#define SUB_ICON_H

#include <stdint.h>
#include "Element.h"

#include "Vector3D.h"
#include "Action.h"

class SubIcon : public Element {
private:
	uint8_t id = 0;
	static int8_t currentId;

public:
	SubIcon();
	SubIcon(Vector3D size, uint16_t glyphId, const char* name, const uint8_t* font, Action* action);
	~SubIcon();

	uint8_t GetId() override;
};

#endif //SUB_ICON_H
