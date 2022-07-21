#include "Cell.h"

Cell::Cell()
    : m_x(0), m_y(0), m_visited(false), m_type(Type::SPACE), m_exteriorWall(false), m_innerWall(false)
{

}

Cell::~Cell()
{
    //dtor
}

char Cell::getType()
{
    switch(m_type)
    {
        case Type::EXTERIOR_WALL:
            return '@';

        case Type:: INNER_WALL:
            return '#';

        case Type::SPACE:
            return ' ';

        case Type::PATH:
            return '.';

        case Type::START:
            return 'S';

        case Type::END:
            return 'E';

        default:
            return '.';

    }
}

void Cell::setType(Cell::Type type)
{
    m_type = type;
}


bool Cell::getVisited()
{
    return m_visited;
}

void Cell::setVisited(bool visited)
{
    m_visited = visited;
}





