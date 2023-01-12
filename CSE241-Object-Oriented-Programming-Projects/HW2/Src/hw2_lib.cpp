#include "hw2_lib.h"

const int B1size = 9, B2size = 11, B3size = 10, B4size = 9, B5size = 11, B6row = 7, B6clm = 11;


// Precondition: Takes vector and int references and also filename as a string
// Postcondition: Gives board as a vector, number of moves, player type, sizes of vector
void read_arbBoard(vector<vector<Cells>> &Board, string filename, int &Move, int &Player, int &X, int &Y)
{
    string text;
    fstream inputStream;
    inputStream.open(filename);
    // Find number of movement and last player (Human or Computer)
    inputStream >> text;
    Move = stoi(text);
    inputStream >> text;
    Player = stoi(text);

    for (X = 0; inputStream >> text; X++)
    {
        Board.resize(X + 1);
        for (Y = 0; Y < text.size(); Y++)
        {
            Board[X].resize(Y + 1);
            if (text.at(Y) == '.') Board[X][Y] = Cells::wal;
            else if (text.at(Y) == '*') Board[X][Y] = Cells::emp;
            else if (text.at(Y) == 'O') Board[X][Y] = Cells::peg;
        }
    }
    
    inputStream.close();
    return;
}

void save_board(vector<vector<Cells>> &Board, string filename, int Move, int Player, int X, int Y)
{
    ofstream outputStream;
    outputStream.open(filename);
    outputStream << Move << endl;
    outputStream << Player << endl;
    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            if (Board[i][j] == Cells::wal)
                outputStream << '.';
            else if (Board[i][j] == Cells::peg)
                outputStream << 'O';
            else if (Board[i][j] == Cells::emp)
                outputStream << '*';
        }
        outputStream << endl;
    }
}
// Display instruction to the screen
void display_instructions(void)
{
    cout << "Instructions: " << endl;
    cout << "-------------";
    cout << endl << endl << "1- Game has 3 type boards." << endl;
    cout << "   I-      Default Type" << endl;
    cout << "   II-     Arbitrary Type" << endl;
    cout << "   III-    Previously Played" << endl;
    cout << endl << "2- Play default board by ENTERING 1 to 6." << endl;
    cout << "3- To play boards from file ENTER \"load filename.txt\"" << endl;
    cout << "4- To save a board into a file ENTER \"save filename.txt\"";
    cout << endl << "5- To play game: " << endl;
    cout << "   Enter coordinates, then a dash and the direction." << endl;
    cout << "   Directions: L (Left) R (Right) U (Up) D (Down)" << endl;
    cout << "   for example: to play peg on B3 to Up, ENTER \"B3-U\"" << endl;
    cout << endl << "6- To display instructions, ENTER \"instructions\"" << endl;
    cout << "7- To terminate, ENTER \"exit\"" << endl << endl;

}

// Takes board and redirect game to human playing and computer playing option. 
// Print final results.
// It is for the board from 1 to 5. 6th board going to be hold in other function because of its shape.
void play_game(vector<vector<Cells>> &Board, int row, int clm, int moveNum, string &load)
{
    int decision, score;
    string str;

    cout << "\n\n----------------------"  << endl;
    cout << "  Let The Game Begin" << endl;
    cout << "----------------------"  << endl << endl;

    display_boards(Board, row, clm);

    cout << endl << "Enter 1 for human playing, 2 for computer playing:  ";
    cin >> decision;
    
    if (decision == HUMAN) human_playing(Board, row, clm, load);
    else if (decision == COMPR) computer_playing(Board, row, clm, load);

    if (load.compare(0, 4, "load") == 0) return;

    score = find_score(Board, row, clm);

    cout << endl << "GAME OVER!";

    if (score == 1) cout << endl << "You won the game!" << endl << endl;
    else cout << endl << score << " pegs are left!" << endl << endl;
    
    return;
}

