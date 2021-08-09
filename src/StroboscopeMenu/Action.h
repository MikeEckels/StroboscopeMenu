#ifndef ACTION_H
#define ACTION_H

enum class Actions{NONE, JUMP_OUTOF_SUB_ICONS, JUMP_INTO_SUB_ICONS, CURSOR_NEXT, CURSOR_PREVIOUS, SELECTION_LIST, USER_INTERFACE_MESSAGE, INPUT_VALUE};

struct inputValueData {
	const char* title;
	const char* prefix;
	const char* suffix;
	uint8_t* value;
	uint8_t lowThresh;
	uint8_t highThresh;
	uint8_t decimalPlaces;
};

struct interfaceMessageData {
	const char* title1;
	const char* title2;
	const char* title3;
	const char* buttons;
};

struct selectionListData {
	const char* title;
	const char* optionsList;
	uint8_t startPosition;
};

typedef struct ActionData {
	struct inputValueData inputValue;
	struct interfaceMessageData interfaceMessage;
	struct selectionListData selectionList;

}ActionData;

struct Action {
	Actions upAction;
	Actions downAction;
	Actions leftAction;
	Actions rightAction;

	ActionData actionData;

	Action(Actions upAction, Actions downAction, Actions leftAction, Actions rightAction, ActionData actionData) : upAction(upAction), downAction(downAction), leftAction(leftAction), rightAction(rightAction), actionData(actionData) {}
	~Action() {}
};

#endif //ACTION_H
