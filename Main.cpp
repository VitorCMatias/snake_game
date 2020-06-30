#include "Header.hpp"

//g++ -O2 -std=c++17 header.h Source.cpp Main.cpp  -o m
//g++ -std=c++17 header.h Snake.cpp Source.cpp Main.cpp -o m

int main()
{
    //System::welcome_screen();
    
    
    Timer timer;

    Map::canvas = System::get_file_content("Map.txt");
    Head::set_coord();

    Fruit fruit;
    int lives = 1;
    int score = 0;
    int difficulty = 0;
    char key_pressed = MOVE_UP;
    bool quit_game = false;

    



    System::show_consol_cursor();
    system("cls");
    Map::print();
    fruit.draw();

    //set_console_size();

    while (!(GetAsyncKeyState('Q')) && lives > 0)
    {
        timer.start();
        Sleep(difficulty);

        if (_kbhit())
            key_pressed = toupper(_getch());
        Head::move(key_pressed);

        if (Head::get_colision())
        {
            lives--;
        }
        else
        {
            Head::print();
            Tail::move();
        }

        if (Head::get_coord() == fruit.get_coord())
        {
            Tail::increase_size();
            Tail::move();
            score += 10;
            fruit.generate();
        }

        print_information(lives, score, timer);
    }
    System::update_map_to_print(fruit.get_position());
    System::write_file();
    System::gotoxy(0, Map::get_height() + 10);
    system("cls");
    return 0;
}
