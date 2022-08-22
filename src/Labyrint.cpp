/*
Namn: Mukti Flora Rahman
Kurs: Objektbaserad programmering i C++
Program: Civilingenjör datateknik
Betyg: E-C
Datum: 2022-07-23
*/

#include "Labyrint.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>

const size_t WIDTH = 11;
const size_t HEIGHT = 11;

Labyrint::Labyrint()
    : m_width( WIDTH ), m_height( HEIGHT )
{ }

Labyrint::Labyrint(size_t width, size_t height)
    : m_width(width), m_height(height)
{ }

// Destructor
Labyrint::~Labyrint()
{
    std::cout << "Inside destructor" << std::endl;
}

//funktion för att köra igång programmet
void Labyrint::run()
{
    bool programIsRunning = true;
    while(programIsRunning == true)
    {
        info();
        char choice = getChoice();

        switch(choice)
        {
            //skapar en ny labyrint
            case '1':
            {
                generateLabyrint();
                break;
            }
            //visar projekt info
            case '2':
            {
                project();
                break;
            }
            //avslutar programmet
            case '3':
            {
                exit(0);
                break;
            }

            default:
                break;
        }

        // frågar ifall användaren vill fortsätta köra programmet
		std::string again;
		std::cin.clear();
		std::cout << "\nDo you want to run the program again? (y/n) \n=> ";
		std::cout.flush();

		std::getline( std::cin, again );
		char agn = again[ 0 ];
		agn = tolower( agn );

		bool validReply = false;

		if ( ( agn == 'y' || agn == 'n' ) && again.length() == 1 )
		{
			validReply = true;
		}
        else
		{
			while ( !validReply )
			{
				std::cin.clear();
				std::cout << "\nDo you want to run the program again? (y/n) \n=> ";
				std::cout.flush();

				std::getline( std::cin, again );
				agn = again[ 0 ];
				agn = tolower( agn );

				if ( ( agn == 'y' || agn == 'n' ) && again.length() == 1 )
				{
					validReply = true;
				}
			}
		}
		// användar vill avsluta programmet
		if ( agn == 'n' )
		{
			programIsRunning = false;
			exit( 0 );
		}

    }
}

//Funktion som generar labyrint programmet
//sätter medlemsvariabler
//ändrar storlek på vektorn
void Labyrint::generateLabyrint()
{
    m_width = WIDTH;
    m_height = HEIGHT;
    m_cells.resize( m_height, std::vector<Cell*>( m_width ) );

    initGenerator();
    resetLabyrint();
}

//funktion som nollställer labyrinten
void Labyrint::resetLabyrint()
{
    m_width = 0;
    m_height = 0;

    deletePointers();
    m_cells.resize(m_height, std::vector<Cell*>( m_width )); // sätta storlek på m_cells
    clearStack();
    std::fill( m_neighbors.begin(), m_neighbors.end(), false );
}

//funktionen som tar bort pointers
void Labyrint::deletePointers()
{
    for ( size_t row = 0; row < m_height; row++ )
    {
        for ( size_t col = 0; col < m_width; col++ )
        {
            delete m_cells[row][col]; // raderar lagrad pointer
        }
    }
}

void Labyrint::clearStack()
{
    while ( m_pathStack.empty() == false )
    {
        m_pathStack.pop();
    }
}

//styr skapandet av labyrint
void Labyrint::initGenerator()
{
    create();
    updateGenerator();
    draw();
    createPath();
}

//för varje rad skapas en rad vektorn
//som ska ha cellpekare
//cellen får olika koordinater, m_x, m_y
void Labyrint::create()
{
    for(size_t row = 0; row < m_height; row++)
    {
        std::vector<Cell*> rowVector;

        for(size_t col = 0; col < m_width; col++)
        {
            Cell* cell = new Cell();
            cell->m_x = col;
            cell->m_y = row;
            rowVector.push_back(cell);
        }

        m_cells[row] = rowVector;
    }
}
//uppdatera alla celler
//få till ytterväggar och innerväggar
//steget innan det skapas en riktig labyrint
void Labyrint::updateGenerator()
{
    for(size_t row = 0; row < m_cells.size(); row++)
    {
        for(size_t col =0;  col < m_cells[row].size(); col++)
        {
            //sätter ytterväggarna,
            if(row == 0 || col == 0 || row == m_cells.size()-1|| col == m_cells[0].size()-1)
            {
                m_cells[row][col]->m_type = Cell::Type::EXTERIOR_WALL;
                m_cells[row][col]->m_exteriorWall = true;
            }
            //sätter hålrum
            else if(row % 2 == 1 && col % 2 == 1)
            {
                m_cells[row][col]->m_type = Cell::Type::SPACE;
            }
            //sätter innerväggar
            else
            {
                m_cells[row][col]->m_type = Cell::Type::INNER_WALL;
                m_cells[row][col]->m_innerWall = true;
            }
        }
    }
    //sätter start samt slut cell
    m_cells[1][0]->m_type = Cell::Type::START;
    m_cells[m_height-2][m_width-1]->m_type = Cell::Type::END;
}


