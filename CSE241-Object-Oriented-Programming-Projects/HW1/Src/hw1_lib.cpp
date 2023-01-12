// FUNCTION LIBRARY WHICH USED IN THE PROGRAMc

#include "hw1_lib.h"        // Include libraries from hw1_lib.h.

// Const integers will be used in the program.
const int B1size = 9, B2size = 11, B3size = 10, B4size = 9, B5size = 11;

// Take reference of a board and display it.
void display_boards(const vector<vector<Cells>> &Board, int sizeX, int sizeY)
{
    char label = 'A';

    cout << "     ";
    for (int i = 0; i < sizeY - 2; i++, label++)
        cout << label << " ";

    cout << endl << endl;

    for (int i = 1; i < sizeX - 1; i++)
    {
        cout << i << "    ";
        for (int j = 1; j < sizeY - 1; j++)
        {
            if (Board[i][j] == Cells::peg)
                cout << "O ";
            else if (Board[i][j] == Cells::wal)
                cout << "  ";
            else
                cout << ". ";
        }
        cout << endl;   
    }
    cout << endl;
}

// Takes board and redirect game to human playing and computer playing option. 
// Print final results.
// It is for the board from 1 to 5. 6th board going to be hold in other function because of its shape.
void play_game(vector<vector<Cells>> &Board, int size)
{
    int decision;
    int score;

    cout << "\n\n----------------------"  << endl;
    cout << "  Let The Game Begin" << endl;
    cout << "----------------------"  << endl << endl;

    display_boards(Board, size, size);

    cout << endl << "Enter 1 for human playing, 2 for computer playing:  ";
    cin >> decision;
    
    if (decision == HUMAN) human_playing(Board, size);
    else if (decision == COMPR) computer_playing(Board, size);

    score = find_score(Board, size, size);

    cout << endl << "GAME OVER!";

    if (score == 1) cout << endl << "You won the game!" << endl << endl;
    else cout << endl << score << " pegs are left!" << endl << endl;

}

// User plays himself/herself.
void human_playing(vector<vector<Cells>> &Board, int size)
{
    string Move;            
    int indexX, indexY;
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
    while (!is_board_tie(Board, size))
    {
        // Take coordinates and the direction.
        cout << endl << "Please enter coordinate and direction to move. (e.g B4-R)" << endl;
        cin >> Move;
        indexY = (int)(Move[0] - ('A' - 1));
        indexX = (int)(Move[1] - '0');
        direction = (Movement)Move[3];
        
        // Takes a valid entry
        while (!is_move_valid(Board, size, indexX, indexY, direction))
        {
            cout << endl << "ERROR, Please enter valid coordinate and direction. (e.g B4-R)" << endl;
            cin >> Move;
            indexY = (int)(Move[0] - ('A' - 1));
            indexX = (int)(Move[1] - '0');
            direction = (Movement)Move[3];
        }

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
        display_boards(Board, size, size);
    }
}

// Computer plays.
void computer_playing(vector<vector<Cells>> &Board, int size)
{
    int indexX = 0, indexY = 0;
    int dir;
    Movement direction;

    // With random number generator computer decide which movement it will perform until board become tied.
    // Random number generator creates a coordinate and direction to move. Then with
    // a loop it being checked if the instruction is legal. It creates random coordinates 
    // and movement until it finds a legal entry.

    while (!is_board_tie(Board, size))
    {
        do 
        {
            indexX = rand() % (size - 2) + 1;
            indexY = rand() % (size - 2) + 1;
            dir = rand() % 4;
            if (dir == 0) direction = Movement::LEFT;
            else if (dir == 1) direction = Movement::RIGHT;
            else if (dir == 2) direction = Movement::UP;
            else if (dir == 3) direction = Movement::DOWN;
        } while (!is_move_valid(Board, size, indexX, indexY, direction));
        
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
        display_boards(Board, size, size);
    }
}

// Checks if first 5 board is tied according to pegs condition.
bool is_board_tie(const vector<vector<Cells>> &Board, int size)
{
    for (int i = 1; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1; j++)
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
bool is_move_valid(const vector<vector<Cells>> &Board, int size, int x, int y, Movement dir)
{
    if (x < 1 || x > size - 2 || y < 1 || y > size - 2) return false;

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
void play_triangle_game(vector<vector<Cells>> &Board, int sizeX, int sizeY)
{
    int indexX, indexY, decision, score, dir, lay;
    string Move;
    Movement direction;
    char layerDir = ' ';

    cout << "\n\n----------------------"  << endl;
    cout << "  Let The Game Begin" << endl;
    cout << "----------------------"  << endl << endl;

    display_boards(Board, sizeX, sizeY);

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
        while (!is_triangle_tie(Board, sizeX, sizeY))
        {
            cout << endl << "Please enter coordinate and direction to move. (e.g B4-R)" << endl;
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

            while (!(perform_triangle_move(Board, sizeX, sizeY, indexX, indexY, direction, layerDir)))
            {
                cout << endl << "ERROR, Please enter valid coordinate and direction. (e.g B4-R)" << endl;
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
            display_boards(Board, sizeX, sizeY);
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


        while (!is_triangle_tie(Board, sizeX, sizeY))
        {
            do 
            {
                indexX = rand() % (sizeX - 2) + 1;
                indexY = rand() % (sizeY - 2) + 1;
                dir = rand() % 4;
                if (dir == 0) direction = Movement::LEFT;
                else if (dir == 1) direction = Movement::RIGHT;
                else if (dir == 2) direction = Movement::UP;
                else if (dir == 3) direction = Movement::DOWN;


                if (direction == Movement::UP || direction == Movement::DOWN) lay = rand() % 2;

                lay % 2 == 0 ? layerDir = 'L' : layerDir = 'R';
                

            } while (!perform_triangle_move(Board, sizeX, sizeY, indexX, indexY, direction, layerDir));
            
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
            display_boards(Board, sizeX, sizeY);
        }
    }
    
    score = find_score(Board, sizeX, sizeY);

    cout << endl << "GAME OVER!";

    if (score == 1) cout << endl << "You won the game!" << endl << endl;
    else cout << endl << score << " pegs are left!" << endl << endl;
}

// Checks every peg of the triangle board and return true if it is tied.
bool is_triangle_tie(const vector<vector<Cells>> &Board, int sizeX, int sizeY)
{
    for (int i = 1; i < sizeX - 1; i++)
    {
        for (int j = 1; j < sizeY - 1; j++)
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
bool perform_triangle_move(vector<vector<Cells>> &Board, int sizeX, int sizeY, int x, int y, Movement dir, char layerDir)
{
    if (x < 1 || x > sizeX - 2 || y < 1 || y > sizeY - 2) return false;

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
int find_score(const vector<vector<Cells>> &Board, int sizeX, int sizeY)
{
    int n = 0;

    for (int i = 0; i < sizeX; i++)
        for (int j = 0; j < sizeY; j++)
            if (Board[i][j] == Cells::peg)  n++;
    
    return n;
}

// ------------------------- END OF FUNCTION LIBRARY -------------------------
