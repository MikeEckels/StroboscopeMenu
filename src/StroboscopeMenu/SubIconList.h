#ifndef SUB_ICON_LIST_H
#define SUB_ICON_LIST_H

#include <math.h>
#include <stdint.h>
#include <U8g2lib.h>
#include "List.h"

#include "SubIcon.h"
#include "Vector3D.h"
#include "DebugUtils.h"

class SubIconList : public List {
private:
	void SetIconSpacing() override;

public:
	SubIconList(U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2, uint8_t size, uint8_t numIconsPerPage, SubIcon** icons);
	~SubIconList();
};

#endif //SUB_ICON_LIST_H
