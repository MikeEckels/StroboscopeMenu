#pragma once
#include "Indexer.h"
#include "Vector3D.h"
#include <math.h>
#include "DebugUtils.h"

class PageCursor : public Indexer {
private:
	U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2 = 0;
	IconList* list = 0;
	Indexer** cursors = 0;
	uint8_t cursorCount = 0;

	void SetSpacing() {
		for (uint8_t i = 0; i < this->cursorCount; i++) {
			static uint8_t x = (uint8_t)(((u8g2->getDisplayWidth() / (uint8_t)2)) - (cursors[i]->GetSize().z + cursors[i]->GetStroke()));
			x += ((2*i)*(cursors[i]->GetSize().z + cursors[i]->GetStroke()));
			Vector3D position = { x, (uint8_t)(u8g2->getDisplayHeight() - (cursors[i]->GetSize().z + cursors[i]->GetStroke()))};
			cursors[i]->SetPosition(position);
		}
	}

	void ClearList() {
		for (uint8_t i = 0; i < this->cursorCount; i++) {
			delete this->cursors[i];
		}
	}

public:
	PageCursor(U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2, IconList* list, Vector3D size, uint8_t stroke) : Indexer{size, stroke }, u8g2(u8g2), list(list) {
		this->cursorCount = ceil((float)list->GetIconCount() / 3.0f);
		this->cursors = new Indexer*[this->cursorCount];

		for (uint8_t i = 0; i < this->cursorCount; i++) {
			this->cursors[i] = new Indexer(size, stroke);
		}

		SetSpacing();
	}

	~PageCursor() {
		ClearList();
		delete cursors;
	}

	/*void SetPosition() {
		this->currentIndex = icon->GetIconId();
		this->position.x = (((0.5) * icon->GetSize().x) + icon->GetPosition().x);
		this->position.y = (icon->GetPosition().y - ((0.5) * (icon->GetSize().y)));
	}

	void NextPosition() {
		uint8_t index = this->currentIndex;
		index++;

		if (index <= icons->GetIconCount() - 1 && index >= 0) {
			SetPosition(icons->GetAt(index));
		}
	}

	void PrevPosition() {
		uint8_t index = this->currentIndex;
		index--;

		if (index <= icons->GetIconCount() - 1 && index >= 0) {
			SetPosition(icons->GetAt(index));
		}
	}*/

	void Render() {
		for (uint8_t i = 0; i < this->cursorCount; i++) {
			for (uint8_t j = 0; j < this->stroke; j++) {
				u8g2->drawCircle(cursors[i]->GetPosition().x, cursors[i]->GetPosition().y, cursors[i]->GetSize().z + j, U8G2_DRAW_ALL);
			}
		}
	}
};
