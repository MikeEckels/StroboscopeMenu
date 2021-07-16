#pragma once
#include "Indexer.h"
#include "Vector3D.h"
#include "DebugUtils.h"

class Cursor : public Indexer {
private:
	U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2 = 0;

public:
	Cursor(U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2) : u8g2(u8g2) {}

	Cursor(U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2, Vector3D size, uint8_t stroke) : Indexer{size, stroke }, u8g2(u8g2) {}

	~Cursor() {}

	void SetPositionIndex(Icon* icon) {
		this->currentIndex = icon->GetIconId();
		this->position.x = (((0.5) * icon->GetSize().x) + icon->GetPosition().x);
		this->position.y = (icon->GetPosition().y - ((0.5) * (icon->GetSize().y)));
	}

	void NextPosition(IconList* icons) {
		uint8_t index = this->currentIndex;
		index++;

		if (index <= icons->GetIconCount() - 1 && index >= 0) {
			Cursor::SetPositionIndex(icons->GetAt(index));
		}
	}

	void PrevPosition(IconList* icons) {
		uint8_t index = this->currentIndex;
		index--;

		if (index <= icons->GetIconCount() - 1 && index >= 0) {
			Cursor::SetPositionIndex(icons->GetAt(index));
		}
	}

	void Render() {
		for (uint8_t i = 0; i < this->stroke; i++) {
			if (GetPosition().x == u8g2->getDisplayWidth() / 2) {
				u8g2->drawCircle(this->position.x, this->position.y, this->size.z + i, 12);
			}
			else {
				u8g2->drawCircle(this->position.x, this->position.y, this->size.z + i, 15);
			}
		}
	}
};
