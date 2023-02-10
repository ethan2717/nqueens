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

/*class QTriplet {
	public:
		Queen *arr;
		int col;
		bool signal;
};*/

bool colOccupied(vector<vector<int>> board, int col, int n) {
	// checks whether a given column is already occupied
	for (int r = 1; r < n; r++) {
		if (board[r][col] == 1) {
			//cout << "\tcolumn " << col << " is occupied" << endl;
			return true;
		}
	}
	return false;
}

/*bool QcolOccupied(Queen *arr, int col) {
	int size = sizeof(arr)/sizeof(Queen);
	for (int q = 0; q < size; q++) {
		for (int r = 1; r <= size; r++) {
			if (arr[q].col == col && arr[q].row == r) {
				return true;
			}
		}
	}
	return false;
}*/

/*bool QisSafe(Queen *arr, int col, int row) {
	int size = sizeof(arr)/sizeof(Queen);
	for (int q = 0; q < size; q++) {
		for (int c = 1; c <= size; c++) {
			if (arr[q].row == row && arr[q].col == c) {
				return false;
			}
		}
	}
	// tr
	for (int q = 0; q < size; q++) {
		for (int c = col, r = row; c > 0 && r <= size; c--, r++) {
			if (arr[q].row == r && arr[q].col == c) {
				return false;
			}
		}
	}
	// tl
	for (int q = 0; q < size; q++) {
		for (int c = col, r = row; c <= size && r <= size; c++, r++) {
			if (arr[q].row == r && arr[q].col == c) {
				return false;
			}
		}
	}
	// br
	for (int q = 0; q < size; q++) {
		for (int c = col, r = row; c > 0 && r > 0; c--, r--) {
			if (arr[q].row == r && arr[q].col == c) {
				return false;
			}
		}
	}
	// bl
	for (int q = 0; q < size; q++) {
		for (int c = col, r = row; c <= size && r > 0; c++, r--) {
			if (arr[q].row == r && arr[q].col == c) {
				return false;
			}
		}
	}
	return true;
}*/

