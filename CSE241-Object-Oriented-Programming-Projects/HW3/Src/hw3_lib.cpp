#include "hw3_lib.h"


// ------------- CELL CLASS IMPLEMENTATIONS -------------

// Constructions for Cell class
PegSolitare::Cell::Cell(char clmValue, int rowValue, Cells cellTypeValue)
                       : clm(clmValue), row(rowValue), cellType(cellTypeValue)
{/*Body intentionally empty*/}
PegSolitare::Cell::Cell(void)
                       : row(0), clm('A'), cellType(Cells::emp)
{/*Body intentionally empty*/}

// Methods of Cell class
// Setter functions for position and cell type
void PegSolitare::Cell::set_position(char C, int R) {row = R; clm = C;}
void PegSolitare::Cell::set_position(char C) {clm = C;}
void PegSolitare::Cell::set_position(int R) {row = R;}
void PegSolitare::Cell::set_cellType(Cells cellTypeValue) {cellType = cellTypeValue;}

// Getter functions for position and cell type
int PegSolitare::Cell::get_row(void) const {return row;}
char PegSolitare::Cell::get_clm(void) const {return clm;}
Cells PegSolitare::Cell::get_cellType(void) const {return cellType;}

void PegSolitare::Cell::display_cell(void) const
{
    cout << get_clm() << get_row();
    cout << endl;
}

// ------------- Cell CLASS IMPLEMENTATIONS -------------

// ------------- PegSolitare CLASS IMPLEMENTATIONS -------------
// Constructions
// Default Constructor
PegSolitare::PegSolitare(void) 
{
    set_default_boards();
    set_defBoardSelection(false);
    set_fileBoardSelection(false);
}
// Constructor with parameter
PegSolitare::PegSolitare(int BT) 
{
    set_boardType(BT);
    set_default_boards();
    set_defBoardSelection(true);
    set_fileBoardSelection(false);
}

PegSolitare::PegSolitare(string fileName)
{
    set_default_boards();
    load_board(fileName);
}


// Member functions definations
void PegSolitare::input_boardType(void)
{
    int BT;
    cout << endl << "Enter the board type:  ";
    cin >> BT;
    set_boardType(BT);
}

void PegSolitare::set_boardType(int BT)
{
    boardType = BT;
    if (boardType < 1 || boardType > 6)
    {
        cerr << endl << "Invalid board type. Program terminated." << endl;
        exit(1);
    }
    set_defBoardSelection(true);
    set_fileBoardSelection(false);
}

void PegSolitare::set_currentCell(char clmValue, int rowValue, Cells cellTypeValue)
{
    currentCell = PegSolitare::Cell(clmValue, rowValue, cellTypeValue);
}

void PegSolitare::display_currentCell(void) const
{
    currentCell.display_cell();
}

