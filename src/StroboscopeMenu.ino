#include "Menu.h"

Menu menu(3, 4, 1, 2, U8X8_PIN_NONE, U8X8_PIN_NONE, true);

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(115200);
}

void loop() {
	menu.FirstPage();
	do {
		menu.Draw();
	} while (menu.NextPage());
}
