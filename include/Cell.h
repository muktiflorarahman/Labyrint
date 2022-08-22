/*
Namn: Mukti Flora Rahman
Kurs: Objektbaserad programmering i C++
Program: Civilingenjör datateknik
Betyg: E-C
Datum: 2022-07-23
*/
#ifndef CELL_H
#define CELL_H
#include <cstddef>

class Labyrint;

class Cell
{
    friend class Labyrint;
public:
    enum class Type
    {
        EXTERIOR_WALL = '@',
        INNER_WALL = '#',
        SPACE = ' ',
        PATH = '.',
        START = 'S',
        END = 'E'
    };

    Cell();
    virtual ~Cell();
    char getType();
    void setType(Cell::Type);
    bool getVisited();
    void setVisited(bool);



private:
    //kolumn variabel x, rad variabel y
    size_t m_x;
    size_t m_y;
    bool m_visited;
    Type m_type;
    bool m_exteriorWall;
    bool m_innerWall;
};

#endif // CELL_H
