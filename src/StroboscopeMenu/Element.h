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

	uint8_t id = 0;
	static int8_t currentId;
	Vector3D position = { 0, 0 };

	bool isSub = false;
	Action* action;

public:
	Element();
	Element(Vector3D size, uint16_t glyphId, const char* name, const uint8_t* font, Action* action);
	~Element();

	Vector3D GetSize();
	Vector3D GetPosition();
	uint16_t GetGlyphId();
	uint8_t GetId();
	const char* GetName();
	const uint8_t* GetFont();
	bool GetType();
	Action* GetAction();

	void SetPosition(Vector3D position);
};

#endif //ELEMENT_H