void PegSolitare::set_default_boards(void)
{
    vector<vector<Cell>> Board1 = 
    {
        {Cell('A', 1, Cells::wal), Cell('B', 1, Cells::wal), Cell('C', 1, Cells::peg), Cell('D', 1, Cells::peg), Cell('E', 1, Cells::peg), Cell('F', 1, Cells::wal), Cell('G', 1, Cells::wal)},
        {Cell('A', 2, Cells::wal), Cell('B', 2, Cells::peg), Cell('C', 2, Cells::peg), Cell('D', 2, Cells::peg), Cell('E', 2, Cells::peg), Cell('F', 2, Cells::peg), Cell('G', 2, Cells::wal)},
        {Cell('A', 3, Cells::peg), Cell('B', 3, Cells::peg), Cell('C', 3, Cells::peg), Cell('D', 3, Cells::emp), Cell('E', 3, Cells::peg), Cell('F', 3, Cells::peg), Cell('G', 3, Cells::peg)},
        {Cell('A', 4, Cells::peg), Cell('B', 4, Cells::peg), Cell('C', 4, Cells::peg), Cell('D', 4, Cells::peg), Cell('E', 4, Cells::peg), Cell('F', 4, Cells::peg), Cell('G', 4, Cells::peg)},
        {Cell('A', 5, Cells::peg), Cell('B', 5, Cells::peg), Cell('C', 5, Cells::peg), Cell('D', 5, Cells::peg), Cell('E', 5, Cells::peg), Cell('F', 5, Cells::peg), Cell('G', 5, Cells::peg)},
        {Cell('A', 6, Cells::wal), Cell('B', 6, Cells::peg), Cell('C', 6, Cells::peg), Cell('D', 6, Cells::peg), Cell('E', 6, Cells::peg), Cell('F', 6, Cells::peg), Cell('G', 6, Cells::wal)},
        {Cell('A', 7, Cells::wal), Cell('B', 7, Cells::wal), Cell('C', 7, Cells::peg), Cell('D', 7, Cells::peg), Cell('E', 7, Cells::peg), Cell('F', 7, Cells::wal), Cell('G', 7, Cells::wal)}
    };
    vector<vector<Cell>> Board2 = 
    {
        {Cell('A', 1, Cells::wal), Cell('B', 1, Cells::wal), Cell('C', 1, Cells::wal), Cell('D', 1, Cells::peg), Cell('E', 1, Cells::peg), Cell('F', 1, Cells::peg), Cell('G', 1, Cells::wal), Cell('H', 1, Cells::wal), Cell('I', 1, Cells::wal)},
        {Cell('A', 2, Cells::wal), Cell('B', 2, Cells::wal), Cell('C', 2, Cells::wal), Cell('D', 2, Cells::peg), Cell('E', 2, Cells::peg), Cell('F', 2, Cells::peg), Cell('G', 2, Cells::wal), Cell('H', 2, Cells::wal), Cell('I', 2, Cells::wal)},
        {Cell('A', 3, Cells::wal), Cell('B', 3, Cells::wal), Cell('C', 3, Cells::wal), Cell('D', 3, Cells::peg), Cell('E', 3, Cells::peg), Cell('F', 3, Cells::peg), Cell('G', 3, Cells::wal), Cell('H', 3, Cells::wal), Cell('I', 3, Cells::wal)},
        {Cell('A', 4, Cells::peg), Cell('B', 4, Cells::peg), Cell('C', 4, Cells::peg), Cell('D', 4, Cells::peg), Cell('E', 4, Cells::peg), Cell('F', 4, Cells::peg), Cell('G', 4, Cells::peg), Cell('H', 4, Cells::peg), Cell('I', 4, Cells::peg)},
        {Cell('A', 5, Cells::peg), Cell('B', 5, Cells::peg), Cell('C', 5, Cells::peg), Cell('D', 5, Cells::peg), Cell('E', 5, Cells::emp), Cell('F', 5, Cells::peg), Cell('G', 5, Cells::peg), Cell('H', 5, Cells::peg), Cell('I', 5, Cells::peg)},
        {Cell('A', 6, Cells::peg), Cell('B', 6, Cells::peg), Cell('C', 6, Cells::peg), Cell('D', 6, Cells::peg), Cell('E', 6, Cells::peg), Cell('F', 6, Cells::peg), Cell('G', 6, Cells::peg), Cell('H', 6, Cells::peg), Cell('I', 6, Cells::peg)},
        {Cell('A', 7, Cells::wal), Cell('B', 7, Cells::wal), Cell('C', 7, Cells::wal), Cell('D', 7, Cells::peg), Cell('E', 7, Cells::peg), Cell('F', 7, Cells::peg), Cell('G', 7, Cells::wal), Cell('H', 7, Cells::wal), Cell('I', 7, Cells::wal)},
        {Cell('A', 8, Cells::wal), Cell('B', 8, Cells::wal), Cell('C', 8, Cells::wal), Cell('D', 8, Cells::peg), Cell('E', 8, Cells::peg), Cell('F', 8, Cells::peg), Cell('G', 8, Cells::wal), Cell('H', 8, Cells::wal), Cell('I', 8, Cells::wal)},
        {Cell('A', 9, Cells::wal), Cell('B', 9, Cells::wal), Cell('C', 9, Cells::wal), Cell('D', 9, Cells::peg), Cell('E', 9, Cells::peg), Cell('F', 9, Cells::peg), Cell('G', 9, Cells::wal), Cell('H', 9, Cells::wal), Cell('I', 9, Cells::wal)}
    };
    vector<vector<Cell>> Board3 = 
    {
        {Cell('A', 1, Cells::wal), Cell('B', 1, Cells::wal), Cell('C', 1, Cells::peg), Cell('D', 1, Cells::peg), Cell('E', 1, Cells::peg), Cell('F', 1, Cells::wal), Cell('G', 1, Cells::wal), Cell('H', 1, Cells::wal)},
        {Cell('A', 2, Cells::wal), Cell('B', 2, Cells::wal), Cell('C', 2, Cells::peg), Cell('D', 2, Cells::peg), Cell('E', 2, Cells::peg), Cell('F', 2, Cells::wal), Cell('G', 2, Cells::wal), Cell('H', 2, Cells::wal)},
        {Cell('A', 3, Cells::wal), Cell('B', 3, Cells::wal), Cell('C', 3, Cells::peg), Cell('D', 3, Cells::peg), Cell('E', 3, Cells::peg), Cell('F', 3, Cells::wal), Cell('G', 3, Cells::wal), Cell('H', 3, Cells::wal)},
        {Cell('A', 4, Cells::peg), Cell('B', 4, Cells::peg), Cell('C', 4, Cells::peg), Cell('D', 4, Cells::peg), Cell('E', 4, Cells::peg), Cell('F', 4, Cells::peg), Cell('G', 4, Cells::peg), Cell('H', 4, Cells::peg)},
        {Cell('A', 5, Cells::peg), Cell('B', 5, Cells::peg), Cell('C', 5, Cells::peg), Cell('D', 5, Cells::emp), Cell('E', 5, Cells::peg), Cell('F', 5, Cells::peg), Cell('G', 5, Cells::peg), Cell('H', 5, Cells::peg)},
        {Cell('A', 6, Cells::peg), Cell('B', 6, Cells::peg), Cell('C', 6, Cells::peg), Cell('D', 6, Cells::peg), Cell('E', 6, Cells::peg), Cell('F', 6, Cells::peg), Cell('G', 6, Cells::peg), Cell('H', 6, Cells::peg)},
        {Cell('A', 7, Cells::wal), Cell('B', 7, Cells::wal), Cell('C', 7, Cells::peg), Cell('D', 7, Cells::peg), Cell('E', 7, Cells::peg), Cell('F', 7, Cells::wal), Cell('G', 7, Cells::wal), Cell('H', 7, Cells::wal)},
        {Cell('A', 8, Cells::wal), Cell('B', 8, Cells::wal), Cell('C', 8, Cells::peg), Cell('D', 8, Cells::peg), Cell('E', 8, Cells::peg), Cell('F', 8, Cells::wal), Cell('G', 8, Cells::wal), Cell('H', 8, Cells::wal)}
    };
    vector<vector<Cell>> Board4 = 
    {
        {Cell('A', 1, Cells::wal), Cell('B', 1, Cells::wal), Cell('C', 1, Cells::peg), Cell('D', 1, Cells::peg), Cell('E', 1, Cells::peg), Cell('F', 1, Cells::wal), Cell('G', 1, Cells::wal)},
        {Cell('A', 2, Cells::wal), Cell('B', 2, Cells::wal), Cell('C', 2, Cells::peg), Cell('D', 2, Cells::peg), Cell('E', 2, Cells::peg), Cell('F', 2, Cells::wal), Cell('G', 2, Cells::wal)},
        {Cell('A', 3, Cells::peg), Cell('B', 3, Cells::peg), Cell('C', 3, Cells::peg), Cell('D', 3, Cells::peg), Cell('E', 3, Cells::peg), Cell('F', 3, Cells::peg), Cell('G', 3, Cells::peg)},
        {Cell('A', 4, Cells::peg), Cell('B', 4, Cells::peg), Cell('C', 4, Cells::peg), Cell('D', 4, Cells::emp), Cell('E', 4, Cells::peg), Cell('F', 4, Cells::peg), Cell('G', 4, Cells::peg)},
        {Cell('A', 5, Cells::peg), Cell('B', 5, Cells::peg), Cell('C', 5, Cells::peg), Cell('D', 5, Cells::peg), Cell('E', 5, Cells::peg), Cell('F', 5, Cells::peg), Cell('G', 5, Cells::peg)},
        {Cell('A', 6, Cells::wal), Cell('B', 6, Cells::wal), Cell('C', 6, Cells::peg), Cell('D', 6, Cells::peg), Cell('E', 6, Cells::peg), Cell('F', 6, Cells::wal), Cell('G', 6, Cells::wal)},
        {Cell('A', 7, Cells::wal), Cell('B', 7, Cells::wal), Cell('C', 7, Cells::peg), Cell('D', 7, Cells::peg), Cell('E', 7, Cells::peg), Cell('F', 7, Cells::wal), Cell('G', 7, Cells::wal)}
    };
    vector<vector<Cell>> Board5 = 
    {
        {Cell('A', 1, Cells::wal), Cell('B', 1, Cells::wal), Cell('C', 1, Cells::wal), Cell('D', 1, Cells::wal), Cell('E', 1, Cells::peg), Cell('F', 1, Cells::wal), Cell('G', 1, Cells::wal), Cell('H', 1, Cells::wal), Cell('I', 1, Cells::wal)},
        {Cell('A', 2, Cells::wal), Cell('B', 2, Cells::wal), Cell('C', 2, Cells::wal), Cell('D', 2, Cells::peg), Cell('E', 2, Cells::peg), Cell('F', 2, Cells::peg), Cell('G', 2, Cells::wal), Cell('H', 2, Cells::wal), Cell('I', 2, Cells::wal)},
        {Cell('A', 3, Cells::wal), Cell('B', 3, Cells::wal), Cell('C', 3, Cells::peg), Cell('D', 3, Cells::peg), Cell('E', 3, Cells::peg), Cell('F', 3, Cells::peg), Cell('G', 3, Cells::peg), Cell('H', 3, Cells::wal), Cell('I', 3, Cells::wal)},
        {Cell('A', 4, Cells::wal), Cell('B', 4, Cells::peg), Cell('C', 4, Cells::peg), Cell('D', 4, Cells::peg), Cell('E', 4, Cells::peg), Cell('F', 4, Cells::peg), Cell('G', 4, Cells::peg), Cell('H', 4, Cells::peg), Cell('I', 4, Cells::wal)},
        {Cell('A', 5, Cells::peg), Cell('B', 5, Cells::peg), Cell('C', 5, Cells::peg), Cell('D', 5, Cells::peg), Cell('E', 5, Cells::emp), Cell('F', 5, Cells::peg), Cell('G', 5, Cells::peg), Cell('H', 5, Cells::peg), Cell('I', 5, Cells::peg)},
        {Cell('A', 6, Cells::wal), Cell('B', 6, Cells::peg), Cell('C', 6, Cells::peg), Cell('D', 6, Cells::peg), Cell('E', 6, Cells::peg), Cell('F', 6, Cells::peg), Cell('G', 6, Cells::peg), Cell('H', 6, Cells::peg), Cell('I', 6, Cells::wal)},
        {Cell('A', 7, Cells::wal), Cell('B', 7, Cells::wal), Cell('C', 7, Cells::peg), Cell('D', 7, Cells::peg), Cell('E', 7, Cells::peg), Cell('F', 7, Cells::peg), Cell('G', 7, Cells::peg), Cell('H', 7, Cells::wal), Cell('I', 7, Cells::wal)},
        {Cell('A', 8, Cells::wal), Cell('B', 8, Cells::wal), Cell('C', 8, Cells::wal), Cell('D', 8, Cells::peg), Cell('E', 8, Cells::peg), Cell('F', 8, Cells::peg), Cell('G', 8, Cells::wal), Cell('H', 8, Cells::wal), Cell('I', 8, Cells::wal)},
        {Cell('A', 9, Cells::wal), Cell('B', 9, Cells::wal), Cell('C', 9, Cells::wal), Cell('D', 9, Cells::wal), Cell('E', 9, Cells::peg), Cell('F', 9, Cells::wal), Cell('G', 9, Cells::wal), Cell('H', 9, Cells::wal), Cell('I', 9, Cells::wal)}
    };
    vector<vector<Cell>> Board6 = 
    {
        {Cell('A', 1, Cells::wal), Cell('B', 1, Cells::wal), Cell('C', 1, Cells::wal), Cell('D', 1, Cells::wal), Cell('E', 1, Cells::emp), Cell('F', 1, Cells::wal), Cell('G', 1, Cells::wal), Cell('H', 1, Cells::wal), Cell('I', 1, Cells::wal)},
        {Cell('A', 2, Cells::wal), Cell('B', 2, Cells::wal), Cell('C', 2, Cells::wal), Cell('D', 2, Cells::peg), Cell('E', 2, Cells::wal), Cell('F', 2, Cells::peg), Cell('G', 2, Cells::wal), Cell('H', 2, Cells::wal), Cell('I', 2, Cells::wal)},
        {Cell('A', 3, Cells::wal), Cell('B', 3, Cells::wal), Cell('C', 3, Cells::peg), Cell('D', 3, Cells::wal), Cell('E', 3, Cells::peg), Cell('F', 3, Cells::wal), Cell('G', 3, Cells::peg), Cell('H', 3, Cells::wal), Cell('I', 3, Cells::wal)},
        {Cell('A', 4, Cells::wal), Cell('B', 4, Cells::peg), Cell('C', 4, Cells::wal), Cell('D', 4, Cells::peg), Cell('E', 4, Cells::wal), Cell('F', 4, Cells::peg), Cell('G', 4, Cells::wal), Cell('H', 4, Cells::peg), Cell('I', 4, Cells::wal)},
        {Cell('A', 5, Cells::peg), Cell('B', 5, Cells::wal), Cell('C', 5, Cells::peg), Cell('D', 5, Cells::wal), Cell('E', 5, Cells::peg), Cell('F', 5, Cells::wal), Cell('G', 5, Cells::peg), Cell('H', 5, Cells::wal), Cell('I', 5, Cells::peg)}
    };

    defBoards.push_back(Board1);
    defBoards.push_back(Board2);
    defBoards.push_back(Board3);
    defBoards.push_back(Board4);
    defBoards.push_back(Board5);
    defBoards.push_back(Board6);
}