// User plays himself/herself.
void human_playing(vector<vector<Cells>> &Board, int row, int clm, string &load)
{
    string Move, filename;            
    int indexX, indexY, moveNum = 0;
    Movement direction;

    /*
    Until game is finish or tied, game continues.
    It asks users to enter the coordinates of peg and the direction person wants to move
    until get a valid entry.

    B4 Represents the Coordinate.
    R represent the direction (Right)
    
    Other directions: L (Left) U (Up) D (Down)

    Lets assume there is a board like this: 

             A B C D E F G

        1        O O O
        2        O O O
        3    O O O O O O O
        4    O O . . O O O 
        5    O O O O O O O
        6        O O O
        7        O O O
    
    For example: F3-L is a valid entry which moves H3 to C3 and takes peg on the E4;

             A B C D E F G

        1        O O O
        2        O O O
        3    O O O O O O O
        4    O O . O X . O 
        5    O O O O O O O
        6        O O O
        7        O O O

    New board becomes;

             A B C D E F G

        1        O O O
        2        O O O
        3    O O O O O O O
        4    O O . O . . O 
        5    O O O O O O O
        6        O O O
        7        O O O

    E5-U is an unvalid entry since there is not any peg above on the E5.
    It will ask a valid number until legal moves finish.

    */
    cin.ignore();

    cout << endl << "To save game into a file enter \"save filename.txt\"" << endl;
    cout << "To load game from a file enter \"load filename.txt\"" << endl;
    while (!is_board_tie(Board, row, clm))
    {
        // Take coordinates and the direction.
        cout << endl << "Please enter coordinate and direction to move. (e.g B4-R)" << endl;
        cout << "Type 0 to return the menu." << endl;
        
        getline(cin, Move);

        if (Move.compare("0") == 0) break;
        else if (Move.compare(0, 4, "save") == 0)
        {
            filename = Move.substr(5);
            save_board(Board, filename, moveNum, HUMAN, clm, row);
            break;
        }
        else if (Move.compare(0, 4, "load") == 0)
        {
            load = Move;
            return;
        }

        indexY = (int)(Move[0] - ('A' - 1));
        indexX = (int)(Move[1] - '0');
        direction = (Movement)Move[3];
        
        // Takes a valid entry
        while (!is_move_valid(Board, row, clm, indexX, indexY, direction))
        {
            cerr << endl << "ERROR, Please enter valid coordinate and direction. (e.g B4-R)" << endl;
            cout << "Type 0 to return the menu." << endl;
            cout << "To save game into a file enter \"save filename.txt\"" << endl;

            getline(cin, Move);

            if (Move.compare("0") == 0) break;
            else if (Move.compare(0, 4, "save") == 0)
            {
                filename = Move.substr(5);
                save_board(Board, filename, moveNum, HUMAN, clm, row);
            }
    
            indexY = (int)(Move[0] - ('A' - 1));
            indexX = (int)(Move[1] - '0');
            direction = (Movement)Move[3];
        }
        if (Move.compare("0") == 0 || Move.compare(0, 4, "save") == 0) break;
        // Perform the instruction
        perform_move(Board, indexX, indexY, direction);

        // Print to the screen which move has been done and the new board.
        cout << endl << "The peg in " << Move[0] << Move[1] << " has been moved to the ";
        switch (direction)
        {
        case 'L':
            cout << "left.\n\n";
            break;
        case 'R':
            cout << "right.\n\n";
            break;
        case 'U':
            cout << "upward.\n\n";
            break;
        case 'D':
            cout << "downward.\n\n";
            break;
        }
        display_boards(Board, row, clm);
        moveNum++;
        
    }
}
// Computer plays.
void computer_playing(vector<vector<Cells>> &Board, int row, int clm, string &load)
{
    int indexX = 0, indexY = 0, moveNum = 0, dir;
    char ch;
    string str;
    Movement direction;

    // With random number generator computer decide which movement it will perform until board become tied.
    // Random number generator creates a coordinate and direction to move. Then with
    // a loop it being checked if the instruction is legal. It creates random coordinates 
    // and movement until it finds a legal entry.

    cin.ignore();
    cout << endl << "Enter \"save filename.txt\" to save the board." << endl;
    cout << "Enter \"load filename.txt\" to load the board." << endl << endl;

    while (!is_board_tie(Board, row, clm))
    {
        cout << "Enter 0 to back or 1 to make another random move." << endl;
        getline(cin, str);

        if (str.compare(0, 4, "save") == 0)
        {
            save_board(Board, str.substr(5), moveNum, COMPR, row, clm);
            break;
        }
        else if (str.compare("0") == 0) break; 
        else if (str.compare(0, 4, "load") == 0)
        {
            load = str;
            return;
        }

        do 
        {
            indexX = rand() % (row - 2) + 1;
            indexY = rand() % (clm - 2) + 1;
            dir = rand() % 4;
            if (dir == 0) direction = Movement::LEFT;
            else if (dir == 1) direction = Movement::RIGHT;
            else if (dir == 2) direction = Movement::UP;
            else if (dir == 3) direction = Movement::DOWN;
        } while (!is_move_valid(Board, row, clm, indexX, indexY, direction));

        perform_move(Board, indexX, indexY, direction);
        indexY += ('A' - 1);
        cout << endl << "The peg in " << (char)indexY << indexX << " has been moved to the ";
        switch (direction)
        {
        case 'L':
            cout << "left.\n\n";
            break;
        case 'R':
            cout << "right.\n\n";
            break;
        case 'U':
            cout << "upward.\n\n";
            break;
        case 'D':
            cout << "downward.\n\n";
            break;
        }
        moveNum++;
        display_boards(Board, row, clm);
    }
}

