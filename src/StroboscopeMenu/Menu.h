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

#include "Action.h"
#include "Icon.h"
#include "SubIcon.h"
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
	bool drawSubIcons = false;
	int8_t menuEvent = 0;
	
	/*################################################--CONFIGURATION PARAMETERS--################################################*/

	uint8_t numIconsPerPage = 3;
	uint8_t numSubIconsPerPage = 1;
	static const uint8_t numIcons = 9; //Must be evenly divisible by 'numIconsPerPage'. add "blank" icons as needed as shown below
	static const uint8_t numStrobeSubIcons = 3;
	static const uint8_t numSubIconLists = 2;
	static const uint8_t numSubPageCursors = 2;

	Vector3D iconSize = Vector3D(32, 32);
	Vector3D pageCursorSize = Vector3D(4, 4); //Radius calculated from square

	Style cursorStyle = TOP_CUTOUT;
	uint8_t cursorStroke = 3;
	uint8_t pageCursorStroke = 1;
	uint8_t pageCursorPadding = 3;
	const uint8_t* textFont = u8g2_font_helvB10_tr;

	//Action data definitions: Provides the arguments for each type of action
	//InputValueData, InterfaceMessageData, SelectionListData-->{{Title, Prefix, Suffix, Value, LowThresh, HighThresh, NumDecimals}, {Title1, Title2, Title3, Buttons}, {Title, List, StartPos}}
	ActionData settingsActionData = { {NULL, NULL, NULL, NULL, NULL, NULL, NULL}, {NULL, NULL, NULL, NULL}, {"Settings", "Screen Timeout\nContrast", 1} };
	ActionData strobeActionData = { {NULL, NULL, NULL, NULL, NULL, NULL, NULL}, {NULL, NULL, NULL, NULL}, {NULL, NULL, NULL} };
	ActionData flashLightActionData = { {NULL, NULL, NULL, NULL, NULL, NULL, NULL}, {NULL, NULL, NULL, NULL}, {"Light State", "ON\nOFF", 1} };
	ActionData blankActionData = { {"Select Voltage", "DAC= ", " V",  &pageCursorPadding, 0, 5, 1}, {NULL, NULL, NULL, NULL}, {NULL, NULL, NULL}};

	//Icon Action definitions: upBtnAction, dwnBtnAction, leftBtnAction, rightBtnAction
	Action settingsAction = Action(Actions::NONE, Actions::SELECTION_LIST, Actions::CURSOR_PREVIOUS, Actions::CURSOR_NEXT, settingsActionData);
	Action strobeAction = Action(Actions::NONE, Actions::JUMP_INTO_SUB_ICONS, Actions::CURSOR_PREVIOUS, Actions::CURSOR_NEXT, strobeActionData);
	Action flashLightAction = Action(Actions::NONE, Actions::INPUT_VALUE, Actions::CURSOR_PREVIOUS, Actions::CURSOR_NEXT, blankActionData);
	Action blankAction = Action(Actions::JUMP_OUTOF_SUB_ICONS, Actions::NONE, Actions::CURSOR_PREVIOUS, Actions::CURSOR_NEXT, blankActionData);
	
	//Icon definitions: Display, Size, GlyphID, Name, Font
	Icon settings = Icon(iconSize, 66, "Settings", u8g2_font_open_iconic_embedded_4x_t, &settingsAction);
	Icon strobe = Icon(iconSize, 67, "Strobe", u8g2_font_open_iconic_embedded_4x_t, &strobeAction);
	Icon flashLight = Icon(iconSize, 77, "Light", u8g2_font_open_iconic_embedded_4x_t, &flashLightAction);

	Icon clock = Icon(iconSize, 65, "Clock", u8g2_font_open_iconic_embedded_4x_t, &blankAction);
	Icon pencil = Icon(iconSize, 69, "Pencil", u8g2_font_open_iconic_embedded_4x_t, &blankAction);
	Icon beat = Icon(iconSize, 70, "Beat", u8g2_font_open_iconic_embedded_4x_t, &blankAction);
	Icon home = Icon(iconSize, 68, "Home", u8g2_font_open_iconic_embedded_4x_t, &blankAction);
	Icon wrench = Icon(iconSize, 72, "Wrench", u8g2_font_open_iconic_embedded_4x_t, &blankAction);
	Icon blank = Icon(iconSize, 0, NULL, NULL, &blankAction);

	//SubIcon definitions: Display, Size, GlyphId, Name, Font
	SubIcon subExternalTrigger = SubIcon(iconSize, 64, "External Trigger", u8g2_font_open_iconic_gui_4x_t, &blankAction);
	SubIcon subFreqControl = SubIcon(iconSize, 70, "Frequency Control", u8g2_font_open_iconic_embedded_4x_t, &blankAction);
	SubIcon subRPMControl = SubIcon(iconSize, 79, "RPM Control", u8g2_font_open_iconic_embedded_4x_t, &blankAction);

	//Icon and SubIcon arrays
	Icon* icons[numIcons] = { &settings, &strobe, &flashLight, &clock, &pencil, &beat, &home, &wrench, &blank };
	SubIcon* strobeSubIcons[numStrobeSubIcons] = { &subExternalTrigger, &subFreqControl, &subRPMControl };

	//Icon and SubIconLists
	IconList mainIconList = IconList(&u8g2, numIcons, numIconsPerPage, icons);
	SubIconList strobeSubIconList = SubIconList(&u8g2, numStrobeSubIcons, numSubIconsPerPage, strobeSubIcons);
	SubIconList* subIconLists[numSubIconLists] = {nullptr, &strobeSubIconList}; //These must be in the order in which they "bind" to thier parent object

	//Cursor definitions: Display, Size, Stroke, Sytle
	Cursor cursor = Cursor(&u8g2, iconSize, cursorStroke, cursorStyle);
	PageCursor mainPageCursor = PageCursor(&u8g2, &mainIconList, pageCursorSize, pageCursorStroke, pageCursorPadding);
	PageCursor strobeSubPageCursor = PageCursor(&u8g2, &strobeSubIconList, pageCursorSize, pageCursorStroke, pageCursorPadding);

	PageCursor* subPageCursors[numSubPageCursors] = {nullptr, &strobeSubPageCursor};

	/*############################################################################################################################*/

	void DrawText();
	void DrawLayout();
	void ProcessMenuEvent(List* list);
	void HandleIconAction(Actions action, ActionData actionData, bool iconType);

public:
	Menu();
	Menu(const unsigned char upBtn, const unsigned char dwnBtn, const unsigned char leftBtn, const unsigned char rightBtn, const unsigned char selectBtn, const unsigned char cancelBtn, bool isInverted);
	~Menu();

	void FirstPage();
	uint8_t NextPage();
	void Draw();
};

#endif //MENU_H
