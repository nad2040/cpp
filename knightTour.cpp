#include <iostream>

using namespace std;

struct delta {
    int dR;
    int dC;
};

delta possibleMove[8] = {{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1},{-2,1},{-1,2}};

const int dim = 8;

int board[dim][dim] = {0};

void displayBoard() {
    static int solutions = 0;
    for (int row=0; row<dim; ++row) {
        for (int col=0; col<dim; ++col) {
            printf("%02d ",board[row][col]);
        }
        cout << endl;
    }
    cout << ++solutions << endl;
}

bool inRange(int row, int col) {
    bool t = ((row >= 0 && row < dim) && (col >= 0 && col < dim));
    //cout << row << " " << col << " " << t << endl;
    return t;
}

bool isGoodMove(int row, int col) {
    return (board[row][col] == 0 && inRange(row, col));
}

void move(int row, int col, int moveNum) {
    board[row][col] = moveNum;
    //cout << "moving " << moveNum << endl;
    if (moveNum == dim*dim) {
        displayBoard();
        exit(1);
    }
    for (int i=0; i<8; ++i) {
        int newRow = row + possibleMove[i].dR;
        int newCol = col + possibleMove[i].dC;
        //cout << row << " +" << possibleMove[i].dR << ", " << col << " +" << possibleMove[i].dC << endl;
        if (inRange(newRow, newCol)) {
            if (isGoodMove(newRow, newCol)) {
                //displayBoard();
                move(newRow,newCol,moveNum+1);
            }
        }
    }
    board[row][col] = 0;
}

int main() {
    move(0,0,1);
}