//funktion för att rita ut labyrinten i konsolen
//loopar först igenom m_cells med avseende på rader
//loopar igenom vektorn med avseende på kolumner
//för att få reda på typ
void Labyrint::draw()
{
    std::cout << std::string(125,'\n') << std::endl;

    for(size_t row = 0; row < m_cells.size(); row++)
    {
        for(size_t col =0;  col < m_cells[row].size(); col++)
        {
            std::cout << m_cells[row][col]->getType();
        }
        std::cout << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
}

//följer algoritmen DFS
void Labyrint::createPath()
{
// - Markera alla noder som obesökta.
// - Välj en startnod och låt den vara nuvarande nod N.
// - Markera N som besökt.
// - Lägg till N till en stack S.

// - Så länge som S inte är tom:
// - Hämta en nod från S och låt den vara N.

// - Om N har obesökta grannar:
// - Lägg till N till S.
// - Välj slumpmässigt en obesökt granne G.
// - Öppna kopplingen mellan N och G.
// - Markera G som besökt.
// - Lägg till G till S.


    //markera alla noder som obesökta - gjort i Cell konstruktorn
    //Välj en startnod och låt den vara nuvarande nod N
    Cell* neighbor = nullptr;
    Cell* oldWall = nullptr;

    Cell* current = m_cells[1][1];
    //markera N som besökt
    //därför pekar instansen av cellpekaren current på m_visited
    //som sätts till true
    current->m_visited = true;

    //lägg till nod N till en stack S
    //lägger till current i stacken m_pathStack
    m_pathStack.push(current);

    //så länge som stack S inte är tom
    while(m_pathStack.empty() == false)
    {
        //hämta en nod från stacken S och låt den vara nod N
        current = m_pathStack.top();
        //tar bort cellen från stacken
        m_pathStack.pop();

        //om nod N har obesökta grannar
        if(unvisitedNeighbors(current))
        {
           //std::cout << "inne i if-unvisitedNeighbors" << std::boolalpha << m_neighbors[0] << m_neighbors[1] << m_neighbors[2] << m_neighbors[3] << std::endl;
           //lägg till nod N i stack S
           m_pathStack.push(current);
           Direction direction = selectDirection();

           //öppna kopplingen mellan N och G
           switch(direction)
           {
                case Direction::UP: {
                    oldWall = m_cells[current->m_y - 1][current->m_x];
                    neighbor = m_cells[current->m_y - 2][current->m_x];
                    break;
                }

                case Direction::RIGHT: {
                    oldWall = m_cells[current->m_y][current->m_x + 1];
                    neighbor = m_cells[current->m_y][current->m_x + 2];
                    break;
                }

                //1 steg nedåt-oldwall som ska rivas
                //2 steg nedåt är grannen som vi ska gå till
                case Direction::DOWN: {
                    oldWall = m_cells[current->m_y + 1][current->m_x];
                    neighbor = m_cells[current->m_y + 2][current->m_x];
                    break;
                }

                case Direction::LEFT: {
                    oldWall = m_cells[current->m_y][current->m_x - 1];
                    neighbor = m_cells[current->m_y][current->m_x - 2];
                    break;
                }

                default:
                    break;
           }
           // - Markera G som besökt.
           //grannen som vi är på väg till är besökt
           neighbor->setVisited(true);
           //här sker rivningen av innerväggen
           oldWall->setType(Cell::Type::SPACE);
           //sätter den som besökt
           oldWall->setVisited(true);
           // - Lägg till G till S.
           //lägger till den besökta grannen till stacken
           m_pathStack.push(neighbor);
           draw();
        }
    }
}

//fyller vektorn med false för obesökta grannar

bool Labyrint::unvisitedNeighbors(Cell* cell)
{
    std::fill(m_neighbors.begin(),m_neighbors.end(), false);
    size_t x = cell->m_x;
    size_t y = cell->m_y;

   // std::cout << "size of m_neighbors vec: " << m_neighbors.size() << std::endl;

    bool visited = false;

    //söker celler uppåt, rör sig i y-axeln
    //om cellen ovanför inte är en yttervägg
    //då kollar vi om cellen 2 steg ovanför är obesökt
    if(m_cells[y-1][x]->m_exteriorWall == false && m_cells[y-2][x]->m_visited == false)
    {
        m_neighbors[0] = true;
        visited = true;
    }

    //söker celler åt höger
    //rör sig till höger på x-axeln
    //om cellen åt höger inte är en yttervägg
    //då kollar vi om cellen 2 steg åt höger är obesökt
    if(m_cells[y][x+1]->m_exteriorWall == false && m_cells[y][x+2]->m_visited == false)
    {
        m_neighbors[1] = true;
        visited = true;
    }

    //söker celler nedåt
    //rör sig nedåt på y-axeln
    //om cellen nedåt inte är en yttervägg
    //då kollar vi om cellen 2 sted nedåt är obesökt
    if(m_cells[y+1][x]->m_exteriorWall == false && m_cells[y+2][x]->m_visited == false)
    {
        m_neighbors[2] = true;
        visited = true;
    }

    //söker celler åt vänster, -1 är vänster på x-axeln
    //rör sig till vänster på x-axeln
    //om cellen åt vänster inte är en yttervägg
    //då kollar vi om cellen 2 steg åt vänster är obesökt
    if(m_cells[y][x-1]->m_exteriorWall == false && m_cells[y][x-2]->m_visited == false)
    {
        m_neighbors[3] = true;
        visited = true;
    }
    return visited;
}

//funktion för att välja riktning
//skapar en vektor med möjliga riktningar
//loopar igenom vektorn
//if sats för att se om pos i vec. m_neigbors är true
//då läggs den pos i vec possibleDirections
Labyrint::Direction Labyrint::selectDirection()
{
    std::vector<int> possibleDirections;
    for (size_t i = 0; i < m_neighbors.size(); i++)
    {
        if (m_neighbors[i] == true)
        {
            possibleDirections.push_back(i);
        }
    }

    int randomNum = generateRandomNum(possibleDirections);
    return (Direction) randomNum;
}


//skriver ut vektorn m_neighbours
void Labyrint::printVector(std::vector <bool> const &a) {
   std::cout << "The vector elements are : ";

   for (size_t i=0; i < a.size(); i++)
   {
    std::cout << std::boolalpha << a.at(i) << ' ';
   }
}

//funktion för att generera ett slumpmässigt tal
int Labyrint::generateRandomNum(std::vector<int> const& v)
{
    std::random_device random_device;
    std::mt19937 engine{random_device()};
    std::uniform_int_distribution<int> dist(0, v.size() - 1);

    //slumpar fram ett tal från fördelningsdistributionen
    //där slängs födelningsmaskinen in
    int random_number = dist(engine);
    int random_element = v[random_number];

    return random_element;
}

//get funktion för val vid meny i terminalen
//användaren kan bara skriva in input mellan 1-3
// returnerar char
char Labyrint::getChoice()
{
    std::string choice;
	std::cin.clear();
	std::getline( std::cin, choice );
	char ch = choice[ 0 ];

	while ( choice.length() != 1 || ch < '1' || ch > '3' )
	{
		std::cout << "Invalid input. Try again with number from 1 to 3\n=> ";
		std::cout.flush();

		std::cin.clear();
		std::getline( std::cin, choice );
		ch = choice[ 0 ];
	}

	return ch;
}

//info funktion om programmet
void Labyrint::info()
{
    std::cout << std::string(100, '\n') << std::endl;
    std::cout << std::string(70, '=') << std::endl;

    std::cout << infoText() << std::endl;
    std::cout << std::string(70, '=') << std::endl;

    std::cout << "\nPlease make a choice. Press 1, 2 or 3 and then enter: " << std::endl;
}

//projekt funktion
void Labyrint::project()
{
    std::cout << std::string(100, '\n') << std::endl;
    std::cout << std::string(70, '=') << std::endl;

    std::cout << projectInfo() << std::endl;
    std::cout << std::string(70, '=') << std::endl;

    std::cout << "\nPlease make a choice. Press 1, 2 or 3 and then enter: " << std::endl;

}

//funktion för att läsa in textfil
//textfil för information
std::string Labyrint::infoText()
{
    std::string infoText = ""; //texten sparas
    std::string line = "";
    std::string fileName = "info.txt";

    std::ifstream readIn;
    readIn.open(fileName);

    while(std::getline(readIn, line))
    {
        infoText += "\t" + line + "\n";
    }
    readIn.close();
    return infoText;
}

//funktion för att läsa in textfil
//textfil för informatiom om projektet
std::string Labyrint::projectInfo()
{
    std::string projectText = "";
    std::string line = "";
    std::string fileName = "projectdescription.txt";

    std::ifstream readIn;
    readIn.open(fileName);

    while(std::getline(readIn, line))
    {
        projectText += line + "\n";
    }
    readIn.close();
    return projectText;
}
