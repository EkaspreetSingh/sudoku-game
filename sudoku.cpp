#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

#define N 9

void displayMenu();
void startGame();
void autoSolve();
void displayBoard(vector<vector<int>> &board);
bool isSafe(vector<vector<int>> &board, int row, int col, int num);
bool solveSudoku(vector<vector<int>> &board);
bool isValidMove(vector<vector<int>> &board, int row, int col, int num);
vector<vector<int>> generateFullBoard();
vector<vector<int>> generatePuzzleBoard(vector<vector<int>> &fullBoard, int cellsToRemove);
void playGame(vector<vector<int>> &board);
void makeMove(vector<vector<int>> &board);

int main() {
    srand(time(0));
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                startGame();
                break;
            case 2:
                autoSolve();
                break;
            case 3:
                cout << "Exiting the game." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

void displayMenu() {
    cout << "Sudoku Game Menu" << endl;
    cout << "1. Start Game" << endl;
    cout << "2. Auto Solve" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
}

void startGame() {
    vector<vector<int>> fullBoard = generateFullBoard();
    vector<vector<int>> puzzleBoard = generatePuzzleBoard(fullBoard, 40);  // Remove 40 cells for the puzzle
    playGame(puzzleBoard);
}

void autoSolve() {
    vector<vector<int>> fullBoard = generateFullBoard();
    vector<vector<int>> puzzleBoard = generatePuzzleBoard(fullBoard, 40);  // Remove 40 cells for the puzzle
    cout << "Original Board:" << endl;
    displayBoard(puzzleBoard);

    if (solveSudoku(puzzleBoard)) {
        cout << "Solved Board:" << endl;
        displayBoard(puzzleBoard);
    } else {
        cout << "No solution exists." << endl;
    }
}

void displayBoard(vector<vector<int>> &board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0)
                cout << ". ";
            else
                cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool isSafe(vector<vector<int>> &board, int row, int col, int num) {
    for (int x = 0; x < N; x++)
        if (board[row][x] == num || board[x][col] == num)
            return false;

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i + startRow][j + startCol] == num)
                return false;

    return true;
}

bool solveSudoku(vector<vector<int>> &board) {
    int row, col;
    bool isEmpty = false;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (board[row][col] == 0) {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty) break;
    }

    if (!isEmpty)
        return true;

    for (int num = 1; num <= 9; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;
            if (solveSudoku(board))
                return true;
            board[row][col] = 0;
        }
    }
    return false;
}

bool isValidMove(vector<vector<int>> &board, int row, int col, int num) {
    return board[row][col] == 0 && isSafe(board, row, col, num);
}

vector<vector<int>> generateFullBoard() {
    vector<vector<int>> board(N, vector<int>(N, 0));
    solveSudoku(board);
    return board;
}

vector<vector<int>> generatePuzzleBoard(vector<vector<int>> &fullBoard, int cellsToRemove) {
    vector<vector<int>> puzzleBoard = fullBoard;
    int count = cellsToRemove;

    while (count > 0) {
        int row = rand() % N;
        int col = rand() % N;

        if (puzzleBoard[row][col] != 0) {
            puzzleBoard[row][col] = 0;
            count--;
        }
    }

    return puzzleBoard;
}

void playGame(vector<vector<int>> &board) {
    int choice;

    while (true) {
        displayBoard(board);
        cout << "1. Make a Move" << endl;
        cout << "2. Auto Solve" << endl;
        cout << "3. Exit to Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                makeMove(board);
                break;
            case 2:
                if (solveSudoku(board)) {
                    cout << "Auto-solved Board:" << endl;
                    displayBoard(board);
                } else {
                    cout << "No solution exists." << endl;
                }
                return;
            case 3:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void makeMove(vector<vector<int>> &board) {
    int row, col, num;
    cout << "Enter row (1-9), column (1-9), and number (1-9) to place: ";
    cin >> row >> col >> num;

    if (isValidMove(board, row - 1, col - 1, num)) {
        board[row - 1][col - 1] = num;
    } else {
        cout << "Invalid move. Try again." << endl;
    }
}
