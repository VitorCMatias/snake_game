#include "Header.hpp"

//g++ -O2 -std=c++17 header.h Source.cpp Main.cpp  -o m
//g++ -std=c++17 header.h Snake.cpp Source.cpp Main.cpp -o m

static uint32_t s_AllocCount = 0;

void *operator new(size_t size)
{
    s_AllocCount++;
    System::gotoxy(0, Map::get_height() + 3);
    cout << "\nAlocating " << size << "bytes\n";

    return malloc(size);
}

int main()
{
    Timer timer;

    Map::canvas = System::get_file_content("Map.txt");
    Head::set_coord();

    Fruit fruit;
    int lives = 1;
    int score = 0;
    int difficulty = 130;
    char key_pressed = MOVE_UP;

    System::show_consol_cursor();
    system("cls");
    Map::print();
    fruit.draw();

    /*
    char str[11];
    sprintf(str,"MODE %d, %d", Map::get_width(), Map::get_height() + 5);
    system(str);
    */

    while (!(GetAsyncKeyState('Q')) && lives > 0)
    {
        timer.start();
        Sleep(difficulty);

        if (_kbhit())
            key_pressed = toupper(_getch());
        Head::move(key_pressed);

        if (Head::get_colision())
            lives--;
        else
            Head::print();
            Tail::move();

        if (Head::get_coord() == fruit.get_coord())
        {
            Tail::increase_size();
            Tail::move();
            fruit.generate();
            score += 10;
        }

        System::gotoxy(0, Map::get_height() + 10);
        printf("Score: %d\n", score);
        timer.update().print();

    }
    system("cls");
    cout << s_AllocCount << " allocations\n";
    print_colour_scheme();
    return 0;
}


