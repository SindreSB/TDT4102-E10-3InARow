#include "GameWindow.h"

const map<Player, Cell> playerToCellState{
	{Player::one, Cell::cross},
	{Player::two, Cell::sircle}
};

GameWindow::GameWindow(Point xy, int width, int height, const string& title):
	Graph_lib::Window{ xy, width * cellSize, height * cellSize, title }, height{ height }, width{width}
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

bool GameWindow::haveNSymbolsInARow(Player p)
{
	bool nInARow;
	// Vi må sjekke alle korisontale og alle vertikale linjer, samt de to diagonalene
	// Vertikale
	for (int i{ 0 }; i < width; i++) {
		nInARow = true;
		for (int j{ 0 }; j < height; j++) {
			if (tiles[j * width + i].state != playerToCellState.at(p)) {
				nInARow = false;
				break;
			}
		}
		if (nInARow) { return true; }
	}

	for (int j{ 0 }; j < height; j++) {
		nInARow = true;
		for (int i{ 0 }; i < width; i++) {
			if (tiles[j * width + i].state != playerToCellState.at(p)) {
				nInARow = false;
				break;
			}
		}
		if (nInARow) { return true; }
	}
	// Diagonal økende
	nInARow = true;
	for (int i{ 0 }; i < width; i++) {
		if (tiles[i * width + i].state != playerToCellState.at(p)) {
			nInARow = false;
			break;
		}
	}
	if (nInARow) { return true; }

	nInARow = true;
	for (int i{ 0 }; i < width; i++) {
		if (tiles[i * width + (width-1 -i)].state != playerToCellState.at(p)) {
			nInARow = false;
			break;
		}
	}
	if (nInARow) { return true; }

	return false;
}

int GameWindow::isGameOver()
{
	if (haveNSymbolsInARow(Player::one)) {
		cout << "Player one won";
	}
	if (haveNSymbolsInARow(Player::two)) {
		cout << "Player two won";
	}
	return 0;
}

void GameWindow::handleClick(Point clickPosition) {
	// Sjekk at klikk var innenfor skjermen
	if (!inRange(clickPosition)) {
		return;
	}
	
	// Sett tile til riktig symbol
	Tile& clickedTile = at(clickPosition);
	if (clickedTile.state != Cell::empty) {
		return;
	}

	clickedTile.set_state(playerToCellState.at(playerTurn));
	playerTurn = playerTurn == Player::one ? Player::two : Player::one; // Toggle player turn

	// TODO check for victory
	isGameOver();
}

void GameWindow::cbClick(Address, Address pw)
{
	Point xy{ Fl::event_x(), Fl::event_y() };
	MouseButton mb = static_cast<MouseButton>(Fl::event_button());
	
	reference_to<GameWindow>(pw).handleClick(xy);
}
