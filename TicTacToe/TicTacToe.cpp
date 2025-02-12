#include <iostream>
#include <vector>
using namespace std;

string sqr = "|___|";
string X = "|_X_|";
string O = "|_O_|";
int play;
int cellNumber = 0;
int turn = 0;
vector<int> cellNums;
vector<int> playedMoves;
vector<string> cellMarks(9, sqr);

void table();
bool isValid();
bool validInput();
void print();
bool winLoseChecker();

int main()
{
    cout << "To play the game you need to understand how to input correctly \n";
    cout << "The table is drawn as \n";
    cout << "[1][2][3]\n";
    cout << "[4][5][6]\n";
    cout << "[7][8][9]\n";
    cout << "to play, you type in the number of cell you want to write in. X always starts first. Good luck and have fun.\n";
    while (turn < 9)
    {
        do
        {
            cout << "Pls put in a number to play\n";
            cin >> play;
        } while (!validInput());
        playedMoves.push_back(play);
        table();
        cellNums.clear();
        cellNumber = 0;
        turn++;
        if (winLoseChecker())
        {
            break;
        }
    }
    return 0;
}

void table()
{
    for (int i = 0; i < 3; i++)
    {

        for (int x = 0; x < 3; x++)
        {
            cellNumber++;
            cellNums.push_back(cellNumber);
            print();
        }
        cout << endl;
    }
}

bool isValid()
{
    for (int i = 0; i < cellNums.size(); ++i)
    {
        if (play == cellNums[i])
        {
            return true;
        }
    }
    return false;
}

bool validInput()
{
    for (int i = 0; i < playedMoves.size(); ++i)
    {
        if (play == playedMoves[i])
        {
            return false;
        }
    }
    return true;
}

void print()
{
    if (turn % 2 == 0)
    {
        if (isValid() && play == cellNumber)
        {
            cellMarks[play - 1] = X;
        }
    }
    else
    {
        if (isValid() && play == cellNumber)
        {
            cellMarks[play - 1] = O;
        }
    }
    cout << cellMarks[cellNumber - 1];
    return;
}

bool winLoseChecker()
{
    for (int i = 0; i < cellMarks.size(); i = i + 3)
    {
        if (cellMarks[i] == X && cellMarks[i + 1] == X && cellMarks[i + 2] == X)
        {
            cout << "X wins";
            return true;
        }
        else if (cellMarks[i] == O && cellMarks[i + 1] == O && cellMarks[i + 2] == O)
        {
            cout << "O wins";
            return true;
        }
    }
    for (int i = 0; i < cellMarks.size(); i++)
    {
        if (cellMarks[i] == X && cellMarks[i + 3] == X && cellMarks[i + 6] == X)
        {
            cout << "X wins";
            return true;
        }
        else if (cellMarks[i] == O && cellMarks[i + 3] == O && cellMarks[i + 6] == O)
        {
            cout << "O wins";
            return true;
        }
    }

    if (cellMarks[0] == O && cellMarks[4] == O && cellMarks[8] == O)
    {
        cout << "O wins";
        return true;
    }
    else if (cellMarks[0] == X && cellMarks[4] == X && cellMarks[8] == X)
    {
        cout << "X wins";
        return true;
    }
    else if (cellMarks[2] == O && cellMarks[4] == O && cellMarks[6] == O)
    {
        cout << "O wins";
        return true;
    }
    else if (cellMarks[2] == X && cellMarks[4] == X && cellMarks[6] == X)
    {
        cout << "X wins";
        return true;
    }
    return false;
}