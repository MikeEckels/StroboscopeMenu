#pragma once
#include <stdint.h>
#include "Arduino.h"

#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#include "Icon.h"
#include "IconList.h"
#include "Vector3D.h"
#include "Cursor.h"
#include "PageCursor.h"
#include "DebugUtils.h"

class Menu {
private:

	Menu(const Menu&) = delete;
	Menu& operator = (const Menu&) = delete;

	U8G2_SH1106_128X64_NONAME_2_HW_I2C u8g2 = U8G2_SH1106_128X64_NONAME_2_HW_I2C(U8G2_R2, U8X8_PIN_NONE);

	unsigned char upBtn = U8X8_PIN_NONE;
	unsigned char dwnBtn = U8X8_PIN_NONE;
	unsigned char leftBtn = U8X8_PIN_NONE;
	unsigned char rightBtn = U8X8_PIN_NONE;
	unsigned char selectBtn = U8X8_PIN_NONE;
	unsigned char cancelBtn = U8X8_PIN_NONE;
	bool isInverted = false;
	int8_t menuEvent = 0;
	
	/*####################--CONFIGURATION PARAMETERS--####################*/

	uint8_t numIconsPerPage = 3; //NEED TO UPDATE TO USE THIS WHEN AUTO SPACING
	static const uint8_t numIcons = 3;

	Vector3D iconSize = Vector3D(32, 32, 8);  //X, Y, Padding
	Vector3D pageCursorSize = Vector3D(4, 4); //Radius calculated from square

	uint8_t cursorStroke = 3;
	uint8_t pageCursorStroke = 1;
	uint8_t pageCursorPadding = 3;
	const uint8_t* textFont = u8g2_font_helvB10_tr;
	
	//Icon definitions: Display, Size, GlyphID, Name, Font
	
	Icon strobe = Icon(&u8g2, iconSize, 67, "Strobe", u8g2_font_open_iconic_embedded_4x_t);
	Icon settings = Icon(&u8g2, iconSize, 66, "Settings", u8g2_font_open_iconic_embedded_4x_t);
	Icon flashLight = Icon(&u8g2, iconSize, 77, "Light", u8g2_font_open_iconic_embedded_4x_t);
	/*Icon clock = Icon(&u8g2, iconSize, 65, "Clock", u8g2_font_open_iconic_embedded_4x_t);
	Icon gear = Icon(&u8g2, iconSize, 66, "Gear", u8g2_font_open_iconic_embedded_4x_t);
	Icon light = Icon(&u8g2, iconSize, 67, "Light", u8g2_font_open_iconic_embedded_4x_t);
	Icon home = Icon(&u8g2, iconSize, 68, "Home", u8g2_font_open_iconic_embedded_4x_t);
	Icon settings = Icon(&u8g2, iconSize, 72, "Settings", u8g2_font_open_iconic_embedded_4x_t);*/

	Icon* icons[numIcons] = {&strobe, &settings, &flashLight};

	/*####################################################################*/

	IconList list = IconList(numIcons, icons);
	Cursor cursor = Cursor(&u8g2, iconSize, cursorStroke);
	PageCursor pageCursor = PageCursor(&u8g2, &list, pageCursorSize, pageCursorStroke, pageCursorPadding);

	void DrawLayout();
	void ProcessMenuEvent();

public:
	Menu();
	Menu(const unsigned char upBtn, const unsigned char dwnBtn, const unsigned char leftBtn, const unsigned char rightBtn, const unsigned char selectBtn, const unsigned char cancelBtn, bool isInverted);
	~Menu();

	void FirstPage();
	uint8_t NextPage();
	void Draw();
};
