#include "header.h"

//g++ -O2 -std=c++11 head.h Source.cpp Main.cpp  -o m

int main()
{
    Timer timer;
    System sys;
    Map::canvas = sys.get_file_content("Map.txt");
    Fruit fruit;
    Tail tail;
    int lives = 1;
    int score = 0;
    int difficulty = 80;
    char key_pressed = MOVE_UP;
    float clock = 0;

    sys.show_consol_cursor(false);
    Map::canvas = sys.get_file_content("Map.txt");
    Map::print();
    system("cls");

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
            tail.Tail_movenent(Head::get_last_position());

        tail.move(Map::canvas);

        if (Head::get_position() == fruit.get_position())
        {
            tail.tail_increase_size(Head::get_last_position());
            tail.move(Map::canvas);
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
