// Filename: nqueens.cpp
//
// This is the main file for this program.
//
// Ethan Yeung, October 2022

#include <iostream>
#include <stack>
#include <fstream>
#include <cstring>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

class Queen {
	public:
		int col;
		int row;
};

class Triplet {
	public:
		vector<vector<int>> board;
		int col;
		bool signal;
};

bool colOccupied(vector<vector<int>> board, int col, int n) {
	// checks whether a given column is already occupied
	for (int r = 1; r < n; r++) {
		if (board[r][col] == 1) {
			return true;
		}
	}
	return false;
}

// checks whether it is safe to place a queen in the given space
bool isSafe(vector<vector<int>> board, int col, int row, int n) {
	// checks horizontally
	for (int c = 1; c < n; c++) {
		if (board[row][c] == 1) {
			return false;
		}
	}
	// checks top right diagonal
	for (int c = col, r = row; c > 0 && r < n; c--, r++) {
		if (board[r][c] == 1) {
			return false;
		}
	}
	// checks top left diagonal
	for (int c = col, r = row; c < n && r < n; c++, r++) {
		if (board[r][c] == 1) {
			return false;
		}
	}
	// checks bottom right diagonal
	for (int c = col, r = row; c > 0 && r > 0; c--, r--) {
		if (board[r][c] == 1) {
			return false;
		}
	}
	// checks bottom left diagonal
	for (int c = col, r = row; c < n && r > 0; c++, r--) {
		if (board[r][c] == 1) {
			return false;
		}
	}
	return true;
}

void printBoard(vector<vector<int>> board, int size) {
	for (int r = 1; r <= size; r++) {
		for (int c = 1; c <= size; c++) {
			cout << board[r][c] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main(int argc, char** argv) {
	if (argc != 3) {
		throw std::invalid_argument("Usage: ./nqueens <INPUT FILE> <OUTPUT FILE>");
	}

	ifstream infile;
	infile.open(argv[1]);
	ofstream outfile;
	outfile.open(argv[2]);

	if (infile.is_open()) {
		string line;
		char *line_ca, *dummy, *coord_ca;

		// reads the input file line by line
		while (getline(infile, line)) {
			int size, n, l = 1;
			Queen q;
			line_ca = strdup(line.c_str()); // stores each line of text as a character array

			size = strtol(strtok(line_ca, " "), &dummy, 10); // records the first number as the board size
			n = size + 1;
			if (size < 4) { // boards less than 4x4 have no solution
				outfile << "No solution" << endl;
				continue;
			}

			// create a board of size nxn and fill 1->size with zeroes
			vector<int> row(n, 0);
			vector<vector<int>> board(n, row);

			bool noSolution = false;
			// records the coords of each queen as a Queen object and places it on the board
			while ((coord_ca = strtok(NULL, " "))) {
				int coord = strtol(coord_ca, &dummy, 10);
				if (coord < 1 || coord > size) {
					outfile << "No solution" << endl;
					noSolution = true;
					break;
				}
				l++;
				if (l % 2 == 0) {
					q.col = coord;
				} else {
					q.row = size - coord + 1;

					// if queen can't be placed, output "No solution"; otherwise, place it
					if (!isSafe(board, q.col, q.row, n)) {
						outfile << "No solution" << endl;
						noSolution = true;
						break;
					} else {
						board[q.row][q.col] = 1;
					}
				}
			}
			if (!noSolution) {
				vector<vector<int>> ans;
				stack<class Triplet> recurStack;
				Triplet init, stacktop;
				init.board = board;
				init.col = 1;
				init.signal = false;
				recurStack.push(init);

				while (!recurStack.empty()) {
					stacktop = recurStack.top();
					recurStack.pop();

					while (colOccupied(stacktop.board, stacktop.col, n) && stacktop.col <= size) {
						stacktop.col++;
					}

					if (stacktop.col > size) {
						stacktop.signal = true;
						ans = stacktop.board;
						break;
					}

					for (int r = 1; r <= size; r++) {
						int true_r = size - r + 1; // true_r is used to represent rows more logically
						if (isSafe(stacktop.board, stacktop.col, true_r, n)) {
							Triplet to_push;
							to_push.col = stacktop.col + 1;
							to_push.board = stacktop.board;
							to_push.board[true_r][stacktop.col] = 1;
							to_push.signal = stacktop.signal;
							recurStack.push(to_push);
						}
					}
					stacktop.signal = false;
				}
				if (stacktop.signal == false) {
					outfile << "No solution" << endl;
					continue;
				} else {
					printBoard(ans, size);
					for (int c = 1; c < n; c++) {
						for (int r = 1; r < n; r++) {
							if (ans[r][c] == 1) {
								outfile << c << " " << size - r + 1 << " ";
							}
						}
					}
					outfile << endl;
				}
			}
		}
	}
	infile.close();
	outfile.close();
	return 0;
}
