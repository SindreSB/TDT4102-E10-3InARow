#include "Tile.h"

// For � sette Tilelabel i henhold til state
const map<Cell, string> cellToSymbol{ {Cell::empty, ""},
									 {Cell::cross, "X"},
									 {Cell::sircle, "O"} };

const map<Cell, int> cellToColor{
									 {Cell::cross, FL_RED},
									 {Cell::sircle, FL_BLUE} };

void Tile::set_state(Cell state)
{
	state = state; 
	set_label(cellToSymbol.at(state));
	if (state == Cell::cross || state == Cell::sircle) {
		pw->color(cellToColor.at(state));
	}
	redraw();
}
