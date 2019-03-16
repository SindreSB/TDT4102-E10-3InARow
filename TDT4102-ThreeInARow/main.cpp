// Example program in TDT4102_Graphics template, from PPP page 415
#include "GUI.h"
#include "Window.h"
#include "GameWindow.h"

int main() {
	GameWindow win{ {100, 100}, "3-in-a-row" };

	return gui_main();
}