// checks whether it is safe to place a queen in the given space
bool isSafe(vector<vector<int>> board, int col, int row, int n) {
	//int size = n - 1;
	//int prow = size - row + 1;
	// checks horizontally
	for (int c = 1; c < n; c++) {
		if (board[row][c] == 1) {
			//cout << col << ", " << prow << " cannot be placed due to horz from " << c << ", " << prow << endl;
			return false;
		}
	}
	/*// checks vertically
	for (int r = 1; r < n; r++) {
		if (board[r][col] == 1) {
			cout << col << ", " << prow << " cannot be placed due to vert from " << col << ", " << size-r+1 << endl;
			return false;
		}
	}*/
	// checks top right diagonal
	for (int c = col, r = row; c > 0 && r < n; c--, r++) {
		if (board[r][c] == 1) {
			//cout << col << ", " << prow << " cannot be placed due to tr_diag from " << c << ", " << size-r+1 << endl;
			return false;
		}
	}
	// checks top left diagonal
	for (int c = col, r = row; c < n && r < n; c++, r++) {
		if (board[r][c] == 1) {
			//cout << col << ", " << prow << " cannot be placed due to tl_diag from " << c << ", " << size-r+1 << endl;
			return false;
		}
	}
	// checks bottom right diagonal
	for (int c = col, r = row; c > 0 && r > 0; c--, r--) {
		if (board[r][c] == 1) {
			//cout << col << ", " << prow << " cannot be placed due to br_diag from " << c << ", " << size-r+1 << endl;
			return false;
		}
	}
	// checks bottom left diagonal
	for (int c = col, r = row; c < n && r > 0; c++, r--) {
		if (board[r][c] == 1) {
			//cout << col << ", " << prow << " cannot be placed due to bl_diag from " << c << ", " << size-r+1 << endl;
			return false;
		}
	}
	//cout << "\t(" << col << ", " << prow << ") is safe" << endl;
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

/*bool nQueensRecur(int **board, int col, int size) {
	while (colOccupied(board, col, size + 1) && col <= size) {
		col++;
	}
	if (col > size) {
		cout << "col greater than size" << endl;
		return true;
	}
	for (int r = 1; r <= size; r++) {
		int true_r = size - r + 1; // due to the way the indexing works, the value produced by the for loop must be adjusted
		//cout << "  col is " << col << " and true_r is " << true_r << endl;
		if (isSafe(board, col, true_r, size + 1)) {
			cout << "change at " << col << ", " << r << endl;
			board[true_r][col] = 1;
			printBoard(board, size);
			if (nQueensRecur(board, col + 1, size)) {
				return true;
			}
			board[true_r][col] = 0;
		}
	}
	cout << "returning false" << endl;
	return false;
}*/

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
			//cout << "------------" << endl;
			int size, n, l = 1;
			//stack<class Queen> queens;
			Queen q;
			line_ca = strdup(line.c_str()); // stores each line of text as a character array

			size = strtol(strtok(line_ca, " "), &dummy, 10); // records the first number as the board size
			n = size + 1;
			if (size < 4) { // boards less than 4x4 have no solution
				outfile << "No solution" << endl;
				continue;
			}
			/*Queen arr[size];
			for (int q = 0; q < size; q++) {
				Queen newQ;
				newQ.col = newQ.row = -1;
				arr[q] = newQ;
			}*/

			// create a board of size nxn and fill 1->size with zeroes
			vector<int> row(n, 0);
			vector<vector<int>> board(n, row);
			/*board = new int *[n];
			for (int i = 0; i < n; i++) {
				board[i] = new int[n];
			}*/

			bool noSolution = false;
			//int q_cnt = 0;
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
					/*if (!QisSafe(arr, q.col, q.row)) {
						outfile << "No solution" << endl;
						noSolution = true;
						break;
					} else {
						arr[q_cnt] = q;
						q_cnt++;
					}*/

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
				/*Queen *ans;
				stack<class QTriplet> recurStack;
				QTriplet init, stacktop;
				init.arr = arr;
				init.col = 1;
				init.signal = false;
				recurStack.push(init);
				while (!recurStack.empty()) {
					stacktop = recurStack.top();
					recurStack.pop();
					while (QcolOccupied(stacktop.arr, stacktop.col) && stacktop.col <= size) {
						stacktop.col++;
					}
					if (stacktop.col > size) {
						stacktop.signal = true;
						ans = stacktop.arr;
						continue;
					}
					for (int r = 1; r <= size; r++) {
						int true_r = size - r + 1;
						if (QisSafe(stacktop.arr, stacktop.col, true_r)) {
							QTriplet to_push;
							to_push.col = stacktop.col + 1;
							to_push.arr = stacktop.arr;
							Queen newQ;
							newQ.col = stacktop.col;
							newQ.row = true_r;
							to_push.arr[q_cnt] = newQ;
							to_push.signal = stacktop.signal;
							recurStack.push(to_push);
						}
					}
					stacktop.signal = false;
				}*/

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

					//int validSpots = 0; // validSpots is used to count how many valid spots are in the current column
					for (int r = 1; r <= size; r++) {
						int true_r = size - r + 1; // true_r is used to represent rows more logically
						if (isSafe(stacktop.board, stacktop.col, true_r, n)) {
							//validSpots++;
							Triplet to_push;
							/*if (validSpots > 1) {
								for (int wipeR = 1; wipeR <= size; wipeR++) {
									stacktop.board[wipeR][stacktop.col] = 0;
								}
								//to_push.col = stacktop.col;
							}*/ //else {
							to_push.col = stacktop.col + 1;
							//}
							to_push.board = stacktop.board;
							to_push.board[true_r][stacktop.col] = 1;
							//printBoard(to_push.board, size);
							//cout << " - to_push.col is " << to_push.col << endl;
							//cout << " - to_push.board is: " << endl;
							//printBoard(to_push.board, size);

							to_push.signal = stacktop.signal;
							recurStack.push(to_push);
						}
					}
					stacktop.signal = false;
					//recurStack.pop();
					//stacktop.col--;
				}
				if (stacktop.signal == false) {
					//cout << " > final\nNo solution" << endl;
				//if (!nQueensRecur(board, 1, size)) {
					outfile << "No solution" << endl;
					continue;
				} else {
					//cout << " > final" << endl;
					/*for (int q = 0; q < size; q++) {
						cout << ans[q].col << " " << ans[q].row << " ";
					}*/
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
			//cout << " > final" << endl;
			//printBoard(board), size);

/*
			// create a stack and use it to simulate recursion
int **ans;
stack<class Triplet> recurStack;
Triplet init, stacktop;
init.board = board;
init.col = 0;
init.signal = false;
recurStack.push(init);

while (!recurStack.empty()) {
	stacktop = recurStack.top();
	recurStack.pop();
	if (stacktop.col >= size) {
		stacktop.signal = true;
		ans = stacktop.board;
		continue;
	}
	for (int r = 0; r < size; r++) {
		if (isSafe(stacktop.board, stacktop.col, r, n)) {
			Triplet to_push;
			to_push.board[stacktop.col][r] = 1;
			to_push.col = stacktop.col + 1;
			to_push.signal = stacktop.signal;
			recurStack.push(to_push);
			if (to_push.signal == true) {
				stacktop.signal = true;
				ans = stacktop.board;
				break;
				continue;
			}
			stacktop.board[stacktop.col][r] = 0;
		}
	}
	stacktop.signal = false;
	continue;
}*/
		}
	}

	infile.close();
	outfile.close();
	return 0;
}