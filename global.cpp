#include "global.h"

int GetMouseInputRelease(void)
{
	static int lastMouseInput = 0;
	int mouse = GetMouseInput();
	int returnValue = 0;

	if (GetMouseInput() == 0) {
		if ((lastMouseInput & MOUSE_INPUT_LEFT) != 0) {
			returnValue = 1;
		}
		else if ((lastMouseInput & MOUSE_INPUT_RIGHT) != 0) {
			returnValue = 2;
		}
	}
	lastMouseInput = mouse;

	return returnValue;

}
