#include "head.h"

// g++ -std=c++11 head.h Source.cpp Main.cpp -o m

int main()
{

    Timer timer;
    Map Map;
    //string Map = get_file_content("Map.txt");
    //int map_height = calculate_map_height(Map);
    //int map_width = calculate_map_width(Map);
    int head_position = find_head_position(Map.map);
    int lives = 1;
    int fruit_position = Map.map.find('*');
    int score = 0;
    int difficulty = 80;
    int old_head_position;
    list<int> tail_list;
    bool wall_shock = false;
    char key_pressed = 'W';
    char old_ch;
    float aux = 0;
    int wall_position;
    int time_position = Map.map.find("%");
    system("cls");
    Map.print();
    old_head_position = head_position;
    while (!(GetAsyncKeyState('Q')) && lives > 0)
    {
        timer.start();

        if (_kbhit())
            key_pressed = toupper(getch());

        switch (key_pressed)
        {
        case 'W':
            old_head_position = head_position;
            wall_position = detect_wall(Map.map, head_position, Map.width, key_pressed);
            head_position = draw_up(Map.map, head_position, Map.width, wall_position);
            tie(lives, wall_shock) = detect_shock(Map.map, head_position, old_head_position, lives, Map.width, key_pressed, wall_position);

            if (!wall_shock)
                Tail_movenent(tail_list, old_head_position);

            if (tail_list.size() > 0)
            {
                draw_snake_tail(Map.map, tail_list);
                Map.map.replace(tail_list.back(), 1, " ");
            }

            break;
        case 'A':
            old_head_position = head_position;
            wall_position = detect_wall(Map.map, head_position, Map.width, key_pressed);
            head_position = draw_left(Map.map, head_position, Map.width, wall_position);
            tie(lives, wall_shock) = detect_shock(Map.map, head_position, old_head_position, lives, Map.width, key_pressed, wall_position);

            if (!wall_shock)
                Tail_movenent(tail_list, old_head_position);

            if (tail_list.size() > 0)
            {
                draw_snake_tail(Map.map, tail_list);
                Map.map.replace(tail_list.back(), 1, " ");
            }
            break;
        case 'S':
            old_head_position = head_position;
            wall_position = detect_wall(Map.map, head_position, Map.width, key_pressed);
            head_position = draw_down(Map.map, head_position, Map.width, Map.width, wall_position);
            tie(lives, wall_shock) = detect_shock(Map.map, head_position, old_head_position, lives, Map.width, key_pressed, wall_position);

            if (!wall_shock)
                Tail_movenent(tail_list, old_head_position);

            if (tail_list.size() > 0)
            {
                draw_snake_tail(Map.map, tail_list);
                Map.map.replace(tail_list.back(), 1, " ");
            }
            break;
        case 'D':
            old_head_position = head_position;
            wall_position = detect_wall(Map.map, head_position, Map.width, key_pressed);
            head_position = draw_right(Map.map, head_position, Map.width, wall_position);
            tie(lives, wall_shock) = detect_shock(Map.map, head_position, old_head_position, lives, Map.width, key_pressed, wall_position);

            if (!wall_shock)
                Tail_movenent(tail_list, old_head_position);

            if (tail_list.size() > 0)
            {
                draw_snake_tail(Map.map, tail_list);
                Map.map.replace(tail_list.back(), 1, " ");
            }
            break;

        default:
            break;
        }

        if (head_position == fruit_position)
        {
            tail_increase_size(tail_list, old_head_position);
            fruit_position = draw_fruit_position(Map.map);
            score += 10;
            draw_snake_tail(Map.map, tail_list);
        }

        Map.print();
        Sleep(difficulty);
        timer.stop();
        aux = aux + timer.elapsedMilliseconds();
        cout<<Map.width;
        printf("%0.1f\n", aux / 1000.0);

        //print_score(map_height, score, lives);
    }

    cout << "You are dead!";
    system("cls");

    return 0;
}
