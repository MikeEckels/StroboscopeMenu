#ifndef ELEMENT_H
#define ELEMENT_H

#include <stdint.h>

#include "Vector3D.h"
#include "Action.h"

class Element {
protected:
	Vector3D size = { 0, 0, 0 };
	uint16_t glyphId = 0;
	const char* name = 0;
	const uint8_t* font = 0;

	Vector3D position = { 0, 0 };

	Action* action;

public:
	Element();
	Element(Vector3D size, uint16_t glyphId, const char* name, const uint8_t* font, Action* action);
	virtual ~Element();

	Vector3D GetSize();
	Vector3D GetPosition();
	uint16_t GetGlyphId();
	const char* GetName();
	virtual uint8_t GetId() = 0;
	const uint8_t* GetFont();
	Action* GetAction();

	void SetPosition(Vector3D position);
};

#endif //ELEMENT_H
