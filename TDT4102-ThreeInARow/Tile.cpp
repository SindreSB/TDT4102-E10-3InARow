#include "Tile.h"

// For � sette Tilelabel i henhold til state
const map<Cell, string> cellToSymbol{ {Cell::empty, ""},
									 {Cell::cross, "X"},
									 {Cell::circle, "O"} };

void Tile::set_state(Cell s)
{
	state = s; 
	set_label(cellToSymbol.at(state));
	redraw();
}
