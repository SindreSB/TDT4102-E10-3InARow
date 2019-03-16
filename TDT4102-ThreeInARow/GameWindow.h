#pragma once
#include "Window.h"
#include "Tile.h"

using namespace Graph_lib;
enum class MouseButton { left = FL_LEFT_MOUSE, right = FL_RIGHT_MOUSE }; 
enum class Player {one, two};

class GameWindow : Graph_lib::Window {
public:
	static constexpr int cellSize = 50;
	GameWindow(Point xy, int width, int height, const string& title);

private:
	Vector_ref<Tile> tiles;
	const int width; //width i antall ruter 
	const int height; //heigth i antall ruter

	Player playerTurn = Player::one; // 

	//Height og Width i piksler
	int Height() const { return height * cellSize; }
	int Width() const { return width * cellSize; }

	bool inRange(Point xy) const { return xy.x >= 0 && xy.x < Width() && xy.y >= 0 && xy.y < Height(); }
	Tile& at(Point xy) { return tiles[xy.x / cellSize + (xy.y / cellSize) * width]; }
	const Tile& at(Point xy) const { return tiles[xy.x / cellSize + (xy.y / cellSize) * width]; }

	bool haveNSymbolsInARow(Player p);
	int isGameOver();
	void handleClick(Point clickPosition);

	//callback funksjon for tile knappen
	static void cbClick(Address, Address pw);
};