void PegSolitare::display_defBoards(void) const
{
    int row, clm;
    char label = 'A';
    cout << endl;
    

    for(int k = 0; k < 6; k++)
    {
        if      (k == 0){row = B1size; clm = B1size;}
        else if (k == 1){row = B2size; clm = B2size;}
        else if (k == 2){row = B3size; clm = B3size;}
        else if (k == 3){row = B4size; clm = B4size;}
        else if (k == 4){row = B5size; clm = B5size;}
        else if (k == 5){row = B6row; clm = B6clm;}
        
        cout << k + 1 << "-)" << endl;
        cout << "      ";
        for (int i = 0; i < clm; i++, label++)
            cout << label << " ";

        cout << endl << endl;


        for (int i = 0; i < row; i++)
        {
            cout << i + 1 << "     ";
            for (int j = 0; j < clm; j++)
            {
                if (defBoards[k][i][j].get_cellType() == Cells::peg)
                    cout << 'o' << ' ';
                else if (defBoards[k][i][j].get_cellType() == Cells::emp)
                    cout << ' ' << ' ';
                else if (defBoards[k][i][j].get_cellType() == Cells::wal)
                    cout << '.' << ' ';
            }
            cout << endl;
        }
        cout << endl << endl;
        label = 'A';
    }
}

