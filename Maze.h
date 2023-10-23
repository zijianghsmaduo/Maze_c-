#ifndef MAZE_H_
#define MAZE_H_

#include<random>
#include<string>
#include<set>
using namespace std;
class Maze
{
private:
    int N;
    bool** north;// is there a wall to north of cell i, j
    bool** west;
    bool** east;
    bool** south;
    
    default_random_engine eng;
    const int Min;
    const int Max;
    // still need northwest, northeast.. but they can be represent by the arrays above

    void generateSingleGapMaze(); // generate a maze starting from lower left

    void generateSGHelper(int x, int y, bool** marked); // The helper of generateSingleGraphMaze (actuall the implementation)

    bool wallExist(int x, int y, string dir); // is there a wall to the dir of x,y

    int toX(int pos);

    int toY(int pos);

    int targetX(int x, string s);

    int targetY(int y, string s);


public:
    Maze(int n);
    ~Maze();

    set<int> adj(int pos); // To find every accessable adjecent grids of the grid pos

    int getV();

    int getN();

    int xyTo1D(int x, int y);

    void drawInConsole();
    
};
    // In my version of Maze, I decided to not use the conceret cell as a wall which is used in 
    // the text book, but to use a virtual wall between two cells
    // First, generate the N S W E, than using the circumstance in the grid 
    // to determine whether a cell is possible to go NE, NW, SE, SW
    // The example is below.
    /*      
    *     4 g g g g
    *     3 g g|g g
    *     2 g g|g g
    *     1 g g|g g   
    *       1 2 3 4
    * eg. (2, 2)cannot go NE and E, but it can go N E S
    *     (2, 3)cannot go SE, but it can go NE  
    */


#endif