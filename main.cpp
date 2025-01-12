#include <iostream>
#include <stdlib.h>
#include <string>

using std::cout , std::cin, std::string;

enum symbols {empty, X, O, draw};

int main() {
    int grid[9][3][3];
    int bigGrid[3][3];

    string symbolX[3] = {" \\ /  ", "  X   ", " / \\  "};
    string symbolO[3] = {" ---  ", "|   | ", " ---  "};

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                grid[i][j][k] = empty; // marking that place is empty
                bigGrid[j][k] = empty; // marking that place is empty
            }
        }
    }

    // row index of big cell
    int bigCellRowNum = 0;
    char displaySymbol= ' ';
    int current = -1;
    // if true, it is X's turn O's otherwise
    bool turn = true;
    int row, col;
    int winner;
    do {
        system("cls");

        // current row in big grid
        for (int bigCellRow = 0; bigCellRow < 9; bigCellRow++) {
            cout << "   ";
            bigCellRowNum = bigCellRow / 3;
            for (int cellRow = 0; cellRow < 3; cellRow++) {
                switch (bigGrid[bigCellRowNum][cellRow]) {
                    case X:
                        cout << symbolX[bigCellRow % 3];
                        break;
                    case O:
                        cout << symbolO[bigCellRow % 3];
                        break;
                    case draw:
                        cout << "      ";
                        break;
                    default:

                        for (int symbol = 0; symbol < 3; symbol++) {
                            switch (grid[bigCellRowNum * 3 + cellRow][bigCellRow % 3][symbol]) {
                                case X:
                                    displaySymbol = 'X';
                                    break;
                                case O:
                                    displaySymbol = 'O';
                                    break;
                                case empty:
                                    if (bigCellRowNum * 3 + cellRow == current)
                                        displaySymbol = '@';
                                    else
                                        displaySymbol = ' ';
                                    break;
                                default:
                                    displaySymbol = ' ';
                                    break;
                            }
                            if (symbol != 2)
                                cout << displaySymbol << '|';
                            else 
                                cout << displaySymbol << ' ';
                        }

                        break;
                }
                if (cellRow != 2) 
                    cout << "|| ";
                else
                    cout << '\n';
            }
            if ((bigCellRow + 1) % 3 == 0 && bigCellRow != 8) {
                cout << "=============================\n";
            }
        }
        
        cout << "It is ";
        if (turn)
            cout << "X";
        else
            cout << "O";
        cout << "'s turn\n";
        if (current == -1 || bigGrid[current / 3][current % 3] != empty) {
            do {
                cout << "Enter row for big cell: ";
                cin >> row;
                cout << "Enter column for big cell: ";
                cin >> col;
                row--;
                col--;
                if (row < 0 || row > 2 || col < 0 || col > 2) {
                    cout << "Invalid coords, reenter\n";
                    continue;
                }
                if (bigGrid[row][col] != empty)
                    cout << "Invalid coords, reenter\n";
            } while (bigGrid[row][col] != empty);
            current = row * 3 + col;
            system("cls");
            continue;
        }
        
        do {
            cout << "Enter row to place symbol: ";
            cin >> row;
            cout << "Enter column to place symbol: ";
            cin >> col;
            row--;
            col--;
            if (row < 0 || row > 2 || col < 0 || col > 2) {
                cout << "Invalid coords, reenter\n";
                continue;
            }
            if (grid[current][row][col] != empty)
                cout << "Invalid coords, reenter\n";
        } while (grid[current][row][col] != empty);

        grid[current][row][col] = turn ? X : O;
        

        int zeroCount = 0;
        int bigZeroCount = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[current][i][j] == empty)
                    zeroCount++;
                if (bigGrid[i][j] == empty)
                    bigZeroCount++;
            }
        }

        if (zeroCount == 0 && bigGrid[current / 3][current % 3] == empty)
            bigGrid[current / 3][current % 3] = draw;

        if (bigZeroCount == 0)
            winner = draw;

        // checking if rows are same
        for (int i = 0; i < 3; i++) {
            if (grid[current][i][0] == grid[current][i][1]
                && grid[current][i][1] == grid[current][i][2]
                && grid[current][i][0] != empty
                && grid[current][i][0] != draw) {

                    bigGrid[current / 3][current % 3] = grid[current][i][0];
            }

            if (bigGrid[i][0] == bigGrid[i][1]
                && bigGrid[i][1] == bigGrid[i][2]
                && bigGrid[i][0] != empty
                && bigGrid[i][0] != draw) {

                    winner = bigGrid[i][0];
            }
        }

        // checking if columns are same
        for (int i = 0; i < 3; i++) {
            if (grid[current][0][i] == grid[current][1][i]
                && grid[current][1][i] == grid[current][2][i]
                && grid[current][0][i] != empty
                && grid[current][0][i] != draw) {
                    
                    bigGrid[current / 3][current % 3] = grid[current][0][i];
            }

            if (bigGrid[0][i] == bigGrid[1][i]
                && bigGrid[1][i] == bigGrid[2][i]
                && bigGrid[0][i] != empty
                && bigGrid[0][i] != draw) {
                    
                    winner = bigGrid[0][i];
            }
        }

        // checking if first diagonal is same
        if (grid[current][0][0] == grid[current][1][1]
            && grid[current][1][1] == grid[current][2][2]
            && grid[current][0][0] != empty
            && grid[current][0][0] != draw) {
                bigGrid[current / 3][current % 3] = grid[current][0][0];
        }

        // checking if first digonal in big grid is same
        if (bigGrid[0][0] == bigGrid[1][1]
            && bigGrid[1][1] == bigGrid[2][2]
            && bigGrid[0][0] != empty
            && bigGrid[0][0] != draw) {
                winner = bigGrid[0][0];
        }

        // checking if second diagonal is same
        if (grid[current][2][0] == grid[current][1][1]
            && grid[current][1][1] == grid[current][0][2]
            && grid[current][2][0] != empty
            && grid[current][2][0] != draw) {
                bigGrid[current / 3][current % 3] = grid[current][2][0];
        }

        // checking if second diagonal in big grid is same
        if (bigGrid[2][0] == bigGrid[1][1]
            && bigGrid[1][1] == bigGrid[0][2]
            && bigGrid[2][0] != empty
            && bigGrid[2][0] != draw) {
                winner = bigGrid[2][0];
        }

        // calculating new current big cell
        current = row * 3 + col;
        // passing turn to another player
        turn = !turn;

    } while (winner == empty);

    switch (winner) {
        case X:
            cout << "X has won!\n";
            break;
        case O:
            cout << "O has won!\n";
            break;
        case draw:
            cout << "It is a draw!\n";
            break;
    }

    return 0;
}