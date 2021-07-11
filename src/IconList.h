#pragma once
#include "Icon.h"
#include "Vector3D.h"

class IconList {
private:
	Vector3D size = { 0, 0 };
	Icon** icons = 0;
	uint8_t iconCount = 0;

	void ClearList() {
		for (uint8_t i = 0; i < this->size.x-1; i++) {
			delete this->icons[i];
		}
	}

public:
	IconList(Vector3D size) : size(size) {
		this->iconCount = 0;
		this->icons = new Icon*[size.x];
	}

	~IconList() {
		ClearList();
		delete icons;
	}

	Vector3D GetSize() {
		return this->size;
	}

	uint8_t GetIconCount() {
		return this->iconCount;
	}

	Icon* GetAt(uint8_t index) {

		if (index <= this->iconCount && index >= 0) {
			return this->icons[index];
		}
		else {
			return 0;
		}
	}

	void AddIcon(Icon* icon) {
		this->icons[this->iconCount] = icon;
		this->iconCount++;
	}
};