#include "head.h"

//g++ -O2 -std=c++11 head.h Source.cpp Main.cpp  -o m

int main()
{

    Timer timer;
    Map Map;
    Head head;
    Tail tail;
    Fruit fruit;
    System sys;

    int lives = 1;
    int score = 0;
    int difficulty = 80;
    char key_pressed = 'W';
    float clock = 0;
    sys.show_consol_cursor(false);
    system("cls");
    //Map.print();
    head.set_last_position();

    /*HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, FOREGROUND_GREEN);
    printf("Score:");*/

    /*SetConsoleTextAttribute(h, FOREGROUND_RED);
    printf("Score:");*/
    
    
    while (!(GetAsyncKeyState('Q')) && lives > 0)
    {
        timer.start();

        if (_kbhit())
            key_pressed = toupper(getch());

        head.set_last_position();

        switch (key_pressed)
        {
        case MOVE_UP:
            head.move_up(Map.canvas);
            break;
        case MOVE_LEFT:
            head.move_left(Map.canvas);
            break;
        case MOVE_DOWN:
            head.move_down(Map.canvas);
            break;
        case MOVE_RIGHT:
            head.move_right(Map.canvas);
            break;
        default:
            break;
        }

        if (head.wall_shock)
            lives--;
        else
            tail.Tail_movenent( head.get_last_position());

        tail.move(Map.canvas);

        if (head.get_position() == fruit.get_position())
        {
            tail.tail_increase_size(head.get_last_position());
            tail.move(Map.canvas);
            fruit.draw(Map.canvas);
            score += 10;
        }


        Map.print();
        Sleep(difficulty);
        timer.stop();
        clock = clock + timer.elapsedMilliseconds();
        printf("Score: %d\n", score);
        printf("%0.1f\n", clock / 1000.0);
    }

    system("cls");

    return 0;
}
