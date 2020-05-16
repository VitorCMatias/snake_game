#include "header.h"

//g++ -O2 -std=c++17 header.h Source.cpp Main.cpp  -o m
//g++ -std=c++17 header.h Snake.cpp Source.cpp Main.cpp -o m

static uint32_t s_AllocCount = 0;

void *operator new(size_t size)
{
    s_AllocCount++;
    cout << "\nAlocating " << size << "bytes\n";

    return malloc(size);
}

int main()
{
    Timer timer;
    System sys;

    Map::canvas = sys.get_file_content("Map.txt");
    Head::set_coord();

    Fruit fruit;
    int lives = 1;
    int score = 0;
    int difficulty = 80;
    char key_pressed = MOVE_UP;

    sys.show_consol_cursor(false);
    system("cls");
    Map::print();

    /*
    char str[11];
    sprintf(str,"MODE %d, %d", Map::get_width(), Map::get_height() + 5);
    system(str);
    */

    while (!(GetAsyncKeyState('Q')) && lives > 0)
    {
        Sleep(difficulty);
        timer.start();

        if (_kbhit())
            key_pressed = toupper(_getch());
        Head::move(key_pressed);
        if (Head::get_colision())
            lives--;
        else
            Head::print();

        gotoxy(0, Map::get_height() + 10);
        cout << "Hp: " << Head::get_position() << "\n";
        cout << "h: " << Map::get_height() << "\n";
        cout << "h_h: " << Head::get_position() % Map::get_height() << "\n";
        cout << "w: " << Map::get_width() << "\n";
        cout << "h_w: " << Head::get_position() % Map::get_width() << "\n";
        gotoxy(10, 0);
        char ch = get_cursor_char();
        //gotoxy(10, 60);
        //cout<<ch;

        /*if (Head::hit())
            lives--;
        else
        {
            Tail::update_position();
            Tail::move();
        }

        if (Head::get_position() == fruit.get_position())
        {
            Tail::increase_size();
            Tail::move();
            fruit.draw(Map::canvas);
            score += 10;
        }
        Sleep(difficulty);
        Map::print();*/

        //timer.update().print();
        //printf("Score: %d\n", score);

        //cout<<"\n"<<s_AllocCount<<" allocations";
    }

    system("cls");
    cout << s_AllocCount << " allocations\n";
    return 0;
}
