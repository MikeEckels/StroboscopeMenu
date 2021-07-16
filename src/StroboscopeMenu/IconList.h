#pragma once
#include "Icon.h"
#include "DebugUtils.h"

class IconList {
private:
	uint8_t size = 0;
	Icon** icons = 0;

	void ShiftLeftOne() {
		Vector3D firstPos = icons[0]->GetPosition();

		for (uint8_t i = 0; i < this->size - 1; i++) {
			icons[i]->SetPosition(icons[i + 1]->GetPosition());
		}

		icons[this->size - 1]->SetPosition(firstPos);
	}

	void ShiftRightOne() {
		Vector3D lastPos = icons[this->size - 1]->GetPosition();

		for (uint8_t i = this->size - 1; i > 0; i--) {
			icons[i]->SetPosition(icons[i - 1]->GetPosition());
		}

		icons[0]->SetPosition(lastPos);
	}

public:
	IconList(uint8_t size, Icon** icons) : size(size), icons(icons) {}

	~IconList() {}

	uint8_t GetIconCount() {
		return this->size;
	}

	Icon* GetAt(uint8_t index) {

		if (index <= this->size && index >= 0) {
			return this->icons[index];
		}
		else {
			return 0;
		}
	}

	void ShiftIconsLeft(uint8_t shift) {
		for (uint8_t i = 0; i < shift; i++) {
			IconList::ShiftLeftOne();
		}
	}

	void ShiftIconsRight(uint8_t shift) {
		for (uint8_t i = 0; i < shift; i++) {
			IconList::ShiftRightOne();
		}
	}
};