#ifndef ACTION_H
#define ACTION_H

enum class Actions{NONE, BACK, CURSOR_NEXT, CURSOR_PREVIOUS, SELECTION_LIST, USER_INTERFACE_MESSAGE, INPUT_VALUE};

struct Action {

	Actions upAction;
	Actions downAction;
	Actions leftAction;
	Actions rightAction;

	Action(Actions upAction, Actions downAction, Actions leftAction, Actions rightAction) : upAction(upAction), downAction(downAction), leftAction(leftAction), rightAction(rightAction) {}
	~Action() {}
};

#endif //ACTION_H