void PegSolitare::lead_game(void)
{
    string opr;
    int sel;

    // If there is not any selected board then lead the game.
    // This mean if a game doesn't start with a constructor with a initiliazed board.
    if (get_defBoardSelection() == false && get_fileBoardSelection() == false)
    {
        // Ask user to select a board or turn back to the menu.
        do
        {
            opr.clear();
            cout << endl << "--> Enter 1 to 6 play with one of the default boards." << endl;
            cout << "(To play board from the file, enter \"LOAD filename.txt\")" << endl;
            getline(cin, opr);
            
            if (opr.compare("1") == 0)
            {
                set_boardType(1);
                set_defBoardSelection(true);
                set_fileBoardSelection(false);
                break;
            }
            else if (opr.compare("2") == 0)
            {
                set_boardType(2);
                set_defBoardSelection(true);
                set_fileBoardSelection(false);
                break;
            }
            else if (opr.compare("3") == 0)
            {
                set_boardType(3);
                set_defBoardSelection(true);
                set_fileBoardSelection(false);
                break;
            }
            else if (opr.compare("4") == 0)
            {
                set_boardType(4);
                set_defBoardSelection(true);
                set_fileBoardSelection(false);
                break;
            }
            else if (opr.compare("5") == 0)
            {
                set_boardType(5);
                set_defBoardSelection(true);
                set_fileBoardSelection(false);
                break;
            }
            else if (opr.compare("6") == 0)
            {
                set_boardType(6);
                set_defBoardSelection(true);
                set_fileBoardSelection(false);
                break;
            } 
            else if (opr.compare(0, 4, "LOAD") == 0)
            {
                load_board(opr.substr(5));
                break;
            }
            else if (opr.compare("-1") == 0)
            {
                cout << endl << "__You have returned to the top menu. (to view menu enter '8')" << endl;
            }
            else
            {
                cerr << endl << "Invalid entry. Try again (to exit '-1')" << endl;
            }
            
        } while (opr.compare("-1") != 0);

    }
    // If a board is selected, then call the playing function.
    if (get_defBoardSelection() == true)
    {
        cout << endl << "Board number " << get_boardType() << " is selected." << endl;
        cout << "---------------------------" << endl;
        display_currentBoard(defBoards[get_boardType() - 1]);
        playing();
    }
    else if (get_fileBoardSelection() == true)
    {       
        cout << endl << "Board loaded from file." << endl;
        cout << "---------------------" << endl;
        display_currentBoard(fileBoard);
        playing();
    }
}
// Until user wants to leave, he/she plays a board.
// User can change board, save board, play randomly until the game is over
void PegSolitare::playing()
{
    string opr;
    
    game_instructions();
    do
    {
        opr.clear();
        cout << "Please enter the operation you want to do: " << endl;
        cout << "(To view instructions enter '0')" << endl;
        getline(cin, opr);
        
        // If user wants to change the board, then changes.
        // He/she can play by enter the coordinates and direction.
        // He/she can make a random move or rules computer to play until game is tied.
        if (opr.compare("-1") == 0)
        {
            cout << endl << "__The game has been closed. You have been redirected to the menu." << endl;
            cout << "(To view menu enter '8')" << endl << endl;
        }
        else if(opr.compare("0") == 0)
        {
            game_instructions();
        }
        else if(opr.compare("1") == 0)
        {
            set_boardType(1);
            set_defBoardSelection(true);
            set_fileBoardSelection(false);
            cout << endl << "Board number " << get_boardType() << " is selected." << endl;
            cout << "---------------------------" << endl;
            display_currentBoard(defBoards[get_boardType() - 1]);
        }
        else if(opr.compare("2") == 0)
        {
            set_boardType(2);
            set_defBoardSelection(true);
            set_fileBoardSelection(false);
            cout << endl << "Board number " << get_boardType() << " is selected." << endl;
            cout << "---------------------------" << endl;
            display_currentBoard(defBoards[get_boardType() - 1]);
        }
        else if(opr.compare("3") == 0)
        {
            set_boardType(3);
            set_defBoardSelection(true);
            set_fileBoardSelection(false);
            cout << endl << "Board number " << get_boardType() << " is selected." << endl;
            cout << "---------------------------" << endl;
            display_currentBoard(defBoards[get_boardType() - 1]);
        }
        else if(opr.compare("4") == 0)
        {
            set_boardType(4);
            set_defBoardSelection(true);
            set_fileBoardSelection(false);
            cout << endl << "Board number " << get_boardType() << " is selected." << endl;
            cout << "---------------------------" << endl;
            display_currentBoard(defBoards[get_boardType() - 1]);
        }
        else if(opr.compare("5") == 0)
        {
            set_boardType(5);
            set_defBoardSelection(true);
            set_fileBoardSelection(false);
            cout << endl << "Board number " << get_boardType() << " is selected." << endl;
            cout << "---------------------------" << endl;
            display_currentBoard(defBoards[get_boardType() - 1]);
        }
        else if(opr.compare("6") == 0)
        {
            set_boardType(6);
            set_defBoardSelection(true);
            set_fileBoardSelection(false);
            cout << endl << "Board number " << get_boardType() << " is selected." << endl;
            cout << "---------------------------" << endl;
            display_currentBoard(defBoards[get_boardType() - 1]);
        }
        else if (opr.compare(0, 4, "LOAD") == 0)
        {
            load_board(opr.substr(5));
            cout << endl << "Board loaded from " << opr.substr(5) << endl;
            cout << "---------------------------" << endl;
            display_currentBoard(fileBoard);
        }
        else if (opr.compare(0, 4, "SAVE") == 0)
        {
            save_board(opr.substr(5));
            cout << endl << "Board saved to file " << opr.substr(5) << endl << endl;
        }
        else if (opr.compare("R") == 0)
        {
            play();
        }
        else if (opr.compare("P") == 0 && get_defBoardSelection())
        {
            playGame(defBoards[get_boardType() - 1]);
        }
        else if (opr.compare("P") == 0 && get_fileBoardSelection())
        {
            playGame(fileBoard);
        }
        else if (move_validitiy(opr) == true)
        {
            play(opr);
        }
        else if (get_defBoardSelection() == true && is_board_tied(defBoards[get_boardType() - 1]))
        {
            cout << endl << "Game over.";
            cout << endl << "Board is tied! Please change the board or the game." << endl << endl;
        }
        else if (get_fileBoardSelection() == true && is_board_tied(fileBoard))
        {
            display_currentBoard(fileBoard);
            cout << endl << "Board is tied! Please change the board or the game." << endl << endl;
        }
        else
        {
            cerr << endl << "Invalid entry. Try again." << endl << endl;
        }
    } while (opr.compare("-1") != 0);
    
}

