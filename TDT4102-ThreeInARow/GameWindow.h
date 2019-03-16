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
	Vector_ref<Tile> tiles;
	Player playerTurn = Player::one; // 


	//Height og Width i piksler
	int Height() const { return height * cellSize; }
	int Width() const { return width * cellSize; }

	bool inRange(Point xy) const { return xy.x >= 0 && xy.x < Width() && xy.y >= 0 && xy.y < Height(); }
	Tile& at(int x, int y) { return tiles[x + width * y]; }
	Tile& at(Point xy) { return tiles[xy.x / cellSize + (xy.y / cellSize) * width]; }
	const Tile& at(Point xy) const { return tiles[xy.x / cellSize + (xy.y / cellSize) * width]; }

	bool haveNSymbolsInARow(Player p);
	int isGameOver();

	Player getPlayerTurn() { return playerTurn; }
	void togglePlayerTurn();

	//callback funksjon for tile knappen
	static void cbClick(Address, Address pw);
};