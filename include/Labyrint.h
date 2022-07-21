#ifndef LABYRINT_H
#define LABYRINT_H
#include "Cell.h"
#include <cstddef>
#include <vector>
#include <stack>
#include <string>

class Labyrint
{
    public:
        enum class Direction
        {
            UP = 0,
            RIGHT = 1,
            DOWN = 2,
            LEFT = 3
        };
        Labyrint(size_t width, size_t height);
        Labyrint();
        virtual ~Labyrint();
        void initGenerator();
        void create();
        void updateGenerator();
        void draw();
        void createPath();
        bool unvisitedNeighbors(Cell*);
        Direction selectDirection();
        void printVector(std::vector<bool> const&);
        int generateRandomNum(std::vector<int> const& v);
        void run();
        char getChoice();
        void info();
        std::string infoText();
        void projectInfo();


    //protected:

    private:
        size_t m_startNode;;
        size_t m_endNode;
        size_t m_width;
        size_t m_height;
        std::vector<std::vector<Cell*>> m_cells;
        std::stack<Cell*> m_pathStack;
        std::vector<bool> m_neighbors;

};

#endif // LABYRINT_H