// Checks if first 5 board is tied according to pegs condition.
bool is_board_tie(const vector<vector<Cells>> &Board, int row, int clm)
{
    for (int i = 1; i < row - 1; i++)
    {
        for (int j = 0; j < clm - 1; j++)
        {
            if (Board[i][j] == Cells::peg)
            {
                if (Board[i][j + 1] == Cells::peg && Board[i][j + 2] == Cells::emp)
                    return false;
                else if (Board[i + 1][j] == Cells::peg && Board[i + 2][j] == Cells::emp)
                    return false;
                else if (Board[i - 1][j] == Cells::peg && Board[i - 2][j] == Cells::emp)
                    return false;
                else if (Board[i][j - 1] == Cells::peg && Board[i][j - 2] == Cells::emp)
                    return false;
            }
        }
    }
    return true;
}

// Checks if instruction is legal.
bool is_move_valid(const vector<vector<Cells>> &Board, int row, int clm, int x, int y, Movement dir)
{
    if (x < 1 || x > row - 2 || y < 1 || y > clm - 2) return false;

    switch (dir)
    {
    case LEFT:
        if (Board[x][y] == Cells::peg && Board[x][y - 1] == Cells::peg && Board[x][y - 2] == Cells::emp) return true; 
        break;
    case RIGHT:
        if (Board[x][y] == Cells::peg && Board[x][y + 1] == Cells::peg && Board[x][y + 2] == Cells::emp) return true; 
        break;
    case UP: 
        if (Board[x][y] == Cells::peg && Board[x - 1][y] == Cells::peg && Board[x - 2][y] == Cells::emp) return true; 
        break;
    case DOWN:
        if (Board[x][y] == Cells::peg && Board[x + 1][y] == Cells::peg && Board[x + 2][y] == Cells::emp) return true; 
        break;
    }

    return false;
}

// Performs the movement if the instruction is legal.
void perform_move(vector<vector<Cells>> &Board, int x, int y, Movement dir)
{
    switch (dir)
    {
    case LEFT:
        Board[x][y] = Cells::emp; Board[x][y - 1] = Cells::emp; Board[x][y - 2] = Cells::peg;
        break;
    case RIGHT:
        Board[x][y] = Cells::emp; Board[x][y + 1] = Cells::emp; Board[x][y + 2] = Cells::peg;
        break;
    case UP:
        Board[x][y] = Cells::emp; Board[x - 1][y] = Cells::emp; Board[x - 2][y] = Cells::peg;
        break;
    case DOWN:
        Board[x][y] = Cells::emp; Board[x + 1][y] = Cells::emp; Board[x + 2][y] = Cells::peg;
        break;
    }
}

