#ifndef LIST_H
#define LIST_H

#include <stdint.h>
#include <U8g2lib.h>

#include "Icon.h"
#include "Vector3D.h"

class List {
protected:
	U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2 = 0;
	uint8_t size = 0;
	uint8_t numIconsPerPage = 0;
	Icon** icons = 0;

	List();
	List(U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2, uint8_t size, uint8_t numIconsPerPage, Icon** icons);

	virtual void SetIconSpacing() = 0;
	void ShiftForwardsOne();
	void ShiftBackwardsOne();

public:
	virtual ~List();
	
	uint8_t GetIconCount();
	uint8_t GetIconsPerPage();
	Icon* GetAt(uint8_t index);

	void ShiftIconsForwards(uint8_t shift);
	void ShiftIconsBackwards(uint8_t shift);
};

#endif //LIST_H
