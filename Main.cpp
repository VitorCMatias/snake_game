#include "head.h"

// g++ -std=c++11 head.h Source.cpp Main.cpp -o m

int main()
{

    Timer timer;
    Map Map;
    Head head;
    Tail tail;
    //string Map = get_file_content("Map.txt");
    //int map_height = calculate_map_height(Map);
    //int map_width = calculate_map_width(Map);
    //int head_position = find_head_position(Map.map);
    int lives = 1;
    int fruit_position = Map.map.find('*');
    int score = 0;
    int difficulty = 80;
    //int old_head_position;
    //list<int> tail_list;
    //bool wall_shock = false;
    char key_pressed = 'W';
    char old_ch;
    float aux = 0;
    //int wall_position;
    int time_position = Map.map.find("%");
    system("cls");
    Map.print();
    head.head_last_position = head.head_position;
    //old_head_position = head_position;
    while (!(GetAsyncKeyState('Q')) && lives > 0)
    {
        timer.start();

        if (_kbhit())
            key_pressed = toupper(getch());

        head.head_last_position = head.head_position;

        switch (key_pressed)
        {
        case 'W':
            //head.head_last_position = head.head_position;
            head.wall_position = head.detect_wall(key_pressed);
            head.draw_up(Map.map);
            tie(lives, head.wall_shock) = head.detect_shock(lives, key_pressed);

            /*if (!head.wall_shock)
                tail.Tail_movenent(tail.tail_list, head.head_last_position);

            if (tail.tail_list.size() > 0)
            {
                tail.draw_snake_tail(Map.map, tail.tail_list);
                Map.map.replace(tail.tail_list.back(), 1, " ");
            }*/

            break;
        case 'A':
            //head.head_last_position = head.head_position;
            head.wall_position = head.detect_wall(key_pressed);
            head.draw_left(Map.map);
            tie(lives, head.wall_shock) = head.detect_shock(lives, key_pressed);

            /*if (!head.wall_shock)
                tail.Tail_movenent(tail.tail_list, head.head_last_position);

            if (tail.tail_list.size() > 0)
            {
                tail.draw_snake_tail(Map.map, tail.tail_list);
                Map.map.replace(tail.tail_list.back(), 1, " ");
            }*/
            break;
        case 'S':
            //head.head_last_position = head.head_position;
            head.wall_position = head.detect_wall(key_pressed);
            head.draw_down(Map.map);
            tie(lives, head.wall_shock) = head.detect_shock(lives, key_pressed);

            /*if (!head.wall_shock)
                tail.Tail_movenent(tail.tail_list, head.head_last_position);

            if (tail.tail_list.size() > 0)
            {
                tail.draw_snake_tail(Map.map, tail.tail_list);
                Map.map.replace(tail.tail_list.back(), 1, " ");
            }*/
            break;
        case 'D':
            //head.head_last_position = head.head_position;
            head.wall_position = head.detect_wall(key_pressed);
            head.draw_right(Map.map);
            tie(lives, head.wall_shock) = head.detect_shock(lives, key_pressed);

            /*if (!head.wall_shock)
                tail.Tail_movenent(tail.tail_list, head.head_last_position);

            if (tail.tail_list.size() > 0)
            {
                tail.draw_snake_tail(Map.map, tail.tail_list);
                Map.map.replace(tail.tail_list.back(), 1, " ");
            }*/
            break;

        default:
            break;
        }

        if (!head.wall_shock)
            tail.Tail_movenent(tail.tail_list, head.head_last_position);

        if (tail.tail_list.size() > 0)
        {
            tail.draw_snake_tail(Map.map, tail.tail_list);
            Map.map.replace(tail.tail_list.back(), 1, " ");
        }

        if (head.head_position == fruit_position)
        {
            tail.tail_increase_size(tail.tail_list, head.head_last_position);
            fruit_position = draw_fruit_position(Map.map);
            score += 10;
            tail.draw_snake_tail(Map.map, tail.tail_list);
        }

        Map.print();
        Sleep(difficulty);
        timer.stop();
        aux = aux + timer.elapsedMilliseconds();
        for (int i : tail.tail_list)
            printf("%d\t", i);
        printf("\n");
        printf("hp: %d hlp: %d\n", head.head_position, head.head_last_position);
        printf("Size: %d\n", tail.tail_list.size());
        printf("Score: %d\n", score);
        printf("%0.1f\n", aux / 1000.0);

        //print_score(map_height, score, lives);
    }

    cout << "You are dead!";
    system("cls");

    return 0;
}