// --------------------------- Functions for play with triangle board ---------------------------
// According to the user's choice, the game is played by human or computer.
void play_triangle_game(vector<vector<Cells>> &Board, int row, int clm, int moveNum, string &load)
{
    int indexX, indexY, decision, score, dir, lay;
    string Move, str;
    Movement direction;
    char layerDir = ' ';

    cout << "\n\n----------------------"  << endl;
    cout << "  Let The Game Begin" << endl;
    cout << "----------------------"  << endl << endl;

    display_boards(Board, row, clm);

    // User decide if going to play himself/herself or computer plays the game.

    cout << endl << "Enter 1 for human playing, 2 for computer playing:  ";
    cin >> decision;

    if (decision == HUMAN)
    {
        /*
        The game continues until there are no legal moves left.

        In triangle board different from the others you move upward and downward through the left or right.
        To give an example let the look this board:

             A B C D E F G H I

        1            O
        2          .   O
        3        .   O   O
        4      O   O   O   O
        5    O   O   O   O   O 

        
        For example since there is not any gap in C5 the G5-L is not legal as much as G5 to Up and Right.

        However,

        User can carry peg on A5 to C3 by move going to be explain:

        First user write A5-U (Which mean carry peg on A5 to Upward) then
        since there is two option in the top row it will be asked enter L or R (Left or Right).

        If user picks L, since there is not any peg on that side it will be asked for a legal move
        but if user picks R the peg on A5 will be moved to the C3 by picking peg on B4.

             A B C D E F G H I

        1            O
        2          .   O
        3        O   O   O
        4      X   O   O   O
        5    .   O   O   O   O 

        
        And final board is going to be this:

             A B C D E F G H I

        1            O
        2          .   O
        3        O   O   O
        4      .   O   O   O
        5    .   O   O   O   O 
        

        The game continues until it is tied.
        */
        
        cout << endl << "To save game into a file enter \"save filename.txt\"" << endl;
        cout << "To load game from a file enter \"load filename.txt\"" << endl;
        while (!is_triangle_tie(Board, row, clm))
        {
            cout << endl << "Please enter coordinate and direction to move. (e.g B4-R)" << endl;
            cout << "Type 0 to return the menu." << endl;
            cin.ignore();
            getline(cin, Move);

            if (Move.compare("0") == 0) break;
            else if (Move.compare(0, 4, "save") == 0)
            {
                save_board(Board, Move.substr(5), moveNum, HUMAN, row, clm);
                break;
            }
            else if (Move.compare(0, 4, "load") == 0)
            {
                load = Move;
                return;
            }

            indexY = (int)(Move[0] - ('A' - 1));
            indexX = (int)(Move[1] - '0');
            direction = (Movement)Move[3];

            if (direction == Movement::UP)
            {
                cout << "Please enter L for UP-LEFT or R for UP-RIGHT:  ";
                cin >> layerDir;
            }
            else if (direction == Movement::DOWN)
            {
                cout << "Please enter L for DOWN-LEFT or R for DOWN-RIGHT:  ";
                cin >> layerDir;
            }

            while (!(perform_triangle_move(Board, row, clm, indexX, indexY, direction, layerDir)))
            {
                cerr << endl << "ERROR, Please enter valid coordinate and direction. (e.g B4-R)" << endl;
                cin >> Move;
                indexY = (int)(Move[0] - ('A' - 1));
                indexX = (int)(Move[1] - '0');
                direction = (Movement)Move[3];

                if (direction == Movement::UP)
                {
                    cout << "Please enter L for UP-LEFT or R for UP-RIGHT:  ";
                    cin >> layerDir;
                }
                else if (direction == Movement::DOWN)
                {
                    cout << "Please enter L for DOWN-LEFT or R for DOWN-RIGHT:  ";
                    cin >> layerDir;
                }
            }
            cout << endl << "The beg in " << Move[0] << Move[1] << " has been moved to the ";
            switch (direction)
            {
            case 'L':
                cout << "left.\n\n";
                break;
            case 'R':
                cout << "right.\n\n";
                break;
            case 'U':
                cout << "upward.\n\n";
                break;
            case 'D':
                cout << "downward.\n\n";
                break;
            }
            moveNum++;
            display_boards(Board, row, clm);
        }
    }
    else if (decision == COMPR)
    {
        /*
        The game continues until there are no legal moves left.

        Computer create instructions by random number generators.
        Then it is constantly checked by a function until a legal move is created.

        Then the instruction is executed.

        The game continues until it is tied.
        */
        cout << endl << "Enter \"save filename.txt\" to save the board." << endl;
        
        while (!is_triangle_tie(Board, row, clm))
        {
            cout << "Enter 0 to back or 1 to make another random move." << endl;
            cin.ignore();
            getline(cin, str);
            
            if (str.compare(0, 4, "save") == 0)
            {
                save_board(Board, str.substr(5), moveNum, COMPR, row, clm);
                break;
            }
            else if (str.compare("0") == 0) break;         
            else if (str.compare(0, 4, "load") == 0)
            {
                load = str;
                return;
            }    
            
            do 
            {
                indexX = rand() % (row - 2) + 1;
                indexY = rand() % (clm - 2) + 1;
                dir = rand() % 4;
                if (dir == 0) direction = Movement::LEFT;
                else if (dir == 1) direction = Movement::RIGHT;
                else if (dir == 2) direction = Movement::UP;
                else if (dir == 3) direction = Movement::DOWN;


                if (direction == Movement::UP || direction == Movement::DOWN) lay = rand() % 2;

                lay % 2 == 0 ? layerDir = 'L' : layerDir = 'R';
                

            } while (!perform_triangle_move(Board, row, clm, indexX, indexY, direction, layerDir));
            
            indexY += ('A' - 1);
            cout << endl << "The peg in " << (char)indexY << indexX << " has been moved to the ";
            switch (direction)
            {
            case 'L':
                cout << "left.\n\n";
                break;
            case 'R':
                cout << "right.\n\n";
                break;
            case 'U':
                cout << "upward.\n\n";
                break;
            case 'D':
                cout << "downward.\n\n";
                break;
            }
            display_boards(Board, row, clm);
        }
    }
    
    score = find_score(Board, row, clm);

    cout << endl << "GAME OVER!";

    if (score == 1) cout << endl << "You won the game!" << endl << endl;
    else cout << endl << score << " pegs are left!" << endl << endl;
}

