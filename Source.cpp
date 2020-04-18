#include "head.h"

void Timer::start()
{
    m_StartTime = std::chrono::system_clock::now();
    m_bRunning = true;
}

void Timer::stop()
{
    m_EndTime = std::chrono::system_clock::now();
    m_bRunning = false;
}

double Timer::elapsedMilliseconds()
{
    std::chrono::time_point<std::chrono::system_clock> endTime;

    if (m_bRunning)
        endTime = std::chrono::system_clock::now();
    else
        endTime = m_EndTime;

    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
}

void gotoxy(short x, short y)
{
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

string get_file_content(const string path)
{
    /*
	    Utiliza um iterator - ponteiros para enderecos de memoria- para construir uma string com os dados da ifstream - input file stream.
		- istreambuf_iterator<char>(file)) = iterator para o inicio do arquivo
		- istreambuf_iterator<char>() = iterator para o final do arquivo
	*/

    ifstream file("Map.txt"); // Ponteiro para o local do arquivo
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    return content;
}

int calculate_map_width(string map)
{
    return (map.find('\n') + 1);
}

int calculate_map_height(string map)
{
    int map_width = calculate_map_width(map);

    return (map.size() / map_width) + 1;
}

int find_head_position(const string map)
{
    return map.find('0');
}

int calculate_head_height(int head_position, int map_width)
{
    return head_position / map_width;
}

int draw_left(string &map, int &head_position, int map_width, int wall_position)
{

    if (head_position % map_width > 1 && head_position - 1 != wall_position)
    {
        map.replace(head_position - 1, 2, "0 "); //Paramters: Position, Size, Content
        head_position--;
    }

    return head_position;
}

int draw_right(string &map, int &head_position, int map_width, int wall_position)
{
    if (head_position % map_width < map_width - 3 && head_position + 1 != wall_position) // 3 por causa das duas paredes '#' e do \n
    {
        map.replace(head_position, 2, " 0"); //Paramters: Position, Size, Content
        head_position++;
    }

    return head_position;
}

int draw_up(string &map, int &head_position, int map_width, int wall_position)
{
    if (head_position / map_width > 1 && head_position - map_width != wall_position)
    {
        map.replace(head_position, 1, " "); //Paramters: Position, Size, Content
        head_position = head_position - map_width;
        map.replace(head_position, 1, "0"); //Paramters: Position, Size, Content
    }
    return head_position;
}
int draw_down(string &map, int &head_position, int map_height, int map_width, int wall_position)
{
    if (head_position < (map_height - 2) * map_width && head_position + map_width != wall_position)
    {
        map.replace(head_position, 1, " "); //Paramters: Position, Size, Content
        head_position = head_position + map_width;
        map.replace(head_position, 1, "0"); //Paramters: Position, Size, Content
    }
    return head_position;
}

int detect_wall(string map, int head_position, int map_width, char key_pressed)
{
    int wall_position = 0;
    int head_lock_ahead = calculate_next_head_position(head_position, map_width, key_pressed);
    if (map.at(head_lock_ahead) == '#')
    {
        wall_position = head_lock_ahead;
    }
    return wall_position;
}

tuple<int, bool> detect_shock(string map, int head_position, int head_last_position, int &lives, int map_width, char key_pressed, int wall_position)
{
    bool head_hit_wall = false;
    int head_lock_ahead = calculate_next_head_position(head_position, map_width, key_pressed);
    if (map.at(head_lock_ahead) == 'o')
    {
        head_hit_wall = false;
        lives--;
    }
    else if (head_position == head_last_position)
    {
        head_hit_wall = true;
        lives--;
    }
    /* else if (map.at(head_lock_ahead) == '#')
    {
        aux = head_lock_ahead;
        //head_hit_wall = true;
        //lives--;
    }*/

    if (head_position == wall_position)
    {
        head_hit_wall = true;
        lives--;
    }

    return make_tuple(lives, head_hit_wall);
}

int calculate_next_head_position(int head_position, int map_width, char key_pressed)
{

    int head_next_position;

    switch (key_pressed)
    {
    case 'W':
        head_next_position = head_position - map_width;
        break;
    case 'A':
        head_next_position = head_position - 1;
        break;
    case 'S':
        head_next_position = head_position + map_width;
        break;
    case 'D':
        head_next_position = head_position + 1;
        break;

    default:
        break;
    }

    return head_next_position;
}

int draw_fruit_position(string &map)
{
    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937 mt_rand(seed);
    int fruit_position = mt_rand() % map.length();

    while (map.at(fruit_position) != ' ')
        fruit_position = mt_rand() % map.length();

    map.replace(fruit_position, 1, "*"); //Paramters: Position, Size, Content

    return fruit_position;
}

void Tail_movenent(list<int> &tail_list, int head_position)
{
    if (tail_list.size() == 1)
    {
        tail_list.push_front(head_position);
    }
    else
    {
        tail_list.push_front(head_position);
        tail_list.pop_back();
    }
}

void tail_increase_size(list<int> &tail_list, int head_position)
{
    tail_list.push_front(head_position);
}

void draw_snake_tail(string &map, list<int> tail)
{
    if (tail.size() == 1)
        map.replace(tail.front(), 1, "o");
    else
    {
        for (int node : tail)
        {
            map.replace(node, 1, "o"); //Paramters: Position, Size, Content
        }
        map.replace(tail.back(), 1, " ");
    }
}

void display_list(list<int> l)
{
    for (int x : l)
        cout << x << " ";
    cout << endl;
}

void print(string txt)
{
    gotoxy(0, 0);
    cout << txt << endl;
}

void print_score(int map_height, int score, int lives)
{
    gotoxy(1, map_height + 2);
    cout << "Score: " << score << endl;
    gotoxy(1, map_height + 3);
    cout << "Lives: " << lives << endl;
}
