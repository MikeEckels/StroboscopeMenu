#include "Cursor.h"

Cursor::Cursor(U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2) : u8g2(u8g2) {}

Cursor::Cursor(U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2, Vector3D size, uint8_t stroke, Style style) : Indexer{ size, stroke }, u8g2(u8g2), style(style) {}

Cursor::~Cursor() {}

void Cursor::SetPositionIndex(Icon* icon) {
	this->currentIndex = icon->GetIconId();
	this->position.x = (((0.5) * icon->GetSize().x) + icon->GetPosition().x);
	this->position.y = (icon->GetPosition().y - ((0.5) * (icon->GetSize().y)));
}

void Cursor::NextPosition(IconList* icons) {
	uint8_t index = this->currentIndex;
	index++;

	if (index > icons->GetIconCount() - 1) {
		index = 0;
	}

	Cursor::SetPositionIndex(icons->GetAt(index));

	/*if (index <= icons->GetIconCount() - 1 && index >= 0) {
		Cursor::SetPositionIndex(icons->GetAt(index));
	}*/
}

void Cursor::PrevPosition(IconList* icons) {
	uint8_t index = this->currentIndex;
	/*if (index > 0) {
		index--;
	}*/

	/*if (index <= icons->GetIconCount() - 1) {
		index = icons->GetIconCount() - 1;
	}

	Cursor::SetPositionIndex(icons->GetAt(index));*/

	if (index <= 0) {
		index = icons->GetIconCount() - 1;
	}
	else {
		index--;
	}

	Cursor::SetPositionIndex(icons->GetAt(index));
}

void Cursor::Render() {
	uint16_t cursorXPos = Indexer::GetPosition().x;
	uint16_t displayWidth = u8g2->getDisplayWidth();

	for (uint8_t i = 0; i < this->stroke; i++) {
		switch (this->style) {
		case ROTATING_CUTOUT:
			if (cursorXPos == displayWidth / 2) {
				u8g2->drawCircle(this->position.x, this->position.y, this->size.z + i, U8G2_DRAW_LOWER_LEFT | U8G2_DRAW_LOWER_RIGHT);
			}
			else if (cursorXPos < displayWidth / 2) {
				u8g2->drawCircle(this->position.x, this->position.y, this->size.z + i, U8G2_DRAW_UPPER_LEFT | U8G2_DRAW_LOWER_LEFT | U8G2_DRAW_LOWER_RIGHT);
			}
			else if (cursorXPos > displayWidth / 2) {
				u8g2->drawCircle(this->position.x, this->position.y, this->size.z + i, U8G2_DRAW_UPPER_RIGHT | U8G2_DRAW_LOWER_LEFT | U8G2_DRAW_LOWER_RIGHT);
			}
			else {
				u8g2->drawCircle(this->position.x, this->position.y, this->size.z + i, U8G2_DRAW_ALL);
			}
			break;
		case TOP_CENTER_CUTOUT:
			if (cursorXPos == displayWidth / 2) {
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