// Checks every peg of the triangle board and return true if it is tied.
bool is_triangle_tie(const vector<vector<Cells>> &Board, int row, int clm)
{
    for (int i = 1; i < row - 1; i++)
    {
        for (int j = 1; j < clm - 1; j++)
        {
            if (Board[i][j] == Cells::peg)
            {
                if (Board[i][j - 2] == Cells::peg && Board[i][j - 4] == Cells::emp)
                    return false;
                else if (Board[i][j + 2] == Cells::peg && Board[i][j + 4] == Cells::emp)
                    return false;
                else if (Board[i - 1][j - 1] == Cells::peg && Board[i - 2][j - 2] == Cells::emp)
                    return false;
                else if (Board[i - 1][j + 1] == Cells::peg && Board[i - 2][j + 2] == Cells::emp)
                    return false;
                else if (Board[i + 1][j - 1] == Cells::peg && Board[i + 2][j - 2] == Cells::emp)
                    return false;
                else if (Board[i + 1][j + 1] == Cells::peg && Board[i + 2][j + 2] == Cells::emp)
                    return false;
            }
        }
    }
    return true;
}

// Checks if movement is valid. If it is, move will be perform and return true. Otherwise it will return false.
bool perform_triangle_move(vector<vector<Cells>> &Board, int row, int clm, int x, int y, Movement dir, char layerDir)
{
    if (x < 1 || x > row - 2 || y < 1 || y > clm - 2) return false;

    switch (dir)
    {
    case LEFT:
        if (Board[x][y] == Cells::peg && Board[x][y - 2] == Cells::peg && Board[x][y - 4] == Cells::emp)
        {
            Board[x][y] = Cells::emp; Board[x][y - 2] = Cells::emp; Board[x][y - 4] = Cells::peg;
            return true;
        }
        break;
    case RIGHT:
        if (Board[x][y] == Cells::peg && Board[x][y + 2] == Cells::peg && Board[x][y + 4] == Cells::emp)
        {
            Board[x][y] = Cells::emp; Board[x][y + 2] = Cells::emp; Board[x][y + 4] = Cells::peg;
            return true;
        }
        break;
    case UP:
        if (layerDir == 'L')
        {
            if (Board[x][y] == Cells::peg && Board[x - 1][y - 1] == Cells::peg && Board[x - 2][y - 2] == Cells::emp)
            {
                Board[x][y] = Cells::emp; Board[x - 1][y - 1] = Cells::emp; Board[x - 2][y - 2] = Cells::peg;
                return true;
            }
        }
        else if (layerDir == 'R')
        {
            if (Board[x][y] == Cells::peg && Board[x - 1][y + 1] == Cells::peg && Board[x - 2][y + 2] == Cells::emp)
            {
                Board[x][y] = Cells::emp; Board[x - 1][y + 1] = Cells::emp; Board[x - 2][y + 2] = Cells::peg;
                return true;
            }
        }
        break;
    case DOWN:
        if (layerDir == 'L')
        {
            if (Board[x][y] == Cells::peg && Board[x + 1][y - 1] == Cells::peg && Board[x + 2][y - 2] == Cells::emp)
            {
                Board[x][y] = Cells::emp; Board[x + 1][y - 1] = Cells::emp; Board[x + 2][y - 2] = Cells::peg;
                return true;
            }
        }
        else if (layerDir == 'R')
        {
            if (Board[x][y] == Cells::peg && Board[x + 1][y + 1] == Cells::peg && Board[x + 2][y + 2] == Cells::emp)
            {
                Board[x][y] = Cells::emp; Board[x + 1][y + 1] = Cells::emp; Board[x + 2][y + 2] = Cells::peg;
                return true;
            }
        }
        break;
    }

    return false;
}

