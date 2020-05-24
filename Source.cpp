#include "Header.hpp"


void System::internal_hide_consol_cursor()
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    bool showFlag = false;
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

string System::internal_get_file_content(const string path)
{
    /*
	    Utiliza um iterator - ponteiros para enderecos de memoria- para construir uma string com os dados da ifstream - input file stream.
		- istreambuf_iterator<char>(file)) = iterator para o inicio do arquivo
		- istreambuf_iterator<char>() = iterator para o final do arquivo
	*/

    ifstream file("Map.txt"); // Ponteiro para o local do arquivo
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    return content;
}

int System::internal_generate_ramdom_number()
{
    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937 mt_rand(seed);
    return mt_rand();
}

int System::internal_set_x(int one_dimension_position)
{
    return one_dimension_position % Map::get_width();
}

void System::internal_gotoxy(short x, short y)
{
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

void System::internal_go_to_console_position(int one_dimension_position){
    System::gotoxy(one_dimension_position % Map::get_width(), one_dimension_position / Map::get_width());
}

COORD System::internal_getxy(CONSOLE_SCREEN_BUFFER_INFO *csbi)
{
    COORD coord = csbi->dwCursorPosition;
    return coord;
}

char System::internal_get_cursor_char()
{
    char c = '\0';

    CONSOLE_SCREEN_BUFFER_INFO con;
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hcon != INVALID_HANDLE_VALUE && GetConsoleScreenBufferInfo(hcon, &con))
    {
        DWORD read = 0;
        if (!ReadConsoleOutputCharacterA(hcon, &c, 1, con.dwCursorPosition, &read) || read != 1)
            c = '\0';
    }
    return c;
}

int System::internal_set_y(int one_dimension_position)
{
    return one_dimension_position / Map::get_width();
}

Timer::Timer()
{
    this->clock = 0;
}

void Timer::start()
{
    m_StartTime = std::chrono::system_clock::now();
    m_bRunning = true;
}

void Timer::stop()
{
    m_EndTime = std::chrono::system_clock::now();
    m_bRunning = false;
}

double Timer::elapsedMilliseconds()
{
    std::chrono::time_point<std::chrono::system_clock> endTime;

    if (m_bRunning)
        endTime = std::chrono::system_clock::now();
    else
        endTime = m_EndTime;

    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
}

Timer Timer::update()
{
    stop();
    clock = clock + elapsedMilliseconds();
    return *this;
}

Timer Timer::print()
{
    printf("%0.1f\n", clock / 1000.0);
    return *this;
}


string Map::canvas;
Map::Map() : width(calculate_width()), height(calculate_height()) {}
int Map::calculate_width() { return (canvas.find('\n') + 1); }
int Map::calculate_height() { return (canvas.size() / width) + 1; }
int Map::internal_get_width() { return width; }
int Map::internal_get_height() { return height; }

void Map::internal_print()
{
    System::gotoxy(0, 0);
    
    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 120);
    //cout <<"\033[40;64m"<< Map::canvas <<"\033[0m"<<'\n';
    cout << GRAY_CHAR << Map::canvas << RESET_COLOR_SCHEME;
    
    //cout<<"\033[3;100;30m"<< Map::canvas<<"\033[0m\n";
}

void print_score(int map_height, int score, int lives)
{
    System::gotoxy(1, map_height + 2);
    cout << "Score: " << score << endl;
    System::gotoxy(1, map_height + 3);
    cout << "Lives: " << lives << endl;
}

Fruit::Fruit()
{
    this->fruit_position = find_position();
    this->x = System::set_x(fruit_position);
    this->y = System::set_y(fruit_position);
}

int Fruit::find_position()
{
    int fruit_position = Map::canvas.find(FRUIT);
    return fruit_position;
}

int Fruit::get_position()
{
    return fruit_position;
}

void Fruit::generate_position()
{
    int new_fruit_position;
    int fruit_x_position;
    int fruit_y_position;

    do
    {
        new_fruit_position = System::generate_ramdom_number() % Map::canvas.length();
    } while (Map::canvas.at(new_fruit_position) != ' ');

    this->x = new_fruit_position % Map::get_width();
    this->y = new_fruit_position / Map::get_width();
}

void Fruit::draw()
{
    System::gotoxy(x, y);
    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 126 | FOREGROUND_INTENSITY);
    cout << YELLOW_CHAR << FRUIT << RESET_COLOR_SCHEME;
    
}

tuple<int, int> Fruit::get_coord()
{
    return tie(x, y);
}

void Fruit::generate()
{
    generate_position();
    draw();
}




void print_colour_scheme()
{
    int i, j, n;

    for (i = 0; i < 11; i++)
    {
        for (j = 0; j < 10; j++)
        {
            n = 10 * i + j;
            if (n > 108)
                break;
            printf("\033[%dm %3d\033[m", n, n);
        }
        printf("\n");
    }


}