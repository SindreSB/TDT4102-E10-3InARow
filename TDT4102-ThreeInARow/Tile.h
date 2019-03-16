#pragma once
#include <GUI.h>

using namespace Graph_lib;

enum class Cell { empty, cross, sircle};

struct Tile : Button {
	Cell state = Cell::empty;
	
	Tile(Point pos, int size, Graph_lib::Callback cb) : Button(pos, size, size, "", cb) {};

	void set_label(string s) { label = s; redraw(); }

	void set_state(Cell state);

};