// Finds the final score. 
int find_score(const vector<vector<Cells>> &Board, int row, int clm)
{
    int n = 0;

    for (int i = 0; i < row; i++)
        for (int j = 0; j < clm; j++)
            if (Board[i][j] == Cells::peg)  n++;
    
    return n;
}

// Display one board.
void display_boards(const vector<vector<Cells>> &Board, int row, int clm)
{
    char label = 'A';

    cout << "     ";
    for (int i = 0; i < clm - 2; i++, label++)
        cout << label << " ";

    cout << endl << endl;

    for (int i = 1; i < row - 1; i++)
    {
        cout << i << "    ";
        for (int j = 1; j < clm - 1; j++)
        {
            if (Board[i][j] == Cells::peg)
                cout << "O ";
            else if (Board[i][j] == Cells::wal)
                cout << ". ";
            else
                cout << "  ";
        }
        cout << endl;   
    }
    cout << endl;
}

// To the menu displays all default boards.
void display_default_boards(const vector<vector<Cells>> &B1, const vector<vector<Cells>> &B2, const vector<vector<Cells>> &B3, 
                            const vector<vector<Cells>> &B4, const vector<vector<Cells>> &B5, const vector<vector<Cells>> &B6)
{
    cout << endl << "---------------- Default Boards ----------------" << endl << endl;

    cout << "1-" << endl;
    display_boards(B1, B1size, B1size);
    cout << "--------------------------" << endl << endl;

    cout << "2-" << endl;
    display_boards(B2, B2size, B2size);
    cout << "--------------------------" << endl << endl;

    cout << "3-" << endl;
    display_boards(B3, B3size, B3size);
    cout << "--------------------------" << endl << endl;
    
    cout << "4-" << endl;
    display_boards(B4, B4size, B4size);
    cout << "--------------------------" << endl << endl;
    
    cout << "5-" << endl;
    display_boards(B5, B5size, B5size);
    cout << "--------------------------" << endl << endl;

    cout << "6-" << endl;
    display_boards(B6, B6row, B6clm);
    cout << "--------------------------" << endl << endl;
}

// To the menu, displays arbitrary boards.
void display_arbitrary_boards(void)
{
    int moveNum, player;                        // Number of move and which player was the last one
    int arbrow, arbclm;                         // Dimensions of arbitrary boards
    
    vector<vector<Cells>> arbBoard;             // Declaration of arbitrary boards
    
    cout << "1- " << endl;
    read_arbBoard(arbBoard, "arbBoard1.txt", moveNum, player, arbrow, arbclm);
    display_boards(arbBoard, arbrow, arbclm);
    cout << endl << "file name: " << "arbBoard1.txt" << endl << endl;
    arbBoard.clear();

    cout << "2- ";
    read_arbBoard(arbBoard, "arbBoard2.txt", moveNum, player, arbrow, arbclm);
    display_boards(arbBoard, arbrow, arbclm);
    cout << endl << "file name: " << "arbBoard2.txt" << endl << endl;
    arbBoard.clear();

    cout << "3- ";
    read_arbBoard(arbBoard, "arbBoard3.txt", moveNum, player, arbrow, arbclm);
    display_boards(arbBoard, arbrow, arbclm);
    cout << endl << "file name: " << "arbBoard3.txt" << endl << endl;
    arbBoard.clear();
}

// ------------------------- END OF FUNCTION LIBRARY -------------------------
