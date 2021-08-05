#ifndef MENU_H
#define MENU_H

#include <stdint.h>
#include <U8g2lib.h>
#include "Arduino.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#include "Icon.h"
#include "IconList.h"
#include "SubIconList.h"
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
	
	/*################################################--CONFIGURATION PARAMETERS--################################################*/

	uint8_t numIconsPerPage = 3;
	uint8_t numSubIconsPerPage = 1;
	static const uint8_t numIcons = 9; //Must be evenly divisible by 'numIconsPerPage'. add "blank" icons as needed as shown below
	static const uint8_t numSettingsSubIcons = 3;

	Vector3D iconSize = Vector3D(32, 32);
	Vector3D pageCursorSize = Vector3D(4, 4); //Radius calculated from square

	Style cursorStyle = TOP_CUTOUT;
	uint8_t cursorStroke = 3;
	uint8_t pageCursorStroke = 1;
	uint8_t pageCursorPadding = 3;
	const uint8_t* textFont = u8g2_font_helvB10_tr;
	
	//Icon definitions: Display, Size, GlyphID, Name, Font
	Icon settings = Icon(iconSize, 66, "Settings", u8g2_font_open_iconic_embedded_4x_t);
	Icon strobe = Icon(iconSize, 67, "Strobe", u8g2_font_open_iconic_embedded_4x_t);
	Icon flashLight = Icon(iconSize, 77, "Light", u8g2_font_open_iconic_embedded_4x_t);

	Icon clock = Icon(iconSize, 65, "Clock", u8g2_font_open_iconic_embedded_4x_t);
	Icon pencil = Icon(iconSize, 69, "Pencil", u8g2_font_open_iconic_embedded_4x_t);
	Icon beat = Icon(iconSize, 70, "Beat", u8g2_font_open_iconic_embedded_4x_t);
	Icon home = Icon(iconSize, 68, "Home", u8g2_font_open_iconic_embedded_4x_t);
	Icon wrench = Icon(iconSize, 72, "Wrench", u8g2_font_open_iconic_embedded_4x_t);
	Icon blank = Icon(iconSize, 0, NULL, NULL);

	Icon subExternalTrigger = Icon(iconSize, 64, "External Trigger", u8g2_font_open_iconic_gui_4x_t);
	Icon subFreqControl = Icon(iconSize, 70, "Frequency Control", u8g2_font_open_iconic_embedded_4x_t);
	Icon subRPMControl = Icon(iconSize, 79, "RPM Control", u8g2_font_open_iconic_embedded_4x_t);

	Icon* icons[numIcons] = { &settings, &strobe, &flashLight, &clock, &pencil, &beat, &home, &wrench, &blank };
	Icon* settingsSubIcons[numSettingsSubIcons] = { &subExternalTrigger, &subFreqControl, &subRPMControl };

	IconList mainIconList = IconList(&u8g2, numIcons, numIconsPerPage, icons);
	SubIconList settingsSubIconList = SubIconList(&u8g2, numSettingsSubIcons, numSubIconsPerPage, settingsSubIcons);
	Cursor cursor = Cursor(&u8g2, iconSize, cursorStroke, cursorStyle);
	PageCursor mainPageCursor = PageCursor(&u8g2, &mainIconList, pageCursorSize, pageCursorStroke, pageCursorPadding);
	PageCursor settingsSubPageCursor = PageCursor(&u8g2, &settingsSubIconList, pageCursorSize, pageCursorStroke, pageCursorPadding);

	/*############################################################################################################################*/

	void DrawText();
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

#endif //MENU_H
