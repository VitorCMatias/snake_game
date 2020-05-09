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
    float clock = 0;

    sys.show_consol_cursor(false);
    system("cls");
<<<<<<< HEAD
    Map.print();
    head.set_last_position();

    /*HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, FOREGROUND_GREEN);
    printf("Score:");*/

    /*SetConsoleTextAttribute(h, FOREGROUND_RED);
    printf("Score:");*/
    //setfontcolor(RED);

=======
    Map::print();

>>>>>>> Use_static_members
    while (!(GetAsyncKeyState('Q')) && lives > 0)
    {
        timer.start();

        if (_kbhit())
            key_pressed = toupper(_getch());

        switch (key_pressed)
        {
        case MOVE_UP:
<<<<<<< HEAD
            head.move_up(&Map.canvas);
            break;
        case MOVE_LEFT:
            head.move_left(&Map.canvas);
            break;
        case MOVE_DOWN:
            head.move_down(&Map.canvas);
            break;
        case MOVE_RIGHT:
            head.move_right(&Map.canvas);
=======
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
>>>>>>> Use_static_members
            break;
        default:
            break;
        }

<<<<<<< HEAD
        if (head.hit())
            lives--;
        else
            tail.Tail_movenent(head.get_last_position());

        tail.move(Map.canvas);
=======
        if (Head::hit())
            lives--;
        else
        {
            Tail::update_position();
            Tail::move();
        }
>>>>>>> Use_static_members

        if (Head::get_position() == fruit.get_position())
        {
            Tail::increase_size();
            Tail::move();
            fruit.draw(Map::canvas);
            score += 10;
        }
<<<<<<< HEAD
    
        Map.print();
=======

>>>>>>> Use_static_members
        Sleep(difficulty);
        Map::print();

        timer.stop();
        clock = clock + timer.elapsedMilliseconds();
        printf("Score: %d\n", score);
        printf("%0.1f\n", clock / 1000.0);
        //cout<<"\n"<<s_AllocCount<<" allocations";
    }

    system("cls");
    cout<<s_AllocCount<<" allocations";
    return 0;
}
