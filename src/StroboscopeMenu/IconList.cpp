#include "IconList.h"

IconList::IconList(U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2, uint8_t size, uint8_t numIconsPerPage, Icon** icons) : u8g2(u8g2), size(size), numIconsPerPage(numIconsPerPage), icons(icons) {
	IconList::SetIconSpacing();
}

IconList::~IconList() {}

void IconList::SetIconSpacing() {
	Vector3D position;

	uint16_t y = ((0.5) * (u8g2->getDisplayHeight() + icons[0]->GetSize().y));
	uint16_t z = (uint16_t)(floor(u8g2->getDisplayWidth() - (this->numIconsPerPage * icons[0]->GetSize().x)) / (this->numIconsPerPage + 1)); //Spacing between icons
	static uint16_t x = z;

	for (uint8_t i = 0; i < this->size; i++) {
		position = { x, y, z };
		x += position.z + icons[i]->GetSize().x;
		icons[i]->SetPosition(position);
	}
}

void  IconList::ShiftLeftOne() {
	Vector3D firstPos = icons[0]->GetPosition();

	for (uint8_t i = 0; i < this->size - 1; i++) {
		icons[i]->SetPosition(icons[i + 1]->GetPosition());
	}

	icons[this->size - 1]->SetPosition(firstPos);
}

void  IconList::ShiftRightOne() {
	Vector3D lastPos = icons[this->size - 1]->GetPosition();

	for (uint8_t i = this->size - 1; i > 0; i--) {
		icons[i]->SetPosition(icons[i - 1]->GetPosition());
	}

	icons[0]->SetPosition(lastPos);
}

uint8_t IconList::GetIconCount() {
	return this->size;
}

uint8_t IconList::GetIconsPerPage() {
	return this->numIconsPerPage;
}

Icon* IconList::GetAt(uint8_t index) {

	if (index <= this->size && index >= 0) {
		return this->icons[index];
	}
	else {
		return 0;
	}
}

void IconList::ShiftIconsLeft(uint8_t shift) {
	for (uint8_t i = 0; i < shift; i++) {
		IconList::ShiftLeftOne();
	}
}

void IconList::ShiftIconsRight(uint8_t shift) {
	for (uint8_t i = 0; i < shift; i++) {
		IconList::ShiftRightOne();
	}
}