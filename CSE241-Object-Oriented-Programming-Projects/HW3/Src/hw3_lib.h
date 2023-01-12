#include <iostream>
#include <fstream>
#include <vector>
#include<cstdlib> 
#include<ctime>

using namespace std;

enum class Cells {wal, peg, emp};   // Enum types represents cells

// Default boards size.
const int B1size = 7, B2size = 9, B3size = 8, B4size = 7, B5size = 9, B6row = 5, B6clm = 9; 

class PegSolitare
{
public:

    PegSolitare(void);              // Default constructor
    PegSolitare(int BT);            // Constructor with integer paramater
    PegSolitare(string fileName);   // Constructor with string paramater
    
    class Cell      // Inner Class
    {
        public:
            Cell(char clmValue, int rowValue, Cells cellTypeValue); // Constructor with paramter
            Cell(void);                                             // Default constructor
            // ------ Setter and Getter Functions of inner class ------
            void set_position(char clmValue, int rowValue);     
            void set_position(char C);
            void set_position(int R);
            void set_cellType(Cells cellTypeValue);
            int get_row(void) const;
            char get_clm(void) const;
            Cells get_cellType(void) const;
            void display_cell(void) const;
        private:
            // ------ Private variables of the class ------
            int row;
            char clm;
            Cells cellType;
    };
    
    // ------ Member functions of the outer class  ------ 
    void set_default_boards(void);
    void display_defBoards(void) const;
    void input_boardType(void);
    void set_boardType(int BT);
    inline int get_boardType(void) const {return boardType;};
    inline bool get_defBoardSelection(void) const {return isDefSelected;};
    inline void set_defBoardSelection(bool choosing) {isDefSelected = choosing;};
    inline bool get_fileBoardSelection(void) const {return isFileSelected;};
    inline void set_fileBoardSelection(bool choosing) {isFileSelected = choosing;};
    void lead_game(void);
    void playing();
    void playGame(vector<vector<Cell>>& Board);
    void load_board(const string& fileName);
    void save_board(const string& fileName);
    inline void set_boardSize(int BS) {boardSize = BS;};
    inline int get_boardSize(void) const {return boardSize;};
    void display_currentBoard(const vector<vector<Cell>>& Board) const;
    void game_instructions(void) const;
    bool move_validitiy(const string& Move) const;
    bool is_board_tied(const vector<vector<Cell>>& Board);
    inline int get_defaultPegNum(void) {return defaultPegNum;};
    bool compare_boards(const vector<vector<Cell>>& Board);
    vector<vector<Cell>> get_board(int n) const;
    
    void play(void);                    // Play a move randomly
    void play(const string& Move);      // Play a move by gettin move from user

    // ------ Static Member Functions ------
    static int increase_gameNum(void);
    inline static int get_gameNum(void) {return gameNum;};
    static void input_currentGame(const vector<PegSolitare>& Games);
    inline static int get_currentGame(void) {return currentGame;};
    inline static void set_currentGame(int CG) {currentGame = CG;};
    static void increase_totalPegNum(int n);
    static void decrease_totalPegNum(void);
    static int get_totalPegNum(void) {return totalPegNum;};


    // Cell type object accessor methods.
    void set_currentCell(char clmValue, int rowValue, Cells cellTypeValue);
    void display_currentCell(void) const;
private:
    vector<vector<vector<Cell>>> defBoards; // Vector of 2D default boards/
    vector<vector<Cell>> fileBoard;         // Vector of a board
    Cell currentCell;                             
    int boardType;
    bool isDefSelected;
    bool isFileSelected;
    int boardSize;
    static int gameNum;
    static int currentGame;
    static int totalPegNum;
    int defaultPegNum = 204;                // Constant total peg number in default boards.
};

// Helper Functions Definations - Nothing but it makes main function more readable.
void display_available_games(const vector<PegSolitare>& Games);
void create_new_game(vector<PegSolitare>& Games);
void view_menu(void);
void board_comparision(vector<PegSolitare>& Games);