#include"Maze.h"
#include<random>
#include<iomanip>
#include<iostream>
using namespace std;

Maze::Maze(int n):N(n), Min(0), Max(1)
{
    random_device rg;
    eng = default_random_engine(rg());
    generateSingleGapMaze();
}

Maze::~Maze()
{
    for (int i = 0; i < N+2; ++i)
    {
        delete[] north[i];
        delete[] east[i];
        delete[] west[i];
        delete[] south[i];
    }

    delete[] north;
    delete[] east;
    delete[] west;
    delete[] south;
}

int Maze::toX(int pos)
{
    return pos % N + 1;
}

int Maze::toY(int pos)
{
    return pos / N + 1;
}

int Maze::xyTo1D(int x, int y)
{
    return (y-1) * N + x - 1; 
}

int Maze::targetX(int x, string s)
{
    if (s == "W" || s == "NW" || s == "SW")
    {
        return x-1;
    }
    if (s == "E" || s == "NE" || s == "SE")
    {
        return x+1;
    }
    return x;
}

int Maze::targetY(int y, string s)
{
    if (s == "N" || s == "NE" || s == "NW")
    {
        return y+1;
    }
    if (s == "S" || s == "SE" || s == "SW")
    {
        return y-1;
    } 
    return y;
}

bool Maze::wallExist(int x, int y, string dir)
{
    int tx = targetX(x, dir);
    int ty = targetY(y, dir);
    bool outBound = (tx == 0 || ty == 0 || tx == N+1 || ty == N+1);

    if (outBound)
    {
        return true;
    }

    if (dir == "N")
    {
        return north[x][y];
    }

    if (dir == "E")
    {
        return east[x][y];
    }

    if (dir == "W")
    {
        return west[x][y];
    }

    if (dir == "S")
    {
        return south[x][y];
    }

    if (dir == "NW")
    {
        return ((west[x][y] && west[x][y+1]) || (west[x][y+1] && north[x-1][y]) || (north[x-1][y] && north[x][y]));
    }

    if (dir == "NE")
    {
        return ((east[x][y] && east[x][y+1]) || (east[x][y+1] && north[x+1][y]) || (north[x+1][y] && north[x][y]));
    }

    if (dir == "SW")
    {
        return ((west[x][y] && west[x][y-1]) || (west[x][y-1] && south[x-1][y]) || (south[x-1][y] && south[x][y]));
    }

    if (dir == "SE")
    {
        return ((east[x][y] && east[x][y-1]) || (east[x][y-1] && south[x+1][y]) || (south[x+1][y] && south[x][y]));
    }

    return true;
}

set<int> Maze::adj(int pos)
{
    int x = toX(pos);
    int y = toY(pos);
    set<int> neighbors;

    if (!wallExist(x, y, "N"))
    {
        neighbors.insert(xyTo1D(x, y+1));
    }

    if (!wallExist(x, y, "W"))
    {
        neighbors.insert(xyTo1D(x-1, y));
    }

    if (!wallExist(x, y, "E"))
    {
        neighbors.insert(xyTo1D(x+1, y));
    }

    if (!wallExist(x, y, "S"))
    {
        neighbors.insert(xyTo1D(x, y-1));
    }

    if (!wallExist(x, y, "NW"))
    {
        neighbors.insert(xyTo1D(x-1, y+1));
    }

    if (!wallExist(x, y, "NE"))
    {
        neighbors.insert(xyTo1D(x+1, y+1));
    }

    if (!wallExist(x, y, "SW"))
    {
        neighbors.insert(xyTo1D(x-1, y-1));
    }

    if (!wallExist(x, y, "SE"))
    {
        neighbors.insert(xyTo1D(x+1, y-1));
    }

    return neighbors;
}


void Maze::generateSGHelper(int x, int y, bool** marked)
{
    marked[x][y] = true;

    while (!marked[x][y+1] || !marked[x+1][y] || !marked[x][y-1] || !marked[x-1][y])
    {
        uniform_real_distribution<double> distr(Min, Max);
        while (true)
        {
            double r = distr(this->eng);

            if (r < 0.25 && !marked[x][y+1])
            {
                north[x][y] = south[x][y+1] = false;
                generateSGHelper(x, y+1, marked);
                break;
            }
            else if (r < 0.5 && !marked[x+1][y])
            {
                east[x][y] = west[x+1][y] = false;
                generateSGHelper(x+1, y, marked);
                break;
            }
            else if (r < 0.75 && !marked[x][y-1])
            {
                south[x][y] = north[x][y-1] = false;
                generateSGHelper(x, y-1, marked);
                break;
            }
            else if (r < 1.00 && !marked[x-1][y])
            {
                west[x][y] = east[x-1][y] = false;
                generateSGHelper(x-1, y, marked);
                break;
            }
        }
    }
}

void Maze::generateSingleGapMaze()
{
    //bool marked[N+2][N+2];
    bool** marked = new bool*[N+2];
    for (int x = 0; x < N+2; ++x)
    {
        marked[x] = new bool[N+2];
        marked[x][0] = true;
        marked[x][N+1] = true;
    }
    for (int y = 0; y < N+2; ++y)
    {
        marked[0][y] = true;
        marked[N+1][y] = true;
    }

    north = new bool*[N+2];
    east = new bool*[N+2];
    west = new bool*[N+2];
    south = new bool*[N+2];
    for (int i = 0; i < N+2; ++i)
    {
        north[i] = new bool[N+2];
        east[i] = new bool[N+2];
        west[i] = new bool[N+2];
        south[i] = new bool[N+2];
        for (int j = 0; j < N+2; ++j)
        {
            north[i][j] = east[i][j] = west[i][j] = south[i][j] = true;
        }
    }
    generateSGHelper(1, 1, marked);
}

int Maze::getV()
{
    return N*N;
}

int Maze::getN()
{
    return N;
}

void Maze::drawInConsole()
{
    for (int y = 2*N+1; y > 0; --y)
    {
        int realY = (y+1) / 2;
        for (int x = 0; x < N+2; ++x)
        {
            if (y == 2*N+1)
            {
                if (x == 0)
                {
                     cout << "__";
                }
                else if (x < N+1)
                {
                    cout << setw(4) << left << "_";
                }
            }
            else if (y % 2 == 0)
            {
                if (x == 0)
                {
                    cout << " |";
                }
                else if (x < N+1)
                {
                    if (east[x][y / 2])
                    {
                       cout << setw(3) << left << xyTo1D(x, realY) << "|" ;
                    }
                    else
                    {
                        cout << setw(3) << left << xyTo1D(x, realY) << " ";
                    }
                }
            }
            else
            {
                if (x == 0)
                {
                    cout << "  ";
                }
                else if (x < N+1)
                {
                    if (south[x][(y+1) / 2])
                    {
                        cout << setw(4) << left << "- ";
                    }
                    else
                    {
                        cout << setw(4) << left << "  ";
                    }
                }
            }
        }
        cout << '\n';
    }
}


/*    ___   _  _  _  
*     4|16| g  g  g|
*       -  - 
*     3 g g|g g
*     2 g g|g g
*     1 g g|g g   
*       1 2 3 4
*/
