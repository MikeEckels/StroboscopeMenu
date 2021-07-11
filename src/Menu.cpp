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
}

Menu::Menu(const unsigned char upBtn, const unsigned char dwnBtn, const unsigned char leftBtn, const unsigned char rightBtn, const unsigned char selectBtn, const unsigned char cancelBtn, bool isInverted) 
	: upBtn(upBtn), dwnBtn(dwnBtn), leftBtn(leftBtn), rightBtn(rightBtn), selectBtn(selectBtn), cancelBtn(cancelBtn), isInverted(isInverted) {}

Menu::~Menu() = default;

void Menu::Initialize() {
	u8g2.begin(this->selectBtn, this->rightBtn, this->leftBtn, this->upBtn, this->dwnBtn, this->cancelBtn, this->isInverted);
	u8g2.setFlipMode(1);

	list.AddIcon(&clock);
	list.AddIcon(&gear);
	list.AddIcon(&light);
	list.AddIcon(&home);
	list.AddIcon(&settings);
}

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

void Menu::Draw() {
	uint8_t i = 0;
	
	while (i < list.GetIconCount()) {
		if (Icon* currentIcon =list.GetAt(i)) {
			u8g2.setFont(currentIcon->GetFont());
			u8g2.drawGlyph(currentIcon->GetPosition().x, currentIcon->GetPosition().y, currentIcon->GetGlyphId());
			DrawLayout();
			i++;
		}
	}
	

	static uint8_t j = 0;
	j++;
	if (j > 50) {
		cursor.SetPosition(list.GetAt(0));
		if (j > 100) {
			cursor.NextPosition(&list);
			if (j > 150) {
				cursor.NextPosition(&list);
				j = 0;
			}
		}
	}
	cursor.Render();
}