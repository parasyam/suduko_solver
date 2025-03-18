#include<bits/stdc++.h>
using namespace std;

class Sudoku {
    vector<vector<int>> grid;

public:
    Sudoku():grid(9,vector<int>(9,0)){}
    void inputGrid();
    void inputFromFile(const string& filename);
    bool isValidGrid();
    bool solve();
    bool isValid(int row,int col,int num);
    void printGrid();
};

void Sudoku::inputGrid() {
    cout<<"Enter the Sudoku grid (9x9) row by row, using 0 for empty cells:\n";
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            cin>>grid[i][j];
}

void Sudoku::inputFromFile(const string& filename) {
    ifstream file(filename);
    if(!file) {
        cout<<"Error: Could not open file "<<filename<<"\n";
        exit(1);
    }
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            file>>grid[i][j];
    file.close();
}

bool Sudoku::isValidGrid() {
    for(int i=0;i<9;i++) {
        vector<bool> rowCheck(10,false),colCheck(10,false);
        for(int j=0;j<9;j++) {
            if(grid[i][j]&&rowCheck[grid[i][j]]) return false;
            if(grid[j][i]&&colCheck[grid[j][i]]) return false;
            rowCheck[grid[i][j]]=colCheck[grid[j][i]]=true;
        }
    }
    return true;
}

bool Sudoku::isValid(int row,int col,int num) {
    for(int i=0;i<9;i++)
        if(grid[row][i]==num||grid[i][col]==num)
            return false;

    int startRow=row/3*3,startCol=col/3*3;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(grid[startRow+i][startCol+j]==num)
                return false;

    return true;
}

bool Sudoku::solve() {
    for(int row=0;row<9;row++) {
        for(int col=0;col<9;col++) {
            if(grid[row][col]==0) {
                for(int num=1;num<=9;num++) {
                    if(isValid(row,col,num)) {
                        grid[row][col]=num;
                        if(solve()) return true;
                        grid[row][col]=0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void Sudoku::printGrid() {
    cout<<"\n+-------+-------+-------+\n";
    for(int i=0;i<9;i++) {
        cout<<"| ";
        for(int j=0;j<9;j++) {
            cout<<grid[i][j]<<" ";
            if((j+1)%3==0) cout<<"| ";
        }
        cout<<"\n";
        if((i+1)%3==0) cout<<"+-------+-------+-------+\n";
    }
}

int main() {
    Sudoku sudoku;
    char choice;
    cout<<"Do you want to input from file (f) or manually (m)? ";
    cin>>choice;

    if(choice=='f') {
        string filename;
        cout<<"Enter filename: ";
        cin>>filename;
        sudoku.inputFromFile(filename);
    } else {
        sudoku.inputGrid();
    }

    if(!sudoku.isValidGrid()) {
        cout<<"Invalid Sudoku grid. Repeated numbers found in rows or columns.\n";
        return 1;
    }
    if(sudoku.solve()) {
        cout<<"Solved Sudoku:\n";
        sudoku.printGrid();
    } else {
        cout<<"No solution exists.\n";
    }
    return 0;
}
