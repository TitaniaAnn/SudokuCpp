#pragma once
class Game
{
private:
	struct Cell {
		std::string value;
		int move;
		bool valid;
		bool readonly;
		std::string possibleValues;

		Cell::Cell() {
			value = "0";
			move = 0;
			valid = false;
			readonly = false;
			possibleValues = "";
		}
	};
	std::vector<Cell> board;
	int boardSize;
	bool test;
	std::string validValues;
	void getAllPossible();
	void updatePossible(int r, int c);
	std::string computeValues(int r, int c);
	void getCoordinates(int * r, int * c);
	void Game::generateBoard(int level);

public:
	Game();
	Game(std::string ** board, int size, std::string vValues);
	~Game();
	void displayOptions();
	void displayBoard();
	void displayPossible();
	void editSquare();
	
};