// ---- Other helper member functions of PegSolitare Class ----
void PegSolitare::display_currentBoard(const vector<vector<Cell>>& Board) const
{
    char label = 'A';

    cout << endl << endl;
    cout << "      ";
    
    for (int i = 0; i < Board[0].size(); i++, label++)
        cout << label << " ";

    cout << endl << endl;


    for (int i = 0; i < Board.size(); i++)
    {
        cout << i + 1 << "     ";
        for (int j = 0; j < Board[i].size(); j++)
        {
            if (Board[i][j].get_cellType() == Cells::peg)
                cout << 'o' << ' ';
            else if (Board[i][j].get_cellType() == Cells::emp)
                cout << ' ' << ' ';
            else if (Board[i][j].get_cellType() == Cells::wal)
                cout << '.' << ' ';
        }
        cout << endl;
    }
    cout << endl << endl;
}

void PegSolitare::game_instructions(void) const
{
    cout << endl << "Game Instruction: " << endl;
    cout << "-----------------" << endl << endl;
    cout << " 1- To make a move enter coordinate then the direction. (eg: B4-U)" << endl;
    cout << " 2- To make a random move enter 'R'."  << endl;
    cout << " 3- To play the game to the computer, enter 'P'. (playGame function)" << endl;
    cout << " 4- To save game into a file enter 'SAVE filename.txt'" << endl;
    cout << " 5- To change default board enter '1 to 6'." << endl;
    cout << " 6- To load a board from file type 'LOAD filename.txt'." << endl;
    cout << " 7- To back the menu enter '-1'." << endl << endl;
}

bool PegSolitare::move_validitiy(const string &Move) const
{
    int i, j;
    char dir;
    i = Move[1] - '1';
    j = Move[0] - 'A';
    dir = Move[3];

    if (!(dir == 'U' || dir == 'D' || dir == 'L' || dir == 'R'))
    {
        return false;
    }

    if (get_defBoardSelection() == true)
    {
        if (get_boardType() != 6)
        {
            switch (dir)
            {
            case 'L':
                if ((j - 2) >= 0 && 
                    defBoards[get_boardType() - 1][i][j].get_cellType() == Cells::peg &&
                    defBoards[get_boardType() - 1][i][j - 1].get_cellType() == Cells::peg &&
                    defBoards[get_boardType() - 1][i][j - 2].get_cellType() == Cells::emp)
                {
                    return true;
                }
                break;
            case 'R':
                if ((j + 2) < defBoards[get_boardType() - 1][0].size() &&
                    defBoards[get_boardType() - 1][i][j].get_cellType() == Cells::peg &&
                    defBoards[get_boardType() - 1][i][j + 1].get_cellType() == Cells::peg &&
                    defBoards[get_boardType() - 1][i][j + 2].get_cellType() == Cells::emp)
                {
                    return true;
                }
                break;
            case 'U':
                if ((i - 2) >= 0 &&
                    defBoards[get_boardType() - 1][i][j].get_cellType() == Cells::peg &&
                    defBoards[get_boardType() - 1][i - 1][j].get_cellType() == Cells::peg &&
                    defBoards[get_boardType() - 1][i - 2][j].get_cellType() == Cells::emp)
                {
                    return true;
                }
                break;
            case 'D':
                if ((i + 2) < defBoards[get_boardType() - 1].size() &&
                    defBoards[get_boardType() - 1][i][j].get_cellType() == Cells::peg &&
                    defBoards[get_boardType() - 1][i + 1][j].get_cellType() == Cells::peg &&
                    defBoards[get_boardType() - 1][i + 2][j].get_cellType() == Cells::emp)
                {
                    return true;
                }
                break;
            }
        }
        else if (get_boardType() == 6)
        {
            switch (dir)
            {
            case 'L':
                if ((j - 4) >= 0 &&
                    defBoards[get_boardType() - 1][i][j].get_cellType() == Cells::peg &&
                    defBoards[get_boardType() - 1][i][j - 2].get_cellType() == Cells::peg &&
                    defBoards[get_boardType() - 1][i][j - 4].get_cellType() == Cells::emp)
                {
                    return true;
                }
                break;
            case 'R':
                if ((j + 4) < defBoards[get_boardType() - 1][0].size() &&
                    defBoards[get_boardType() - 1][i][j].get_cellType() == Cells::peg &&
                    defBoards[get_boardType() - 1][i][j + 2].get_cellType() == Cells::peg &&
                    defBoards[get_boardType() - 1][i][j + 4].get_cellType() == Cells::emp)
                {
                    return true;
                }
                break;
            case 'U':
                if ((i - 2) >= 0 && (j - 2) >= 0 &&
                    defBoards[get_boardType() - 1][i][j].get_cellType() == Cells::peg &&
                    defBoards[get_boardType() - 1][i - 1][j - 1].get_cellType() == Cells::peg &&
                    defBoards[get_boardType() - 1][i - 2][j - 2].get_cellType() == Cells::emp)
                {
                    return true;
                }
                break;
            case 'D':
                if ((i + 2) < defBoards[get_boardType() - 1].size() && (j - 2) >= 0 && 
                    defBoards[get_boardType() - 1][i][j].get_cellType() == Cells::peg &&
                    defBoards[get_boardType() - 1][i + 1][j - 1].get_cellType() == Cells::peg &&
                    defBoards[get_boardType() - 1][i + 2][j - 2].get_cellType() == Cells::emp)
                {
                    return true;
                }
                break;
            }
        }
    }
    else if (get_fileBoardSelection() == true)
    {
        switch (dir)
        {
        case 'L':
            if ((j - 2) >= 0 && 
                fileBoard[i][j].get_cellType() == Cells::peg &&
                fileBoard[i][j - 1].get_cellType() == Cells::peg &&
                fileBoard[i][j - 2].get_cellType() == Cells::emp)
            {
                return true;
            }
            break;
        case 'R':
            if ((j + 2) < fileBoard.size() &&
                fileBoard[i][j].get_cellType() == Cells::peg &&
                fileBoard[i][j + 1].get_cellType() == Cells::peg &&
                fileBoard[i][j + 2].get_cellType() == Cells::emp)
            {
                return true;
            }
            break;
        case 'U':
            if ((i - 2) >= 0 &&
                fileBoard[i][j].get_cellType() == Cells::peg &&
                fileBoard[i - 1][j].get_cellType() == Cells::peg &&
                fileBoard[i - 2][j].get_cellType() == Cells::emp)
            {
                return true;
            }
            break;
        case 'D':
            if ((i + 2) < fileBoard.size() &&
                fileBoard[i][j].get_cellType() == Cells::peg &&
                fileBoard[i + 1][j].get_cellType() == Cells::peg &&
                fileBoard[i + 2][j].get_cellType() == Cells::emp)
            {
                return true;
            }
            break;
        }    
    }
    return false;
}

