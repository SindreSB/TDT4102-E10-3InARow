#include "GameWindow.h"


const map<Player, Cell> playerToCellState{
	{Player::one, Cell::cross},
	{Player::two, Cell::circle}
};

GameWindow::GameWindow(Point xy, const string& title):
	Graph_lib::Window{ xy, width * cellSize, height * cellSize, title },
	gameOverText{ {Width() / 2, Height() / 2}, ""}
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

	gameOverText.set_color(Color::black);
	gameOverText.move(-40, 0);
	gameOverText.set_font_size(20);
	attach(gameOverText);

	// Fjern window reskalering
	resizable(nullptr);
	size_range(x_max(), y_max(), x_max(), y_max());
}

bool GameWindow::haveNSymbolsInARow(Player p)
{
	bool nInARow;
	// Vi må sjekke alle horisontale og alle vertikale linjer, samt de to diagonalene
	// Vertikale
	for (int i{ 0 }; i < width; i++) {
		nInARow = true;
		for (int j{ 0 }; j < height; j++) {
			if (at(j, i).state != playerToCellState.at(p)) {
				nInARow = false;
				break;
			}
		}
		if (nInARow) { return true; }
	}

	// Horisontale
	for (int j{ 0 }; j < height; j++) {
		nInARow = true;
		for (int i{ 0 }; i < width; i++) {
			if (at(j, i).state != playerToCellState.at(p)) {
				nInARow = false;
				break;
			}
		}
		if (nInARow) { return true; }
	}

	// Diagonal mot høyre
	nInARow = true;
	for (int i{ 0 }; i < width; i++) {
		if (tiles[i * width + i].state != playerToCellState.at(p)) {
			nInARow = false;
			break;
		}
	}
	if (nInARow) { return true; }

	//Diagonal mot venstre
	nInARow = true;
	for (int i{ 0 }; i < width; i++) {
		if (at((width - 1 - i), i).state != playerToCellState.at(p)) {
			nInARow = false;
			break;
		}
	}
	if (nInARow) { return true; }

	return false;
}

bool GameWindow::isGameOver()
{
	// Om vi allerede har sjekket og noe n har vunnet, trenger vi ikke s
	// sjekke igjen
	if (gameOver) {
		return true;
	}

	Player currentPlayer = getPlayerTurn();
	if (haveNSymbolsInARow(currentPlayer)) {
		// Lagre at spillet er vunnet, så vi ikke må sjekke igjen
		gameOver = true;

		if (currentPlayer == Player::one) {
			gameOverText.set_label("One won");
		}
		else {
			gameOverText.set_label("Two won");
		}

		flush();
	}

	return false;
}

void GameWindow::showGameOverText(string text)
{
	gameOverText.set_label("Two won");
	attach(gameOverText);
	flush();
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

	// Sjekk om spillet er over
	if (win.isGameOver()) {
		return;
	}

	// Sjekk at ruten ikke har en verdi fra før
	Tile& clickedTile = win.at(xy);
	if (clickedTile.state != Cell::empty) {
		return;
	}

	// Set symbolet til nåværende spiller i ruten
	Player currentPlayer = win.getPlayerTurn();
	Cell playersCell = playerToCellState.at(currentPlayer);
	clickedTile.set_state(playersCell);

	// Sjekk om noen nå har vunnet
	win.isGameOver();
	
	// Bytt spiller, slik at neste runde setter det andre symbolet
	win.togglePlayerTurn();

}
