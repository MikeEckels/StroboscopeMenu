#pragma once
#include <Math.h>
#include "Vector3D.h"
#include "IconList.h"

class Cursor {
private:
	U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2 = 0;
	Vector3D size = { 0, 0 };
	uint8_t stroke = 0;

	Vector3D position = { 0, 0 };
	uint8_t currentIndex = 0;

public:

	Cursor(U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2) : u8g2(u8g2) {}

	Cursor(U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2, Vector3D size, uint8_t stroke) : u8g2(u8g2), size(size), stroke(stroke){
		this->size.z = ((0.5) * (sqrt((pow(this->size.x, 2)) + (pow(this->size.y, 2)))));
	}

	~Cursor() {}

	Vector3D GetSize() {
		return this->size;
	}

	uint8_t GetStroke() {
		return this->stroke;
	}

	uint8_t GetPositionIndex() {
		return this->currentIndex;
	}

	void SetSize(Vector3D size) {
		this->size = size;
	}

	void SetStroke(uint8_t stroke) {
		this->stroke = stroke;
	}

	void SetPosition(Icon* icon) {
		this->currentIndex = icon->GetIconId();
		this->position.x = (((0.5) * icon->GetSize().x) + icon->GetPosition().x);
		this->position.y = (icon->GetPosition().y - ((0.5) * (icon->GetSize().y)));
	}

	void NextPosition(IconList* icons) {
		uint8_t index = this->currentIndex;
		index++;
		
		if (index <= icons->GetIconCount() && index >= 0) {
			SetPosition(icons->GetAt(index));
		}
	}

	void PrevPosition(IconList* icons) {
		uint8_t index = this->currentIndex;
		index--;

		if (index <= icons->GetIconCount() && index >= 0) {
			SetPosition(icons->GetAt(index));
		}
	}

	void Render() {
		for (uint8_t i = 0; i < this->stroke; i++) {
			u8g2->drawCircle(this->position.x, this->position.y, this->size.z + i, U8G2_DRAW_ALL);
			//u8g2.drawFrame(cursor.GetPosition().x - i, cursor.GetPosition().y - i, cursor.GetSize().x + (2 * i), cursor.GetSize().y + (2 * i));
		}
	}
};