bool PegSolitare::is_board_tied(const vector<vector<Cell>> &Board)
{
    if ((get_boardType() != 6 && get_defBoardSelection() == true) || get_fileBoardSelection() == true)
    {
        for (int i = 0; i < Board.size(); i++)
        {
            for (int j = 0; j < Board[0].size(); j++)
            {
                if(Board[i][j].get_cellType() == Cells::peg)
                {
                    if((j + 2) < Board[0].size() && Board[i][j + 1].get_cellType() == Cells::peg 
                                                 && Board[i][j + 2].get_cellType() == Cells::emp)
                    {
                        return false;
                    }
                    else if((i + 2) < Board.size() && Board[i + 1][j].get_cellType() == Cells::peg 
                                                   && Board[i + 2][j].get_cellType() == Cells::emp)
                    {
                        return false;
                    }
                    else if((j - 2) >= 0 && Board[i][j - 1].get_cellType() == Cells::peg 
                                         && Board[i][j - 2].get_cellType() == Cells::emp)
                    {
                        return false;
                    }
                    else if((i - 2) >= 0 && Board[i - 1][j].get_cellType() == Cells::peg 
                                         && Board[i - 2][j].get_cellType() == Cells::emp)
                    {
                        return false;
                    }
                }
            }
        }
    }
    else if (get_boardType() == 6 && get_defBoardSelection() == true)
    {
        for (int i = 0; i < Board.size(); i++)
        {
            for (int j = 0; j < Board[0].size(); j++)
            {
                if(Board[i][j].get_cellType() == Cells::peg)
                {
                    if((j + 4) < Board[0].size() && Board[i][j + 2].get_cellType() == Cells::peg 
                                                 && Board[i][j + 4].get_cellType() == Cells::emp)
                    {
                        return false;
                    }
                    else if((i + 2) < Board.size() && (j - 2) >= 0 && 
                            Board[i + 1][j - 1].get_cellType() == Cells::peg && Board[i + 2][j - 2].get_cellType() == Cells::emp)
                    {
                        return false;
                    }
                    else if((j - 4) >= 0 && Board[i][j - 2].get_cellType() == Cells::peg 
                                         && Board[i][j - 4].get_cellType() == Cells::emp)
                    {
                        return false;
                    }
                    else if((i - 2) >= 0 && (j - 2) >= 0 && Board[i - 1][j - 1].get_cellType() == Cells::peg 
                                                         && Board[i - 2][j - 2].get_cellType() == Cells::emp)
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

// Makes a move according to the validity which taken coordinates from user.
void PegSolitare::play(const string& Move)
{
    int i, j;
    char dir;

    i = Move[1] - '1';
    j = Move[0] - 'A';
    dir = Move[3];

    if (get_defBoardSelection() == true)
    {
        if (get_boardType() != 6)
        {
            switch (dir)
            {
            case 'L':
                defBoards[get_boardType() - 1][i][j].set_cellType(Cells::emp);
                defBoards[get_boardType() - 1][i][j - 1].set_cellType(Cells::emp);
                defBoards[get_boardType() - 1][i][j - 2].set_cellType(Cells::peg);
                break;
            case 'R':
                defBoards[get_boardType() - 1][i][j].set_cellType(Cells::emp);
                defBoards[get_boardType() - 1][i][j + 1].set_cellType(Cells::emp);
                defBoards[get_boardType() - 1][i][j + 2].set_cellType(Cells::peg);
                break;
            case 'U':
                defBoards[get_boardType() - 1][i][j].set_cellType(Cells::emp);
                defBoards[get_boardType() - 1][i - 1][j].set_cellType(Cells::emp);
                defBoards[get_boardType() - 1][i - 2][j].set_cellType(Cells::peg);
                break;
            case 'D':
                defBoards[get_boardType() - 1][i][j].set_cellType(Cells::emp);    
                defBoards[get_boardType() - 1][i + 1][j].set_cellType(Cells::emp);            
                defBoards[get_boardType() - 1][i + 2][j].set_cellType(Cells::peg);
                break;
            }
        }
        else if (get_boardType() == 6)
        {
            switch (dir)
            {
            case 'L':
                defBoards[get_boardType() - 1][i][j].set_cellType(Cells::emp);
                defBoards[get_boardType() - 1][i][j - 2].set_cellType(Cells::emp);
                defBoards[get_boardType() - 1][i][j - 4].set_cellType(Cells::peg);
                break;
            case 'R':
                defBoards[get_boardType() - 1][i][j].set_cellType(Cells::emp);
                defBoards[get_boardType() - 1][i][j + 2].set_cellType(Cells::emp);
                defBoards[get_boardType() - 1][i][j + 4].set_cellType(Cells::peg);
                break;
            case 'U':
                defBoards[get_boardType() - 1][i][j].set_cellType(Cells::emp);
                defBoards[get_boardType() - 1][i - 1][j - 1].set_cellType(Cells::emp);
                defBoards[get_boardType() - 1][i - 2][j - 2].set_cellType(Cells::peg);
                break;
            case 'D':
                defBoards[get_boardType() - 1][i][j].set_cellType(Cells::emp);    
                defBoards[get_boardType() - 1][i + 1][j - 1].set_cellType(Cells::emp);            
                defBoards[get_boardType() - 1][i + 2][j - 2].set_cellType(Cells::peg);
                break;
            }
        }
        display_currentBoard(defBoards[get_boardType() - 1]);
    }
    else if (get_fileBoardSelection() == true)
    {
        switch (dir)
        {
        case 'L':
            fileBoard[i][j].set_cellType(Cells::emp);
            fileBoard[i][j - 1].set_cellType(Cells::emp);
            fileBoard[i][j - 2].set_cellType(Cells::peg);
            break;
        case 'R':
            fileBoard[i][j].set_cellType(Cells::emp);
            fileBoard[i][j + 1].set_cellType(Cells::emp);
            fileBoard[i][j + 2].set_cellType(Cells::peg);
            break;
        case 'U':
            fileBoard[i][j].set_cellType(Cells::emp);
            fileBoard[i - 1][j].set_cellType(Cells::emp);
            fileBoard[i - 2][j].set_cellType(Cells::peg);
            break;
        case 'D':
            fileBoard[i][j].set_cellType(Cells::emp);    
            fileBoard[i + 1][j].set_cellType(Cells::emp);            
            fileBoard[i + 2][j].set_cellType(Cells::peg);
            break;
        }
        display_currentBoard(fileBoard);
    }
    PegSolitare::decrease_totalPegNum();
}

// Makes a a random move.
void PegSolitare::play()
{
    int i, j;
    char dir;
    string Move;
    Move.resize(4);
    do 
    {
        if (!get_defBoardSelection() && !get_fileBoardSelection())
        {
            cout << endl << "Board is tied! Please change the board or the game." << endl << endl;
            return;
        }
        
        if (get_defBoardSelection())
        {
            i = rand() % (defBoards[get_boardType() - 1].size());
            j = rand() % (defBoards[get_boardType() - 1][0].size());
        }
        else if (get_fileBoardSelection())
        {
            i = rand() % (fileBoard.size());
            j = rand() % (fileBoard.size());
        }
        dir = rand() % 4;
        if (dir == 0) dir = 'L';
        else if (dir == 1) dir = 'R';
        else if (dir == 2) dir = 'U';
        else if (dir == 3) dir = 'D';

        Move[0] = j + 'A';
        Move[1] = i + '1';
        Move[3] = dir;
        
    } while (move_validitiy(Move) == false);
    
    play(Move);
}

void PegSolitare::playGame(vector<vector<Cell>>& Board)
{
    int i, j;
    char dir;
    string Move;
    Move.resize(4);
    
    while(is_board_tied(Board) == false)
    {
        do 
        {
            if (!get_defBoardSelection() && !get_fileBoardSelection())
            {
                cout << endl << "Board is tied! Please change the board or the game." << endl << endl;
                return;
            }
            
            if (get_defBoardSelection())
            {
                i = rand() % (defBoards[get_boardType() - 1].size());
                j = rand() % (defBoards[get_boardType() - 1][0].size());
            }
            else if (get_fileBoardSelection())
            {
                i = rand() % (fileBoard.size());
                j = rand() % (fileBoard.size());
            }
            dir = rand() % 4;
            if (dir == 0) dir = 'L';
            else if (dir == 1) dir = 'R';
            else if (dir == 2) dir = 'U';
            else if (dir == 3) dir = 'D';

            Move[0] = j + 'A';
            Move[1] = i + '1';
            Move[3] = dir;
            
        } while (move_validitiy(Move) == false);
        play(Move);
    }
    cout << endl << "Game Over." << endl << endl;
}

// Load a board from a file.
void PegSolitare::load_board(const string& fileName)
{
    fstream inputStream;
    string line;
    fileBoard.clear();

    inputStream.open(fileName);
    if(inputStream.is_open() == false)
    {
        cerr << endl << endl << "File couldn't open. Program terminated." << endl;
        exit(1);
    }
    for(int i = 0; inputStream >> line; i++)
    {
        fileBoard.resize(i + 1);
        for(int j = 0; j < line.size(); j++)
        {
            fileBoard[i].resize(j + 1);
            if (line.at(j) == '.') fileBoard[i][j].set_cellType(Cells::wal);
            else if (line.at(j) == '#') fileBoard[i][j].set_cellType(Cells::emp);
            else if (line.at(j) == 'o') 
            {
                fileBoard[i][j].set_cellType(Cells::peg);
                PegSolitare::increase_totalPegNum(1);
            }

            fileBoard[i][j].set_position(j + 'A', i + 1);
        }
    }
    if (fileBoard.size() != fileBoard[0].size())
    {
        cerr << endl << endl << "Board is not square! Program terminated." << endl;
        exit(1);
    }
    else if (fileBoard.size() < 5)
    {
        cerr << endl << endl << "Board size is smaller then 5. Program terminated." << endl;
        exit(1);
    }

    set_fileBoardSelection(true);
    set_defBoardSelection(false);
    inputStream.close();
}

// Save the board to a file.
void PegSolitare::save_board(const string& fileName)
{
    ofstream outputStream;
    outputStream.open(fileName);

    if(outputStream.is_open() == false)
    {
        cerr << endl << endl << "File couldn't create. Program terminated." << endl;
        exit(1);
    }
    if (get_defBoardSelection())
    {
        for(int i = 0; i < defBoards[get_boardType() - 1].size(); i++)
        {
            for(int j = 0; j < defBoards[get_boardType() - 1][0].size(); j++)
            {
                if(defBoards[get_boardType() - 1][i][j].get_cellType() == Cells::peg)
                {
                    outputStream << 'o';
                }
                else if(defBoards[get_boardType() - 1][i][j].get_cellType() == Cells::wal)
                {
                    outputStream << '.';
                }
                else if(defBoards[get_boardType() - 1][i][j].get_cellType() == Cells::emp)
                {
                    outputStream << '#';
                }
            }
            outputStream << '\n';
        }
    }
    else if(get_fileBoardSelection())
    {
        for(int i = 0; i < fileBoard.size(); i++)
        {
            for(int j = 0; j < fileBoard.size(); j++)
            {
                if(fileBoard[i][j].get_cellType() == Cells::peg)
                {
                    outputStream << 'o';
                }
                else if(fileBoard[i][j].get_cellType() == Cells::wal)
                {
                    outputStream << '.';
                }
                else if(fileBoard[i][j].get_cellType() == Cells::emp)
                {
                    outputStream << '#';
                }
            }
            outputStream << '\n';
        }
    }
    
    outputStream.close();
}

// Takes a vector of a board and compare it with the current board.
bool PegSolitare::compare_boards(const vector<vector<Cell>>& Board)
{
    int numOfPeg1 = 0, numOfPeg2 = 0;

    if (!get_defBoardSelection() && !get_fileBoardSelection())
    {
        return false;
    }
    for(int i = 0; i < Board.size(); i++)
    {
        for(int j = 0; j < Board[0].size(); j++)
        {
            if(Board[i][j].get_cellType() == Cells::peg)
                numOfPeg2++;
        }
    }

    if(get_defBoardSelection())
    {
        for(int i = 0; i < defBoards[get_boardType() - 1].size(); i++)
        {
            for(int j = 0; j < defBoards[get_boardType() - 1][0].size(); j++)
            {
                if(defBoards[get_boardType() - 1][i][j].get_cellType() == Cells::peg)
                    numOfPeg1++;
            }
        }  
    }
    if(get_fileBoardSelection())
    {
        for(int i = 0; i < fileBoard.size(); i++)
        {
            for(int j = 0; j < fileBoard[0].size(); j++)
            {
                if(fileBoard[i][j].get_cellType() == Cells::peg)
                    numOfPeg1++;
            }
        }
    }

    if (numOfPeg2 > numOfPeg1)
    {        
        cout << endl << "Second board has more pegs." << endl << endl;
        return false;
    }
    else if (numOfPeg2 == numOfPeg1)
    {
        cout << endl << "Both boards have the same number of pegs." << endl << endl;
        return false;
    }
    else
        return true;
}

// Returns the current board.
vector<vector<PegSolitare::Cell>> PegSolitare::get_board(int n) const
{
    if (n >= 0 && n < 6)
    {
        return defBoards[n];
    }
    else
    {
        return fileBoard;
    }
}

// ----- Static variable functions -----
// Increase number of the total games.
int PegSolitare::increase_gameNum(void)
{
    gameNum++;
    return gameNum;
}

// Changes the current game.
void PegSolitare::input_currentGame(const vector<PegSolitare>& Games)
{
    int opr;

    cout << endl << "--> Select the game you want to change." << " (0 to "<< get_gameNum() - 1 << ")"<< endl;
    display_available_games(Games);
    cin >> opr;
    set_currentGame(opr);
    if (get_currentGame() < 0 || get_currentGame() > get_gameNum() - 1)
    {
        cerr << endl << "Invalid selection. Program terminated." << endl;
        exit(1);
    }
    cout << endl << "New active game is: ";

    if (get_currentGame() == 0)
        cout << "default" << endl << endl;
    else
        cout << get_currentGame() << endl << endl;
}

// Increase number of the pegs
void PegSolitare::increase_totalPegNum(int n)
{
    totalPegNum += n;
}

// Decrease number of the pegs
void PegSolitare::decrease_totalPegNum(void)
{
    totalPegNum--;
}
// ------------- PegSolitare CLASS IMPLEMENTATIONS -------------

// ----- Helper functions make program sensible -----
void create_new_game(vector<PegSolitare>& Games)
{
    PegSolitare::increase_gameNum();
    Games.resize(PegSolitare::get_gameNum());
    PegSolitare::increase_totalPegNum(Games[0].get_defaultPegNum());
    cout << endl << "--> Game number '" << PegSolitare::get_gameNum() - 1 << "' has been created. " << endl << endl;
}

void display_available_games(const vector<PegSolitare>& Games)
{
    cout << endl << "Available Games: " << endl;
    cout << "-----------------" << endl << endl;
    for (int i = 0; i < PegSolitare::get_gameNum(); i++)
    {
        if (i == 0)
        {
            cout << "1- Default Game: 0" << endl;
        }
        else
        {
            cout << i + 1 << "- Game number:  " << i << endl;
        }        
    }
    cout << "-----------------" << endl << endl;
}

// Precondition: There should be already selected board.
// If there is, then it will compare a board user selected.
void board_comparision(vector<PegSolitare>& Games)
{
    int game_number, def_num;
    string board_name;
    vector<vector<PegSolitare::Cell>> disp;

    cout << endl << "-->Enter the game number: " << endl;
    cout << "(0 to " << Games.size() - 1 << ") - To create more game back to menu (-1)." << endl;
    cout << endl << "Warning! Load function overwrites the board on the selected game." << endl;
    cout << "If you want to compare the a board from a file, then select a different game which now you are playing." << endl;

    cin >> game_number;
    getchar();

    if (game_number >= 0 && game_number < Games.size())
    {
        cout << endl << "Enter board name: " << endl;
        cout << "(To default boards enter 1 to 6, or enter LOAD filename.txt from a file.)" << endl;
        
        getline(cin, board_name);

        if (board_name.compare("1") == 0 || board_name.compare("2") == 0 || board_name.compare("3") == 0 || 
            board_name.compare("4") == 0 || board_name.compare("5") == 0 || board_name.compare("6") == 0)
        {
            def_num = stoi(board_name) - 1;

            if(Games[PegSolitare::get_currentGame()].compare_boards(Games[game_number].get_board(def_num)))
            {
                cout << endl << "1st Board has more pegs." << endl;
            }
            if (!Games[PegSolitare::get_currentGame()].get_defBoardSelection() && !Games[PegSolitare::get_currentGame()].get_fileBoardSelection())
            {
                cerr << endl << "The first board is not selected. Please select a board first." << endl << endl;
                return;
            }

            cout << endl << "1st Board" << endl;
            cout << "---------" << endl;
            if (Games[PegSolitare::get_currentGame()].get_defBoardSelection())
                disp = Games[PegSolitare::get_currentGame()].get_board(Games[PegSolitare::get_currentGame()].get_boardType() - 1);
            
            else if (Games[PegSolitare::get_currentGame()].get_fileBoardSelection())
                disp = Games[PegSolitare::get_currentGame()].get_board(-1);
           
            Games[PegSolitare::get_currentGame()].display_currentBoard(disp);

            disp.clear();
            cout << endl << "2nd Board" << endl;
            cout << "---------" << endl;
            disp = Games[game_number].get_board(def_num);
            Games[game_number].display_currentBoard(disp);
        }
        else if (board_name.compare(0, 4, "LOAD") == 0)
        {
            Games[game_number].load_board(board_name.substr(5));
            
            if(Games[PegSolitare::get_currentGame()].compare_boards(Games[game_number].get_board(-1)))
            {
                cout << endl << "1st Board has more pegs." << endl << endl;
            }
            if (!Games[PegSolitare::get_currentGame()].get_defBoardSelection() && !Games[PegSolitare::get_currentGame()].get_fileBoardSelection())
            {
                cerr << endl << "The first board is not selected. Please select a board first." << endl << endl;
                return;
            }
            cout << endl << "1st Board" << endl;
            cout << "---------" << endl;
            if (Games[PegSolitare::get_currentGame()].get_defBoardSelection())
                disp = Games[PegSolitare::get_currentGame()].get_board(Games[PegSolitare::get_currentGame()].get_boardType() - 1);
            
            else if (Games[PegSolitare::get_currentGame()].get_fileBoardSelection())
                disp = Games[PegSolitare::get_currentGame()].get_board(-1);
            
            Games[PegSolitare::get_currentGame()].display_currentBoard(disp);
            
            disp.clear();
            
            cout << endl << "2nd Board" << endl;
            cout << "---------" << endl;
            disp = Games[game_number].get_board(-1);
            Games[game_number].display_currentBoard(disp);

            
        }
        else
        {
            cout << endl << "__Invalid input. You have redirected to menu." << endl;
        }
    }
    cout << endl << "(The results are printed before the boards.)" << endl << endl;
    disp.clear();
}

void view_menu(void)
{
    cout << endl;
    cout << "------- Menu -------" << endl;
    cout << "--------------------" << endl << endl;
    cout << "1- Enter '1' to create a new game. " << endl;
    cout << "2- Enter '2' to choose a board to play. " << endl;
    cout << "3- Enter '3' to display list of available games. " << endl;
    cout << "4- Enter '4' to change the game. " << endl;
    cout << "5- Enter '5' to see number of total pegs." << endl;
    cout << "6- Enter '6' to compare boards" << endl;
    cout << "8- Enter '8' to view menu. " << endl;
    cout << "9- Enter '-1' to terminate the game. " << endl << endl;
}
