#pragma once
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
	
	Icon() {
		this->iconId = ++currentIconId;		
	}

	Icon(Vector3D size, uint16_t glyphId, const char* name, const uint8_t* font) :
		size(size), glyphId(glyphId),  name(name), font(font) {

		this->iconId = ++currentIconId;
	}

	~Icon() {
		--currentIconId;
	}

	Vector3D GetSize() {
		return this->size;
	}

	Vector3D GetPosition()  {
		return this->position;
	}

	uint16_t GetGlyphId() {
		return this->glyphId;
	}

	uint8_t GetIconId() {
		return this->iconId;
	}

	const char* GetName() {
		return this->name;
	}

	const uint8_t* GetFont() {
		return this->font;
	}

	void SetPosition(Vector3D position) {
		this->position = position;
	}
};