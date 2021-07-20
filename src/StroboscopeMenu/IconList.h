#ifndef ICON_LIST_H
#define ICON_LIST_H

#include <stdint.h>
#include <U8g2lib.h>

#include "Icon.h"
#include "Vector3D.h"
#include "DebugUtils.h"

class IconList {
private:
	U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2 = 0;
	uint8_t size = 0;
	uint8_t numIconsPerPage = 0;
	Icon** icons = 0;

	void SetIconSpacing();
	void ShiftLeftOne();
	void ShiftRightOne();

public:
	IconList(U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2, uint8_t size, uint8_t numIconsPerPage, Icon** icons);
	~IconList();

	uint8_t GetIconCount();
	uint8_t GetIconsPerPage();
	Icon* GetAt(uint8_t index);

	void ShiftIconsLeft(uint8_t shift);
	void ShiftIconsRight(uint8_t shift);
};

#endif //ICON_LIST_H