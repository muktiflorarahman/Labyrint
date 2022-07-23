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

    return 0;
}
