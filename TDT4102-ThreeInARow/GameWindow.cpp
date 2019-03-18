#include "GameWindow.h"


const map<Player, Cell> playerToCellState{
	{Player::one, Cell::cross},
	{Player::two, Cell::sircle}
};

GameWindow::GameWindow(Point xy, const string& title):
	Graph_lib::Window{ xy, width * cellSize, height * cellSize, title }
{
	// Legg til alle tiles p� vinduet
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			int y = i * cellSize,
				x = j * cellSize;
			tiles.push_back(new Tile{ Point{x, y}, cellSize, cbClick });
			attach(tiles.back());
		}
	}

	// Fjern window reskalering
	resizable(nullptr);
	size_range(x_max(), y_max(), x_max(), y_max());
}



void GameWindow::togglePlayerTurn()
{
	playerTurn = playerTurn == Player::one ? Player::two : Player::one;
}

void GameWindow::cbClick(Address, Address pw)
{
	Point xy{ Fl::event_x(), Fl::event_y() };
	MouseButton mb = static_cast<MouseButton>(Fl::event_button());
	
	auto& win = reference_to<GameWindow>(pw);

	// Sjekk at klikk var innenfor skjermen
	if (!win.inRange(xy)) {
		return;
	}




}
