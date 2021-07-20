#ifndef PAGE_CURSOR_H
#define PAGE_CURSOR_H

#include <stdint.h>
#include <U8g2lib.h>
#include "Indexer.h"

#include "Cursor.h"
#include "IconList.h"
#include "Vector3D.h"
#include "DebugUtils.h"

class PageCursor : public Indexer {
private:
	U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2 = 0;
	IconList* list = 0;
	Indexer** cursors = 0;
	uint8_t cursorCount = 0;
	uint8_t padding = 0;

	void SetSpacing();
	void ClearList();

public:
	PageCursor(U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2, IconList* list, Vector3D size, uint8_t stroke, uint8_t padding);
	~PageCursor();

	void Render(Cursor* cursor);
};

#endif //PAGE_CURSOR_H
