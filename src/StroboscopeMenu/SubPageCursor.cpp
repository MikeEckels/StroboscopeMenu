#include "SubPageCursor.h"

SubPageCursor::SubPageCursor(U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2, List* list, Vector3D size, uint8_t stroke, uint8_t padding) : PageCursor{ u8g2, list, size, stroke, padding } {
	SubPageCursor::SetSpacing();
}

SubPageCursor::~SubPageCursor() {}

void SubPageCursor::SetSpacing() {
	Vector3D position;

	/*static uint8_t x;
	uint8_t y = (uint8_t)(u8g2->getDisplayHeight() - (cursors[0]->GetSize().z + cursors[0]->GetStroke()));*/

	uint8_t x = (uint8_t)(u8g2->getDisplayWidth() - (cursors[0]->GetSize().z + cursors[0]->GetStroke()));
	static uint8_t y;

	if (this->cursorCount % 2) { //Odd number of cursors
		y = (uint8_t)(floor(-0.5 * this->cursorCount * (this->padding + cursors[0]->GetStroke()) - this->cursorCount * cursors[0]->GetSize().z + 0.5 * (this->padding + cursors[0]->GetStroke())) + cursors[0]->GetSize().z + 0.5 * u8g2->getDisplayHeight());
	}
	else { //Even number of cursors
		y = (uint8_t)((0.5 * u8g2->getDisplayHeight()) - (floor(0.5 * (this->cursorCount - 1)) * (2 * cursors[0]->GetSize().z)) - (floor(0.5 * (this->cursorCount - 1)) * (this->padding + cursors[0]->GetStroke())) - (0.5 * (this->padding + cursors[0]->GetStroke())) - cursors[0]->GetSize().z);
	}

	for (uint8_t i = 0; i < this->cursorCount; i++) {
		position = { x, y };
		y += (this->padding + cursors[i]->GetStroke() + (2 * cursors[i]->GetSize().z));
		cursors[i]->SetPosition(position);
	}
}