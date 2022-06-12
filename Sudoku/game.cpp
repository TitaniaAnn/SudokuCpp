#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include "game.h"
 
// Constructors
Game::Game()
{
	boardSize = 9;
	test = false;
	validValues = "123456789";
	board.resize(boardSize * boardSize);
	// generate game
	for (int a = 0; a < boardSize; a++) {
		for (int b = 0; b < boardSize; b++) {
			
		}
	}
	getAllPossible();
}

Game::Game(std::string ** tboard, int size, std::string vValues) {
	boardSize = size;
	test = false;
	validValues = vValues;
	board.resize(boardSize * boardSize);
	for (int a = 0; a < boardSize; a++) {
		for (int b = 0; b < boardSize; b++) {
			if (tboard[a][b] != "0") {
				board[a * boardSize + b].value = tboard[a][b];
				board[a * boardSize + b].readonly = true;
				board[a * boardSize + b].valid = true;
			}
		}
	}
}

Game::~Game()
{
}

void Game::getAllPossible() {
	for (int a = 0; a < boardSize; a++) {
		for (int b = 0; b < boardSize; b++) {
			if (board[a * boardSize + b].value == "0")
				board[a * boardSize + b].possibleValues = computeValues(a, b);
			else
				board[a * boardSize + b].possibleValues = "";
		}
	}
}

void Game::updatePossible(int r, int c) {
	for (int a = 0; a < boardSize; a++) {
			if (board[r * boardSize + a].value == "0")
				board[r * boardSize + a].possibleValues = computeValues(r, a);
			else
				board[r * boardSize + a].possibleValues = "";
			if (board[a * boardSize + c].value == "0")
				board[a * boardSize + c].possibleValues = computeValues(a, c);
			else
				board[a * boardSize + c].possibleValues = "";
	}

	int sRow = ((r + 1) - (r % 3)) - 1;
	int sCol = ((c + 1) - (c % 3)) - 1;
	for (int a = sRow; a < sRow + 3; a++) {
		for (int b = sCol; b < sCol + 3; b++) {
			if (board[a * boardSize + b].value == "0")
				board[a * boardSize + b].possibleValues = computeValues(a, b);
			else
				board[a * boardSize + b].possibleValues = "";
		}
	}
}

std::string Game::computeValues(int r, int c) {
	std::string values;
	for (int a = 0; a < boardSize * boardSize; a++) {
		if (values.find(board[a].value) == std::string::npos) {
			if (values.length() > 0)
				values += " ";
			values += board[a].value;
		}
	}
	for (int a = 0; a < 9; a++) {
		if (board[r * boardSize + a].value != "0") {
			std::string::size_type i = values.find(board[r * boardSize + a].value);
			values.erase(i, board[r * boardSize + a].value.length());
		}
		else if (board[a * boardSize + c].value != "0") {
			std::string::size_type i = values.find(board[a * boardSize + c].value);
			values.erase(i, board[a * boardSize + c].value.length());
		}
	}

	int sRow = ((r + 1) - (r % 3)) - 1;
	int sCol = ((c + 1) - (c % 3)) - 1;
	for (int a = sRow; a < sRow + 3; a++) {
		for (int b = sCol; b < sCol + 3; b++) {
			if (board[a * boardSize + b].value != "0") {
				std::string::size_type i = values.find(board[a * boardSize + b].value);
				values.erase(i, board[a * boardSize + b].value.length());
			}
		}
	}
	return values;
}

void Game::displayOptions() {
	std::cout << "Options:" << std::endl;
	std::cout << "   ?  Show these instructions" << std::endl;
	std::cout << "   D  Display the board" << std::endl;
	std::cout << "   E  Edit one square" << std::endl;
	std::cout << "   S  Show the possible values for a square" << std::endl;
	std::cout << "   C  Solve the puzzle" << std::endl;
	std::cout << "   Q  Save and Quit" << std::endl << std::endl;
}

void Game::displayBoard() {
	std::string stringBoard = "   A B C D E F G H I\n";
	for (int a = 0; a < 9; a++) {
		stringBoard += (a + 1) + "  ";
		for (int b = 0; b < 9; b++) {
			stringBoard += board[a * boardSize + b].value;
			if (b == 2 || b == 5)
				stringBoard += "|";
			else if (b < 8)
				stringBoard += " ";
			else
				stringBoard += "\n";
		}
		if (a == 2 || a == 5)
			stringBoard += "   -----+----+-----\n";
	}
	stringBoard += "\n";
	std::cout << stringBoard;
}

void Game::displayPossible() {
	int r, c;
	getCoordinates(&r, &c);

	std::cout << board[r * boardSize + c].possibleValues;
}

void Game::editSquare() {
	int r, c;
	getCoordinates(&r, &c);
	std::string input;
	do {
		std::cout << ">";
		std::cin >> input;
	} while (validValues.find(input) == std::string::npos);

	if (board[r * boardSize + c].possibleValues.find(input) != std::string::npos) {
		board[r * boardSize + c].value = input;
		if (board[r * boardSize + c].possibleValues.length() < 3 && !test)
			board[r * boardSize + c].valid = true;
		board[r * boardSize + c].possibleValues = "";
		updatePossible(r, c);
	}
}

void Game::getCoordinates(int * r, int * c) {
	char alpha[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I' };
	char coord[3];
	int row, col;
	do {
		std::cout << "What are the coordinates of the square: ";
		std::cin.get(coord, 3);
		std::cin.ignore();

		if ((!(!isdigit(coord[0]) && !isalpha(coord[1])) && ((coord[0] < '1' || coord[0] > '9') || (toupper(coord[1]) < toupper(alpha[0]) || toupper(coord[1]) > toupper(alpha[8])))) ||
			(!(!isdigit(coord[1]) && !isalpha(coord[0])) && ((coord[1] < '1' || coord[1] > '9') || (toupper(coord[0]) < toupper(alpha[0]) || toupper(coord[0]) > toupper(alpha[8]))))) {
			std::cout << "ERROR: Square \'" << coord << "\' is invalid\n";
		}
	} while ((!(!isdigit(coord[0]) && !isalpha(coord[1])) && ((coord[0] < '1' || coord[0] > '9') || (toupper(coord[1]) < toupper(alpha[0]) || toupper(coord[1]) > toupper(alpha[8])))) ||
		(!(!isdigit(coord[1]) && !isalpha(coord[0])) && ((coord[1] < '1' || coord[1] > '9') || (toupper(coord[0]) < toupper(alpha[0]) || toupper(coord[0]) > toupper(alpha[8])))));

	row = (isdigit(coord[0])) ? (coord[0] - '0') - 1 : (coord[1] - '0') - 1;
	*r = row;

	col = (isalpha(coord[0])) ? (toupper(coord[0]) - toupper(alpha[0])) : (toupper(coord[1]) - toupper(alpha[0]));
	*c = col;
} 