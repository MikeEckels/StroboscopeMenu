#include "Menu.h"

int8_t Element::currentId = -1;

Menu:: Menu() {
	this->upBtn = 3;
	this->dwnBtn = 4;
	this->leftBtn = 1;
	this->rightBtn = 2;
	this->selectBtn = U8X8_PIN_NONE;
	this->cancelBtn = U8X8_PIN_NONE;
	this->isInverted = true;

	u8g2.begin(this->selectBtn, this->rightBtn, this->leftBtn, this->upBtn, this->dwnBtn, this->cancelBtn, this->isInverted);
	u8g2.setFlipMode(1);

	cursor.SetPositionIndex(mainIconList.GetAt(0));
}

Menu::Menu(const unsigned char upBtn, const unsigned char dwnBtn, const unsigned char leftBtn, const unsigned char rightBtn, const unsigned char selectBtn, const unsigned char cancelBtn, bool isInverted) 
	: upBtn(upBtn), dwnBtn(dwnBtn), leftBtn(leftBtn), rightBtn(rightBtn), selectBtn(selectBtn), cancelBtn(cancelBtn), isInverted(isInverted) {

	u8g2.begin(this->selectBtn, this->rightBtn, this->leftBtn, this->upBtn, this->dwnBtn, this->cancelBtn, this->isInverted);
	u8g2.setFlipMode(1);

	cursor.SetPositionIndex(mainIconList.GetAt(0));
}

Menu::~Menu() = default;

void Menu::FirstPage() {
	u8g2.firstPage();
}

uint8_t Menu::NextPage() {
	return u8g2.nextPage();
}

void Menu::DrawText() {
	Element* currentIcon = mainIconList.GetAt(cursor.GetPositionIndex());

	if (currentIcon && currentIcon->GetName() && currentIcon->GetFont()) {
		u8g2.setFont(this->textFont);
		u8g2.setCursor((u8g2.getDisplayWidth() - u8g2.getStrWidth(currentIcon->GetName())) / 2, u8g2.getFontAscent());
		u8g2.print(currentIcon->GetName());
	}
}

void Menu::DrawLayout() {
	for (uint8_t i = 0; i < 7; i++) {
		for (uint8_t j = 0; j < 3; j++) {
			u8g2.drawFrame(16 * i, 16 * j, 32, 32);;
		}
	}
}

void Menu::ProcessMenuEvent(List* list) {
	if (this->menuEvent == 0) {
		this->menuEvent = u8g2.getMenuEvent();
		Action* iconAction = list->GetAt(cursor.GetPositionIndex())->GetAction();
		bool iconType = list->GetAt(cursor.GetPositionIndex())->GetType();

		switch (this->menuEvent) {
		case U8X8_MSG_GPIO_MENU_UP:
			Menu::HandleIconAction(iconAction->upAction, iconAction->actionData, iconType);
			DEBUG_PRINTLN("UP");
			break;
		case  U8X8_MSG_GPIO_MENU_DOWN:
			Menu::HandleIconAction(iconAction->downAction, iconAction->actionData, iconType);
			DEBUG_PRINTLN("DOWN");
			break;
		case  U8X8_MSG_GPIO_MENU_NEXT:
			Menu::HandleIconAction(iconAction->rightAction, iconAction->actionData, iconType);
			DEBUG_PRINTLN("NEXT");
			//cursor.NextPosition(&mainIconList);
			break;
		case  U8X8_MSG_GPIO_MENU_PREV:
			Menu::HandleIconAction(iconAction->leftAction, iconAction->actionData, iconType);
			DEBUG_PRINTLN("PREV");
			//cursor.PrevPosition(&mainIconList);
			break;
		case  U8X8_MSG_GPIO_MENU_SELECT:
			DEBUG_PRINTLN("SELECT");
			break;
		case  U8X8_MSG_GPIO_MENU_HOME:
			DEBUG_PRINTLN("HOME");
			break;
		default:

			break;
		}
		this->menuEvent = 0;
	}
}

