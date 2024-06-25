#include <vector>
#include <iostream>

using namespace std;

bool isValidSudoku(vector<vector<char>>& board) {
    int vertical[9][9] = {0};
    int horizontal[9][9] = {0};
    int box[9][9] = {0};

    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(board[i][j] != '.')
            {
                int numIndex = board[i][j] - '1';
                int boxIndex = (i / 3)*3 + j / 3;

                if(vertical[j][numIndex]++ || horizontal[i][numIndex]++ || box[boxIndex][numIndex]++)
                    return false;
            }
        }
    }
    return true;
}

int main() {
    vector<vector<char>> board = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','5','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };

    cout << "The sudoku board is " << (isValidSudoku(board) ? "valid" : "invalid") << endl;

    return 0;
}
