#include "Labyrint.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>

const size_t WIDTH = 11;
const size_t HEIGHT = 11;

Labyrint::Labyrint(size_t width, size_t height)
    : m_width(width), m_height(height), m_neighbors(4, false)
{
    std::cout << width << height << std::endl;
}

Labyrint::Labyrint()
    : m_width(WIDTH), m_height(HEIGHT)
{

}

Labyrint::~Labyrint()
{
    //dtor
}

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
                initGenerator();
                break;
            }
            //visar projekt info
            case '2':
            {
                projectInfo();
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

    }

    // ask if user wants to keep running program
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

		// user wants to quit
		if ( agn == 'n' )
		{
			programIsRunning = false;
			exit( 0 );
		}

   //labyrint->initGenerator();
}

void Labyrint::initGenerator()
{
    create();
    updateGenerator();
    draw();
    createPath();
}

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
        m_cells.push_back(rowVector);
    }
}

void Labyrint::updateGenerator()
{
    for(size_t row = 0; row < m_cells.size(); row++)
    {
        for(size_t col =0;  col < m_cells[row].size(); col++)
        {
            //sätter ytterväggarna
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
    std::this_thread::sleep_for(std::chrono::milliseconds(750));
}

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
    //TODO
    //Felsöka m_cells vektor
    Cell* current = m_cells[1][1];

    //markera N som besökt
    current->m_visited = true;

    //lägg till N till en stack S
    m_pathStack.push(current);

    //så länge som S inte är tom
    while(m_pathStack.empty() == false)
    {
        //hämta en nod från stacken S och låt den vara nod N
        current = m_pathStack.top();
        //tar bort cellen från stacken
        m_pathStack.pop();

        //om N har obesökta grannar
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
           neighbor->setVisited(true);
           oldWall->setType(Cell::Type::SPACE);
           oldWall->setVisited(true);
           // - Lägg till G till S.
           m_pathStack.push(neighbor);
           draw();
        }
    }
}

bool Labyrint::unvisitedNeighbors(Cell* cell)
{
    std::fill(m_neighbors.begin(),m_neighbors.begin() + 4, false);
    size_t x = cell->m_x;
    size_t y = cell->m_y;

   // std::cout << "size of m_neighbors vec: " << m_neighbors.size() << std::endl;

    bool visited = false;

    //söker celler uppåt
    if(m_cells[y-1][x]->m_exteriorWall == false && m_cells[y-2][x]->m_visited == false)
    {
        m_neighbors[0] = true;
        visited = true;
    }

    //söker celler åt höger
    if(m_cells[y][x+1]->m_exteriorWall == false && m_cells[y][x+2]->m_visited == false)
    {
        m_neighbors[1] = true;
        visited = true;
    }

    //söker celler nedåt
    if(m_cells[y+1][x]->m_exteriorWall == false && m_cells[y+2][x]->m_visited == false)
    {
        m_neighbors[2] = true;
        visited = true;
    }

    //söker celler åt vänster
    if(m_cells[y][x-1]->m_exteriorWall == false && m_cells[y][x-2]->m_visited == false)
    {
        m_neighbors[3] = true;
        visited = true;
    }
    return visited;
}

Labyrint::Direction Labyrint::selectDirection()
{
    std::vector<int> possibleDirections;
    //printVector(m_neighbors);
    for(int i = 0; i < m_neighbors.size(); i++)
    {
        if(m_neighbors[i] == true)
        {
            possibleDirections.push_back(i);
        }
    }
    int randomNum = generateRandomNum(possibleDirections);
    return (Direction) randomNum;

}

void Labyrint::printVector(std::vector <bool> const &a) {
   std::cout << "The vector elements are : ";

   for(int i=0; i < a.size(); i++)
   {
    std::cout << std::boolalpha << a.at(i) << ' ';
   }
}

int Labyrint::generateRandomNum(std::vector<int> const& v)
{
    std::random_device random_device;
    std::mt19937 engine{random_device()};
    std::uniform_int_distribution<int> dist(0, v.size() - 1);
    int random_element = v[dist(engine)];

    return random_element;

}

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

void Labyrint::info()
{
    std::cout << std::string(100, '\n') << std::endl;
    std::cout << std::string(70, '=') << std::endl;

    std::cout << infoText() << std::endl;
    std::cout << std::string(70, '=') << std::endl;

    std::cout << "\nPlease make a choice. Press 1, 2 or 3 and then enter: " << std::endl;


}

std::string Labyrint::infoText()
{
    std::string infoText = "";
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

void Labyrint::projectInfo()
{
    std::cout << "project info" << std::endl;

}


