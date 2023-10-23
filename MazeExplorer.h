#ifndef MAZEEXPLORER_H_
#define MAZEEXPLORER_H_
#include "Maze.h"

class MazeExplorer
{
protected:
    int* disTo;

    int* edgeTo;

    bool* marked;

    Maze* maze;

    static const int MAX_VALUE = 123456789;
public:
    MazeExplorer(Maze* m)
    {
        maze = m;

        disTo = new int[maze->getV()];
        edgeTo = new int[maze->getV()];
        marked = new bool[maze->getV()];

        for (int i = 0; i < maze->getV(); ++i)
        {
            disTo[i] = MAX_VALUE;
            edgeTo[i] = MAX_VALUE;
        }
    }

    ~MazeExplorer()
    {
        delete[] disTo;
        delete[] edgeTo;
        delete[] marked;
    }

    virtual void solve() = 0;

    virtual void printPath() = 0;

    int* getDisTo()
    {
        return disTo;
    }

    int* getEdgeTo()
    {
        return edgeTo;
    }
};



#endif