void Menu::HandleIconAction(Actions action, ActionData actionData, bool iconType) {

	switch (action) {
	case Actions::NONE:
			//Do Nothing
		DEBUG_PRINT_NOTICE("NONE");
		break;
	case Actions::JUMP_OUTOF_SUB_ICONS:
		drawSubIcons = false;
		DEBUG_PRINT_NOTICE("JUMPOUT");
		break;
	case Actions::JUMP_INTO_SUB_ICONS:
		drawSubIcons = true;
		DEBUG_PRINT_NOTICE("JUMPIN");
		break;
	case Actions::CURSOR_NEXT:
		if (iconType) {
			cursor.NextPosition(subIconLists[cursor.GetPositionIndex()]);
			DEBUG_PRINT_NOTICE("NEXTSUB");
		}
		else {
			cursor.NextPosition(&mainIconList);
			DEBUG_PRINT_NOTICE("NEXTMAIN");
		}
		break;
	case Actions::CURSOR_PREVIOUS:
		if (iconType) {
			cursor.PrevPosition(subIconLists[cursor.GetPositionIndex()]);
			DEBUG_PRINT_NOTICE("PREVSUB");
		}
		else {
			cursor.PrevPosition(&mainIconList);
			DEBUG_PRINT_NOTICE("PREVMAIN");
		}
		break;
	case Actions::SELECTION_LIST:
		DEBUG_PRINT_NOTICE("LIST");
		u8g2.setMenuNextPin(U8X8_PIN_NONE);
		u8g2.setMenuPrevPin(U8X8_PIN_NONE);
		u8g2.setMenuHomePin(Menu::leftBtn);
		u8g2.setMenuSelectPin(Menu::rightBtn);
		u8g2.userInterfaceSelectionList(actionData.selectionList.title, actionData.selectionList.startPosition, actionData.selectionList.optionsList);
		u8g2.setMenuSelectPin(U8X8_PIN_NONE);
		u8g2.setMenuHomePin(U8X8_PIN_NONE);
		u8g2.setMenuPrevPin(Menu::leftBtn);
		u8g2.setMenuNextPin(Menu::rightBtn);
		break;
	case Actions::USER_INTERFACE_MESSAGE:
		DEBUG_PRINT_NOTICE("MESSAGE");
		u8g2.setMenuUpPin(U8X8_PIN_NONE);
		u8g2.setMenuDownPin(U8X8_PIN_NONE);
		u8g2.setMenuHomePin(Menu::upBtn);
		u8g2.setMenuSelectPin(Menu::dwnBtn);
		u8g2.userInterfaceMessage(actionData.interfaceMessage.title1, actionData.interfaceMessage.title2, actionData.interfaceMessage.title3, actionData.interfaceMessage.buttons);
		u8g2.setMenuSelectPin(U8X8_PIN_NONE);
		u8g2.setMenuHomePin(U8X8_PIN_NONE);
		u8g2.setMenuUpPin(Menu::upBtn);
		u8g2.setMenuDownPin(Menu::dwnBtn);
		break;
	case Actions::INPUT_VALUE:
		DEBUG_PRINT_NOTICE("INPUT");
		u8g2.setMenuNextPin(U8X8_PIN_NONE);
		u8g2.setMenuPrevPin(U8X8_PIN_NONE);
		u8g2.setMenuHomePin(Menu::leftBtn);
		u8g2.setMenuSelectPin(Menu::rightBtn);
		u8g2.userInterfaceInputValue(actionData.inputValue.title, actionData.inputValue.prefix, actionData.inputValue.value, actionData.inputValue.lowThresh, actionData.inputValue.highThresh, actionData.inputValue.decimalPlaces, actionData.inputValue.suffix);
		u8g2.setMenuSelectPin(U8X8_PIN_NONE);
		u8g2.setMenuHomePin(U8X8_PIN_NONE);
		u8g2.setMenuPrevPin(Menu::leftBtn);
		u8g2.setMenuNextPin(Menu::rightBtn);
		break;
	default:
		DEBUG_PRINT_ERR("Action not supported");
		break;
	}
}

void Menu::Draw() {
	uint8_t i = 0;
	List* list;
	PageCursor* pageCursor;

	if (!drawSubIcons) {
		list = &mainIconList;
		pageCursor = &mainPageCursor;
	}
	else {
		list = subIconLists[cursor.GetPositionIndex()];
		pageCursor = subPageCursors[cursor.GetPositionIndex()];
	}

	while (i < list->GetIconCount()) {
		Element* currentIcon = list->GetAt(i);

		if (currentIcon && currentIcon->GetName() && currentIcon->GetFont()) {
			u8g2.setFont(currentIcon->GetFont());
			u8g2.drawGlyph(currentIcon->GetPosition().x, currentIcon->GetPosition().y, currentIcon->GetGlyphId());
			Menu::DrawText();
			//Menu::DrawLayout();
		}
		i++;
	}
	Menu::ProcessMenuEvent(list);

	cursor.Render();
	pageCursor->Render(&cursor);
}
