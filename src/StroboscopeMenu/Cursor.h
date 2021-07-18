#pragma once
#include "Indexer.h"
#include "Vector3D.h"
#include "DebugUtils.h"

enum Style { ROTATING_CUTOUT, TOP_CENTER_CUTOUT, TOP_CUTOUT, FULL_CIRCLE, FULL_SQUARE };

class Cursor : public Indexer {
private:
	U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2 = 0;
	Style style;
public:
	Cursor(U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2) : u8g2(u8g2) {}

	Cursor(U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2, Vector3D size, uint8_t stroke, Style style) : Indexer{size, stroke }, u8g2(u8g2), style(style) {}

	~Cursor() {}

	void SetPositionIndex(Icon* icon) {
		this->currentIndex = icon->GetIconId();
		this->position.x = (((0.5) * icon->GetSize().x) + icon->GetPosition().x);
		this->position.y = (icon->GetPosition().y - ((0.5) * (icon->GetSize().y)));
	}

	void NextPosition(IconList* icons) {
		uint8_t index = this->currentIndex;
		index++;

		/*if (index > icons->GetIconCount() - 1) {
			index = 0;
		}

		Cursor::SetPositionIndex(icons->GetAt(index));*/

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
			switch (this->style) {
			case ROTATING_CUTOUT :
				if (Indexer::GetPosition().x == u8g2->getDisplayWidth() / 2) {
					u8g2->drawCircle(this->position.x, this->position.y, this->size.z + i, U8G2_DRAW_LOWER_LEFT | U8G2_DRAW_LOWER_RIGHT);
				}
				else if (Indexer::GetPosition().x < u8g2->getDisplayWidth() / 2) {
					u8g2->drawCircle(this->position.x, this->position.y, this->size.z + i, U8G2_DRAW_UPPER_LEFT | U8G2_DRAW_LOWER_LEFT | U8G2_DRAW_LOWER_RIGHT);
				}
				else if (Indexer::GetPosition().x > u8g2->getDisplayWidth() / 2) {
					u8g2->drawCircle(this->position.x, this->position.y, this->size.z + i, U8G2_DRAW_UPPER_RIGHT | U8G2_DRAW_LOWER_LEFT | U8G2_DRAW_LOWER_RIGHT);
				}
				else {
					u8g2->drawCircle(this->position.x, this->position.y, this->size.z + i, U8G2_DRAW_ALL);
				}
				break;
			case TOP_CENTER_CUTOUT:
				if (Indexer::GetPosition().x == u8g2->getDisplayWidth() / 2) {
					u8g2->drawCircle(this->position.x, this->position.y, this->size.z + i, U8G2_DRAW_LOWER_LEFT | U8G2_DRAW_LOWER_RIGHT);
				}
				else {
					u8g2->drawCircle(this->position.x, this->position.y, this->size.z + i, U8G2_DRAW_ALL);
				}
				break;
			case TOP_CUTOUT:
				u8g2->drawCircle(this->position.x, this->position.y, this->size.z + i, U8G2_DRAW_LOWER_LEFT | U8G2_DRAW_LOWER_RIGHT);
				break;
			case FULL_CIRCLE:
				u8g2->drawCircle(this->position.x, this->position.y, this->size.z + i, U8G2_DRAW_ALL);
				break;
			case FULL_SQUARE:
				u8g2->drawFrame((this->position.x - (0.5 * this->size.x)) - i, (this->position.y - (0.5 * this->size.y)) - i, this->size.x + (2 * i), this->size.y + (2 * i));
				break;
			default:
				u8g2->drawCircle(this->position.x, this->position.y, this->size.z + i, U8G2_DRAW_ALL);
				break;
			}
		}
	}
};
