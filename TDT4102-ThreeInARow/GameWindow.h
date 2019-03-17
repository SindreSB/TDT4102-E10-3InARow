#pragma once
#include "Window.h"
#include "Tile.h"

using namespace Graph_lib;
enum class MouseButton { left = FL_LEFT_MOUSE, right = FL_RIGHT_MOUSE }; 
enum class Player {one, two};

class GameWindow : Graph_lib::Window {
public:
	static constexpr int width = 3;
	static constexpr int height = 3;
	static constexpr int cellSize = 50;
	GameWindow(Point xy, const string& title);

private:
	// Graphic objects
	Vector_ref<Tile> tiles;
	Text gameOverText;

	//Height og Width i piksler
	int Height() const { return height * cellSize; }
	int Width() const { return width * cellSize; }

	// Variables to keep track of game state
	Player playerTurn = Player::one; 
	bool gameOver = false;

	bool inRange(Point xy) const { return xy.x >= 0 && xy.x < Width() && xy.y >= 0 && xy.y < Height(); }
	Tile& at(int x, int y) { return tiles[x + width * y]; }
	Tile& at(Point xy) { return tiles[xy.x / cellSize + (xy.y / cellSize) * width]; }
	const Tile& at(Point xy) const { return tiles[xy.x / cellSize + (xy.y / cellSize) * width]; }

	int isGameOver();
	bool haveNSymbolsInARow(Player p);

	Player getPlayerTurn() { return playerTurn; }
	void togglePlayerTurn();

	//callback funksjon for tile knappen
	static void cbClick(Address, Address pw);
};