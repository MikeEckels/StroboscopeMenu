#ifndef SUB_PAGE_CURSOR_H
#define SUB_PAGE_CURSOR_H
#include <math.h>
#include <stdint.h>
#include <U8g2lib.h>
#include "PageCursor.h"

#include "List.h"
#include "Vector3D.h"
#include "DebugUtils.h"

class SubPageCursor : public PageCursor {
private:
	void SetSpacing() override;

public:
	SubPageCursor(U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2, List* list, Vector3D size, uint8_t stroke, uint8_t padding);
	~SubPageCursor();

};

#endif //SUB_PAGE_CURSOR_H
