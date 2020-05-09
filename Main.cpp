#include "header.h"

//g++ -O2 -std=c++11 head.h Source.cpp Main.cpp  -o m

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
    float clock = 0;

    sys.show_consol_cursor(false);
    system("cls");
    Map::print();
    

    while (!(GetAsyncKeyState('Q')) && lives > 0)
    {
        timer.start();

        if (_kbhit())
            key_pressed = toupper(getch());

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
            Tail::Tail_movenent();

        Tail::move();

        if (Head::get_position() == fruit.get_position())
        {
            Tail::tail_increase_size();
            Tail::move();
            fruit.draw(Map::canvas);
            score += 10;
        }

        Sleep(difficulty);
        Map::print();

        timer.stop();
        clock = clock + timer.elapsedMilliseconds();
        printf("Score: %d\n", score);
        printf("%0.1f\n", clock / 1000.0);
    }

    system("cls");

    return 0;
}
