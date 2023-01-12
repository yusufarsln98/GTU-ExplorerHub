// FUNCTION DECLARATIONS AND LIBRARIES USED IN THE PROGRAM

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

enum class Cells{wal, peg, emp};
enum Movement {LEFT = 'L', RIGHT = 'R', UP = 'U', DOWN  = 'D'};

#define HUMAN 1
#define COMPR 2

void display_boards(const vector<vector<Cells>> &Board, int sizeX, int sizeY);
void play_game(vector<vector<Cells>> &Board, int size);
void human_playing(vector<vector<Cells>> &Board, int size);
void computer_playing(vector<vector<Cells>> &Board, int size);
bool is_board_tie(const vector<vector<Cells>> &Board, int size);
bool is_move_valid(const vector<vector<Cells>> &Board, int size, int x, int y, Movement dir);
void perform_move(vector<vector<Cells>> &Board, int x, int y, Movement dir);
void play_triangle_game(vector<vector<Cells>> &Board, int sizeX, int sizeY);
bool is_triangle_tie(const vector<vector<Cells>> &Board, int sizeX, int sizeY);
bool perform_triangle_move(vector<vector<Cells>> &Board, int sizeX, int sizeY, int x, int y, Movement dir, char layerDir);
int find_score(const vector<vector<Cells>> &Board, int sizeX, int sizeY);

// ------------------------- END OF HEADER FILE -------------------------
