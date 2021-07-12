#pragma once
#include "Icon.h"

class IconList {
private:
	uint8_t size = 0;
	Icon** icons = 0;

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
};