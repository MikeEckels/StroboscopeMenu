#ifndef ICON_H
#define ICON_H

#include <stdint.h>
#include "Vector3D.h"

class Icon {
private:
	Vector3D size = { 0, 0, 0 };
	uint16_t glyphId = 0;
	const char* name = 0;
	const uint8_t* font = 0;

	uint8_t iconId = 0;
	static int8_t currentIconId;
	Vector3D position = { 0, 0 };

public:
	
	Icon();
	Icon(Vector3D size, uint16_t glyphId, const char* name, const uint8_t* font);
	~Icon();

	Vector3D GetSize();
	Vector3D GetPosition();
	uint16_t GetGlyphId();
	uint8_t GetIconId();
	const char* GetName();
	const uint8_t* GetFont();

	void SetPosition(Vector3D position);
};

#endif //ICON_H