#include "Menu.h"

Menu menu(3, 2, 1, U8X8_PIN_NONE, 4, U8X8_PIN_NONE, true);

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	menu.Initialize();
}

void loop() {
	
	menu.FirstPage();
	do {
		menu.Draw();
	} while (menu.NextPage());
	
	//digitalWrite(LED_BUILTIN, HIGH);
	//delay(500);
	//digitalWrite(LED_BUILTIN, LOW);
	//delay(500);
}
