#include "List.h"

List::List() {}

List::List(U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2, uint8_t size, uint8_t numIconsPerPage, Icon** icons) : u8g2(u8g2), size(size), numIconsPerPage(numIconsPerPage), icons(icons) {}

List::~List() {}

void  List::ShiftForwardsOne() {
	Vector3D firstPos = icons[0]->GetPosition();

	for (uint8_t i = 0; i < this->size - 1; i++) {
		icons[i]->SetPosition(icons[i + 1]->GetPosition());
	}

	icons[this->size - 1]->SetPosition(firstPos);
}

void  List::ShiftBackwardsOne() {
	Vector3D lastPos = icons[this->size - 1]->GetPosition();

	for (uint8_t i = this->size - 1; i > 0; i--) {
		icons[i]->SetPosition(icons[i - 1]->GetPosition());
	}

	icons[0]->SetPosition(lastPos);
}

uint8_t List::GetIconCount() {
	return this->size;
}

uint8_t List::GetIconsPerPage() {
	return this->numIconsPerPage;
}

Icon* List::GetAt(uint8_t index) {

	if (index <= this->size - 1 && index >= 0) {
		return this->icons[index];
	}
	else {
		return 0;
	}
}

void List::ShiftIconsForwards(uint8_t shift) {
	for (uint8_t i = 0; i < shift; i++) {
		List::ShiftForwardsOne();
	}
}

void List::ShiftIconsBackwards(uint8_t shift) {
	for (uint8_t i = 0; i < shift; i++) {
		List::ShiftBackwardsOne();
	}
}
