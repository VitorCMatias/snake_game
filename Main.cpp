#include "head.h"

// g++ -std=c++11 head.h Source.cpp Main.cpp -o m

int main()
{

    string Map = get_file_content("Map.txt");
    int head_position = find_head_position(Map);
    int map_height = calculate_map_height(Map);
    int map_width = calculate_map_width(Map);
    int lives = 1;
    int fruit_position = Map.find('*');
    int score = 0;
    int difficulty = 80;
    int old_head_position;
    list<int> tail_list;
    bool wall_shock = false;
    char key_pressed = 'W';
    char old_ch;
    system("cls");
    print(Map);
    old_head_position = head_position;
    while (!(GetAsyncKeyState('Q')) && lives > 0)
    {

        if (_kbhit())
            key_pressed = toupper(getch());

        switch (key_pressed)
        {
        case 'W':
            old_head_position = head_position;
            head_position = draw_up(Map, head_position, map_width);
            tie(lives, wall_shock) = detect_shock(Map, head_position, old_head_position, lives, map_width, key_pressed);

            if (!wall_shock)
                Tail_movenent(tail_list, old_head_position);
        
            if (tail_list.size() > 0)
            {
                draw_snake_tail(Map, tail_list);
                Map.replace(tail_list.back(), 1, " ");
            }
            break;
        case 'A':
            old_head_position = head_position;
            head_position = draw_left(Map, head_position, map_width);
            tie(lives, wall_shock) = detect_shock(Map, head_position, old_head_position, lives, map_width, key_pressed);

            if (!wall_shock)
                Tail_movenent(tail_list, old_head_position);
            
            if (tail_list.size() > 0)
            {
                draw_snake_tail(Map, tail_list);
                Map.replace(tail_list.back(), 1, " ");
            }
            break;
        case 'S':
            old_head_position = head_position;
            head_position = draw_down(Map, head_position, map_height, map_width);
            tie(lives, wall_shock) = detect_shock(Map, head_position, old_head_position, lives, map_width, key_pressed);

            if (!wall_shock)
                Tail_movenent(tail_list, old_head_position);

            if (tail_list.size() > 0)
            {
                draw_snake_tail(Map, tail_list);
                Map.replace(tail_list.back(), 1, " ");
            }
            break;
        case 'D':
            old_head_position = head_position;
            head_position = draw_right(Map, head_position, map_width);
            tie(lives, wall_shock) = detect_shock(Map, head_position, old_head_position, lives, map_width, key_pressed);

            if (!wall_shock)
                Tail_movenent(tail_list, old_head_position);

            if (tail_list.size() > 0)
            {
                draw_snake_tail(Map, tail_list);
                Map.replace(tail_list.back(), 1, " ");
            }
            break;

        default:
            break;
        }

        if (head_position == fruit_position)
        {
            tail_increase_size(tail_list, old_head_position);
            fruit_position = draw_fruit_position(Map);
            score += 10;
            draw_snake_tail(Map, tail_list);
        }

        print(Map);
        Sleep(difficulty);

        print_score(map_height, score, lives);
    }

    cout << "You are dead!";
    system("cls");
    return 0;
}
