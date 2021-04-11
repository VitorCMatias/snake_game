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

void System::internal_go_to_console_position(int one_dimension_position)
{
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

    cout << GRAY_CHAR << Map::canvas << RESET_COLOR_SCHEME;
}

void print_score(int map_height, int score, int lives)
{
    System::gotoxy(1, map_height + 2);
    cout << "Score: " << score << endl;
    System::gotoxy(1, map_height + 3);
    cout << "Lives: " << lives << endl;
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

void set_console_size()
{

    char str[11];
    sprintf(str, "MODE %d, %d", Map::get_width(), Map::get_height() + 5);
    system(str);
}

void test_sound()
{
    int f, t;
    while (!GetAsyncKeyState('Q'))
    {
        if (GetAsyncKeyState('V'))
        {
            fflush(stdin);
            cin >> f;
        }
        if (GetAsyncKeyState('P'))
            Beep(f, 100);
    }
    //532Hz, 500ms
    //cout << s_AllocCount << " allocations\n";
    //220Hz good for menu
}

void print_information(int lives, int score, Timer &timer)
{

    const int map_height = Map::get_height();
    const int map_width = Map::get_width();
    for (int i = 0; i < 3; i++)
    {
        System::gotoxy(0, map_height + i);
        for (int j = 0; j < map_width - 1; j++)
        {
            if (i != 0 && i != 1)
            {
                cout << GRAY_CHAR << '#' << RESET_COLOR_SCHEME;
            }
            else
            {
                System::gotoxy(0, map_height + i);
                cout << GRAY_CHAR << "##" << RESET_COLOR_SCHEME;
                System::gotoxy(map_width - 3, map_height + i);
                cout << GRAY_CHAR << "##" << RESET_COLOR_SCHEME;
            }
        }
        printf("\n");
    }

    System::gotoxy(4, map_height);
    printf("LIVES");
    System::gotoxy(6, map_height + 1);
    printf("%d", lives);

    System::gotoxy(24, map_height);
    printf("SCORE");

    if (score < 100)
        System::gotoxy(26, map_height + 1);
    else
        System::gotoxy(26 - (calculate_digits(score) - 3), map_height + 1);

    printf("%d", score);

    System::gotoxy(map_width - 8, map_height);
    printf("TIME");
    System::gotoxy(map_width - 8, map_height + 1);
    timer.update().print();
    /*if (timer < 100.0)
        printf("%0.1f", timer);
    else
        printf("%d", int(timer));*/
}

void show_consol_cursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

int calculate_digits(int val)
{
    int i = 0;
    while (val)
    {
        val = val / 10;
        i++;
    }

    return i;
}

void System::internal_welcome_screen(char &choice)
{
    
    
    system("cls");
    cout << "Snake Game\n";
    cout << "by Vitor Matias\n\n";
    cout << "1-New Game\n";
    cout << "2-Continue\n";
    cout << "3-Records\n";
    cout << "4-Quit\n";

    while (!GetAsyncKeyState('Q'))
    {
        if (_kbhit())
        {
            choice = toupper(_getch());
            imprimir_selecao_menu(choice);
        }
    }
}

void imprimir_selecao_menu(char &choice)
{
    switch (choice)
    {
    case '1':
    {
        system("cls");
        cout << "Snake Game\n";
        cout << "by Vitor Matias\n\n";
        cout << MENU_SELECTOR << "1-New Game\n"<< RESET_COLOR_SCHEME;
        cout << "2-Continue\n";
        cout << "3-Records\n";
        cout << "4-Quit\n";

        if(_kbhit())
        break;
    }
    case '2':
    {
        system("cls");
        cout << "Snake Game\n";
        cout << "by Vitor Matias\n\n";
        cout << "1-New Game\n";
        cout << MENU_SELECTOR << "2-Continue\n"<< RESET_COLOR_SCHEME;
        cout << "3-Records\n";
        cout << "4-Quit\n";
        break;
    }
    case '3':
    {
        system("cls");
        cout << "Snake Game\n";
        cout << "by Vitor Matias\n\n";
        cout << "1-New Game\n";
        cout << "2-Continue\n";
        cout << MENU_SELECTOR << "3-Records\n"<< RESET_COLOR_SCHEME;
        cout << "4-Quit\n";
        break;
    }
    case '4':
    {
        system("cls");
        cout << "Snake Game\n";
        cout << "by Vitor Matias\n\n";
        cout << "1-New Game\n";
        cout << "2-Continue\n";
        cout << "3-Records\n";
        cout << MENU_SELECTOR << "4-Quit\n"<< RESET_COLOR_SCHEME;
        break;
    }
    case '\n':

    default:
        break;
    }
}

void System::internal_write_file()
{
    ofstream myfile("Saves/example.txt");

    
    if (myfile.is_open())
    {
        myfile << Map::canvas;
        myfile.close();
    }
    else
        cout << "Unable to open file";
}

int System::internal_convert_coord_to_one_dimendion(const int x, const int y)
{
    return y * Map::get_width() + x;
}

void System::internal_update_map_to_print(int fruit_position){
    list<int> tail = Tail::get_tail();
    tail.pop_back();

    Map::canvas.replace(Head::get_position(), 1, "0");
    for(int node : tail){
        Map::canvas.replace(node, 1, "o"); 
    }

    Map::canvas.replace(fruit_position, 1, "*");

    
}