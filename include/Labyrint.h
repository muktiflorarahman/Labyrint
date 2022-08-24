/*
Namn: Mukti Flora Rahman
Kurs: Objektbaserad programmering i C++
Program: Civilingenjör datateknik
Betyg: E-C
Datum: 2022-07-23
*/

#ifndef LABYRINT_H
#define LABYRINT_H
#include "Cell.h"
#include <cstddef>
#include <vector>
#include <stack>
#include <string>

class Labyrint
{
private:
    size_t m_width { 0 };
    size_t m_height { 0 };

    std::vector<std::vector<Cell*>> m_cells;

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
    ~Labyrint();

    void run();


    //kommentarer från jimmy
    //implementera destruktor
    //flytta bool neighbors till respektive funktion, som en lokal variabel
    //flytta pathStack till respektive funktion som lokal variabel


private:
    void generateLabyrint();
    void resetLabyrint();
    void deletePointers();
    void initGenerator();
    void create();
    void updateGenerator();
    void draw();
    void createPath();
    std::vector<bool>unvisitedNeighbors(Cell* cell);
    Direction selectDirection(std::vector<bool>&);
    void printVector(std::vector<bool> const&);
    int generateRandomNum(std::vector<int> const& v);
    char getChoice();
    void info();
    void project();
    std::string infoText();
    std::string projectInfo();

};

#endif // LABYRINT_H
