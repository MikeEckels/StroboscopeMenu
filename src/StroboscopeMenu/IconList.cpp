#include "IconList.h"

IconList::IconList(U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2, uint8_t size, uint8_t numIconsPerPage, Icon** icons) : List{ u8g2, size, numIconsPerPage, (Element**)icons } {
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
