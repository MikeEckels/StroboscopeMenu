#pragma once
#include "Vector3D.h"

class Icon {
private:
	U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2 = 0;
	Vector3D size = { 0, 0, 0 };
	uint16_t glyphId = 0;
	const char* name = 0;
	const uint8_t* font = 0;

	uint8_t iconId = 0;
	static int8_t currentIconId;
	Vector3D position = { 0, 0 };

	void SetSpacing() {
		static uint8_t pos = this->size.z;

		this->position.x = pos;
		this->position.y = ((0.5) * (u8g2->getDisplayHeight() + this->size.y));
		pos += this->size.x + this->size.z;
	}

public:
	
	Icon(U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2) : u8g2(u8g2) {
		this->iconId = ++currentIconId;
		SetSpacing();		
	}

	Icon(U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2, Vector3D size, uint16_t glyphId, const char* name, const uint8_t* font) :
		u8g2(u8g2), size(size), glyphId(glyphId),  name(name), font(font) {

		this->iconId = ++currentIconId;
		SetSpacing();
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
};