/*
Namn: Mukti Flora Rahman
Kurs: Objektbaserad programmering i C++
Program: Civilingenjör datateknik
Betyg: E-C
Datum: 2022-07-23
*/
#include <iostream>
#include "Labyrint.h"
#include "Cell.h"
#include <cstddef>
#include <string>

// main funktion
// skapar en ny labyrint
// kör labyrint programmet
//raderar labyrinten
//sätter labyrint pekaren till nullpointer
int main()
{
    Labyrint* labyrint = new Labyrint;
    labyrint->run();

    delete labyrint;
    labyrint = nullptr;

    return 0;
}
