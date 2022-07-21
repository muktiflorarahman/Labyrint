#include <iostream>
#include "Labyrint.h"
#include "Cell.h"
#include <cstddef>
#include <string>


int main()
{
    Labyrint* labyrint = new Labyrint;
    labyrint->run();

    delete labyrint;
    labyrint = nullptr;
    //size_t width = 11;
    //size_t height = 11;
    //Labyrint* labyrint= new Labyrint(width, height);
    //labyrint->initGenerator();

    return 0;
}
