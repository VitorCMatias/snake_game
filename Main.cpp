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
    Fruit fruit;
    int lives = 1;
    int score = 0;
    int difficulty = 80;
    char key_pressed = MOVE_UP;

    sys.show_consol_cursor(false);
    system("cls");
    Map::print();

    /*char str[11];
    sprintf(str,"MODE %d, %d", Map::get_width(), Map::get_height() + 5);
    system(str);*/

    while (!(GetAsyncKeyState('Q')) && lives > 0)
    {
        timer.start();

        if (_kbhit())
            key_pressed = toupper(_getch());

        switch (key_pressed)
        {
        case MOVE_UP:
            Head::move_up();
            break;
        case MOVE_LEFT:
            Head::move_left();
            break;
        case MOVE_DOWN:
            Head::move_down();
            break;
        case MOVE_RIGHT:
            Head::move_right();
            break;
        default:
            break;
        }

        if (Head::hit())
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
        Map::print();

        timer.update().print();
        printf("Score: %d\n", score);

        //cout<<"\n"<<s_AllocCount<<" allocations";
    }

    system("cls");
    cout << s_AllocCount << " allocations\n";
    return 0;
}
