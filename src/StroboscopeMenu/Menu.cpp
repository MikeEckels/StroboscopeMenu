#include "Menu.h"

int8_t Icon::currentIconId = -1;

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

	cursor.SetPosition(list.GetAt(0));
}

Menu::Menu(const unsigned char upBtn, const unsigned char dwnBtn, const unsigned char leftBtn, const unsigned char rightBtn, const unsigned char selectBtn, const unsigned char cancelBtn, bool isInverted) 
	: upBtn(upBtn), dwnBtn(dwnBtn), leftBtn(leftBtn), rightBtn(rightBtn), selectBtn(selectBtn), cancelBtn(cancelBtn), isInverted(isInverted) {

	u8g2.begin(this->selectBtn, this->rightBtn, this->leftBtn, this->upBtn, this->dwnBtn, this->cancelBtn, this->isInverted);
	u8g2.setFlipMode(1);

	cursor.SetPosition(list.GetAt(0));
}

Menu::~Menu() = default;

void Menu::FirstPage() {
	u8g2.firstPage();
}

uint8_t Menu::NextPage() {
	return u8g2.nextPage();
}

void Menu::DrawLayout() {
	for (uint8_t i = 0; i < 7; i++) {
		for (uint8_t j = 0; j < 3; j++) {
			u8g2.drawFrame(16 * i, 16 * j, 32, 32);;
		}
	}
}

void Menu::ProcessMenuEvent() {
	if (this->menuEvent == 0) {
		this->menuEvent = u8g2.getMenuEvent();

		switch (this->menuEvent) {
		case U8X8_MSG_GPIO_MENU_UP:

			break;
		case  U8X8_MSG_GPIO_MENU_DOWN:

			break;
		case  U8X8_MSG_GPIO_MENU_NEXT:
			cursor.NextPosition(&list);
			break;
		case  U8X8_MSG_GPIO_MENU_PREV:
			cursor.PrevPosition(&list);
			break;
		case  U8X8_MSG_GPIO_MENU_SELECT:

			break;
		case  U8X8_MSG_GPIO_MENU_HOME:

			break;
		default:
			
			break;
		}
		this->menuEvent = 0;
	}
}

void Menu::Draw() {
	uint8_t i = 0;
	
	while (i < list.GetIconCount()) {
		if (Icon* currentIcon =list.GetAt(i)) {
			u8g2.setFont(currentIcon->GetFont());
			u8g2.drawGlyph(currentIcon->GetPosition().x, currentIcon->GetPosition().y, currentIcon->GetGlyphId());
			//DrawLayout();
			i++;
		}
	}
	ProcessMenuEvent();
	cursor.Render();
	pageCursor.Render();
}