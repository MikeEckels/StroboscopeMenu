#ifndef CURSOR_H
#define CURSOR_H

#include <stdint.h>
#include <U8g2lib.h>
#include "Indexer.h"

#include "Element.h"
#include "List.h"
#include "Vector3D.h"
#include "DebugUtils.h"

//ROTATING_CUTOUT and TOP_CENTER_CUTOUT only work properly with an odd 'numIconsPerPage'
enum Style { ROTATING_CUTOUT, TOP_CENTER_CUTOUT, TOP_CUTOUT, FULL_CIRCLE, FULL_SQUARE };

class Cursor : public Indexer {
private:
	U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2 = 0;
	Style style;

public:
	Cursor(U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2);
	Cursor(U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2, Vector3D size, uint8_t stroke, Style style);
	~Cursor();

	void SetPositionIndex(Element* icon);

	void NextPosition(List* icons);
	void PrevPosition(List* icons);
	void Render();
};

#endif //CURSOR_H
