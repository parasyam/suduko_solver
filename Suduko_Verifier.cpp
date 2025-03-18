#include<iostream>
#include<fstream>
#include<vector>
#include<bitset>
using namespace std;

class SudokuVerifier {
    vector<vector<int>> grid;

public:
    SudokuVerifier():grid(9,vector<int>(9,0)){}
    void inputGrid();
    void inputFromFile(const string& filename);
    bool isValidSudoku();
    void printGrid();
};

void SudokuVerifier::inputGrid() {
    cout<<"Enter the Sudoku grid (9x9) row by row, using '_' for empty cells:\n";
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++) {
            string val;
            cin>>val;
            grid[i][j] = (val == "_") ? 0 : stoi(val);
        }
}

void SudokuVerifier::inputFromFile(const string& filename) {
    ifstream file(filename);
    if(!file) {
        cout<<"Error: Could not open file "<<filename<<"\n";
        exit(1);
    }
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++) {
            string val;
            file>>val;
            grid[i][j] = (val == "_") ? 0 : stoi(val);
        }
    file.close();
}

bool SudokuVerifier::isValidSudoku() {
    vector<bitset<10>> rowMask(9), colMask(9), boxMask(9);

    for(int i=0;i<9;i++) {
        for(int j=0;j<9;j++) {
            int num = grid[i][j];
            if(num < 0 || num > 9) return false;
            if(num == 0) continue;

            int boxIdx = (i/3)*3 + (j/3);
            if(rowMask[i][num] || colMask[j][num] || boxMask[boxIdx][num])
                return false;

            rowMask[i].set(num);
            colMask[j].set(num);
            boxMask[boxIdx].set(num);
        }
    }
    return true;
}

void SudokuVerifier::printGrid() {
    cout<<"\n+-------+-------+-------+\n";
    for(int i=0;i<9;i++) {
        cout<<"| ";
        for(int j=0;j<9;j++) {
            if(grid[i][j] == 0)
                cout<<"_ ";
            else
                cout<<grid[i][j]<<" ";
            if((j+1)%3==0) cout<<"| ";
        }
        cout<<"\n";
        if((i+1)%3==0) cout<<"+-------+-------+-------+\n";
    }
}

int main() {
    SudokuVerifier verifier;
    char choice;
    cout<<"Do you want to input from file (f) or manually (m)? ";
    cin>>choice;

    if(choice=='f') {
        string filename;
        cout<<"Enter filename: ";
        cin>>filename;
        verifier.inputFromFile(filename);
    } else {
        verifier.inputGrid();
    }

    cout<<"Sudoku Grid:\n";
    verifier.printGrid();

    if(verifier.isValidSudoku()) 
        cout<<"Valid Sudoku Grid!\n";
    else 
        cout<<"Invalid Sudoku Grid!\n";

    return 0;
}
