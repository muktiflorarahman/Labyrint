/*
Namn: Mukti Flora Rahman
Kurs: Objektbaserad programmering i C++
Program: Civilingenjör datateknik
Betyg: E-C
Datum: 2022-07-23
*/
#include "Cell.h"
#include <iostream>


Cell::Cell()
    : m_x(0), m_y(0), m_visited(false), m_type(Type::SPACE), m_exteriorWall(false), m_innerWall(false)
{

}

// Destructor
Cell::~Cell()
{
    std::cout << "Inside destructor" << std::endl;
}

//get-type funktion
//switch sats för de olika typerna i labyrint, väggar

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
//set funktion för att sätta variabeln m_type
void Cell::setType(Cell::Type type)
{
    m_type = type;
}

//funktion för att se vilka som har besökts
//returnerar därför variabeln m_visited
bool Cell::getVisited()
{
    return m_visited;
}

//set funktionn för att sätta variabeln m_visited
void Cell::setVisited(bool visited)
{
    m_visited = visited;
}




