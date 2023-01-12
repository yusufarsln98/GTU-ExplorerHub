#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

// Enumerated Types
enum class Cells{wal, peg, emp};
enum Movement {LEFT = 'L', RIGHT = 'R', UP = 'U', DOWN  = 'D'};

#define HUMAN 1
#define COMPR 2

// ------------------------- Function Declarations -------------------------

void display_boards(const vector<vector<Cells>> &Board, int row, int clm);
void display_default_boards(const vector<vector<Cells>> &B1, const vector<vector<Cells>> &B2, const vector<vector<Cells>> &B3, 
                            const vector<vector<Cells>> &B4, const vector<vector<Cells>> &B5, const vector<vector<Cells>> &B6);
void display_arbitrary_boards(void);
void display_instructions(void);
void read_arbBoard(vector<vector<Cells>> &Board, string filename, int &Move, int &Player, int &X, int &Y);
void save_board(vector<vector<Cells>> &Board, string filename, int Move, int Player, int X, int Y);

void play_game(vector<vector<Cells>> &Board, int row, int clm, int moveNum, string &load);
void human_playing(vector<vector<Cells>> &Board, int row, int clm, string &load);
void computer_playing(vector<vector<Cells>> &Board, int row, int clm, string &load);
bool is_board_tie(const vector<vector<Cells>> &Board, int row, int clm);
bool is_move_valid(const vector<vector<Cells>> &Board, int row, int clm, int x, int y, Movement dir);
void perform_move(vector<vector<Cells>> &Board, int x, int y, Movement dir);
void play_triangle_game(vector<vector<Cells>> &Board, int row, int clm, int moveNum, string &load);
bool is_triangle_tie(const vector<vector<Cells>> &Board, int row, int clm);
bool perform_triangle_move(vector<vector<Cells>> &Board, int row, int clm, int x, int y, Movement dir, char layerDir);
int find_score(const vector<vector<Cells>> &Board, int row, int clm);

// ------------------------- END OF HEADER FILE -------------------------