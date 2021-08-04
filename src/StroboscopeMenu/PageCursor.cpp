#include "PageCursor.h"

PageCursor::PageCursor(U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2, IconList* list, Vector3D size, uint8_t stroke, uint8_t padding) : Indexer{ size, stroke }, u8g2(u8g2), list(list), padding(padding) {
	this->cursorCount = ceil((float)list->GetIconCount() / list->GetIconsPerPage());
	this->cursors = new Indexer * [this->cursorCount];

	for (uint8_t i = 0; i < this->cursorCount; i++) {
		this->cursors[i] = new Indexer(size, stroke);
	}

	PageCursor::SetSpacing();
}

PageCursor::~PageCursor() {
	PageCursor::ClearList();
	delete cursors;
}

void PageCursor::SetSpacing() {
	Vector3D position;

	static uint8_t x;
	uint8_t y = (uint8_t)(u8g2->getDisplayHeight() - (cursors[0]->GetSize().z + cursors[0]->GetStroke()));

	if (this->cursorCount % 2) { //Odd number of cursors
		x = (uint8_t)(floor(-0.5 * this->cursorCount * (this->padding + cursors[0]->GetStroke()) - this->cursorCount * cursors[0]->GetSize().z + 0.5 * (this->padding + cursors[0]->GetStroke())) + cursors[0]->GetSize().z + 0.5 * u8g2->getDisplayWidth());
	}
	else { //Even number of cursors
		x = (uint8_t)((0.5 * u8g2->getDisplayWidth()) - (floor(0.5 * (this->cursorCount - 1)) * (2 * cursors[0]->GetSize().z)) - (floor(0.5 * (this->cursorCount - 1)) * (this->padding + cursors[0]->GetStroke())) - (0.5 * (this->padding + cursors[0]->GetStroke())) - cursors[0]->GetSize().z);
	}

	for (uint8_t i = 0; i < this->cursorCount; i++) {
		position = { x, y };
		x += (this->padding + cursors[i]->GetStroke() + (2 * cursors[i]->GetSize().z));
		cursors[i]->SetPosition(position);
	}
}

void PageCursor::ClearList() {
	for (uint8_t i = 0; i < this->cursorCount; i++) {
		delete this->cursors[i];
	}
}

void PageCursor::Render(Cursor* cursor) {
	//static uint8_t oldIndex;
	uint8_t cursorIndex = cursor->GetPositionIndex();
	uint8_t previousCursorIndex = cursor->GetPreviousPositionIndex();

	//DEBUG_PRINT_NOTICE(cursorIndex);
	//DEBUG_PRINT_NOTICE(previousCursorIndex);

	if ((cursorIndex != previousCursorIndex)) {
		//DEBUG_PRINTLN("RAN");
		this->currentIndex = floor(cursorIndex / this->list->GetIconsPerPage());
	}

	for (uint8_t i = 0; i < this->cursorCount; i++) {
		for (uint8_t j = 0; j < this->stroke; j++) {
			if (i == this->currentIndex) {
				this->previousIndex = this->currentIndex;
				u8g2->drawDisc(cursors[i]->GetPosition().x, cursors[i]->GetPosition().y, cursors[i]->GetSize().z + j, U8G2_DRAW_ALL);
			}
			else {
				u8g2->drawCircle(cursors[i]->GetPosition().x, cursors[i]->GetPosition().y, cursors[i]->GetSize().z + j, U8G2_DRAW_ALL);
			}
		}
	}

	//oldIndex = cursorIndex;
}