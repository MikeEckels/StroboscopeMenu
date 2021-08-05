#ifndef ICON_LIST_H
#define ICON_LIST_H

#include <math.h>
#include <stdint.h>
#include <U8g2lib.h>
#include "List.h"

#include "Icon.h"
#include "Vector3D.h"

class IconList : public List {
private:
	void SetIconSpacing() override;

public:
	IconList(U8G2_SH1106_128X64_NONAME_2_HW_I2C* u8g2, uint8_t size, uint8_t numIconsPerPage, Icon** icons);
	~IconList();
};

#endif //ICON_LIST_H
