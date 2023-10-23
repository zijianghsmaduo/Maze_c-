#include"Maze.h"
#include"MazeExplorer.h"
#include<cmath>
#include<iostream>
#include<iomanip>
#include"stdlib.h"
using namespace std;

class DepthFirstMazeSolver: public MazeExplorer
{
private:
    int s;
    int t;

    bool targetFound = false;

    bool isGoSideway(int after, int before)
    {
        int dis = abs(after-before);
        if (dis == maze->getV() || dis == 1)
        {
            return false;
        }

        return true;
    }

    void dfs(int v)
    {
        marked[v] = true;
        if (v == t)
        {
            targetFound = true;
        }

        if (targetFound)
        {
            return;
        }

        for (int elem: maze->adj(v))
        {
            if (!marked[elem])
            {
                edgeTo[elem] = v;
                if (isGoSideway(elem, v))
                {
                    disTo[elem] = disTo[v] + 2;
                }
                else
                {
                    disTo[elem] = disTo[v] + 1;
                }
                dfs(elem);
                if (targetFound)
                {
                    return;
                }
                
            }
        }
    }

public:
    DepthFirstMazeSolver(Maze* m, int sourceX, int sourceY, int targetX, int targetY):MazeExplorer(m)
    {
        s = maze->xyTo1D(sourceX, sourceY);
        t = maze->xyTo1D(targetX, targetY);

        disTo[s] = 0;
        edgeTo[s] = s;
    }

    virtual void solve() override
    {
        dfs(s);
        printPath();
    }

    virtual void printPath() override
    {
        int pos = t;
        if (targetFound)
        {
            cout << t << ' ';
            while (edgeTo[pos] != pos)
            {
                cout << "<- " << edgeTo[pos] << ' ';
                pos = edgeTo[pos];
            }
            cout << endl;
        }
        else
        {
            cout << "Target not found!" << endl;
        }
        
       /*
       for (int i = 0; i < maze->getV(); ++i)
       {
            cout << setw(3) << edgeTo[i] << ' ';
       }
       cout << endl;
       for (int i = 0; i < maze->getV(); ++i)
       {
            cout << setw(3) << i << ' ';
       }
       */
    }
};

int main()
{
    Maze maze(4);

    DepthFirstMazeSolver mdfp(&maze, 1, 1, 4, 4);
    //getchar();
    //cout << "1" << endl;
    maze.drawInConsole();
    getchar();
    //system("pause");
    cout << endl;
    mdfp.solve();
    cout << endl;
}