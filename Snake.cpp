#include "header.h"
int Head::x;
int Head::y;
Head::Head()
{
    this->head_position = find_position();
    this->wall_shock = false;
    this->head_last_position = this->head_position;
}

int Head::calculate_next_position(char key_pressed)
{
    const int width = Map::get_width();

    int head_next_position;

    switch (key_pressed)
    {
    case 'W':
        head_next_position = this->head_position - width;
        break;
    case 'A':
        head_next_position = this->head_position - 1;
        break;
    case 'S':
        head_next_position = this->head_position + width;
        break;
    case 'D':
        head_next_position = this->head_position + 1;
        break;

    default:
        break;
    }

    return head_next_position;
    
}

int Head::find_position()
{
    return Map::canvas.find('0');
}

int Head::detect_wall(const char key_pressed)
{
    int wall_position = 0;
    int head_lock_ahead = calculate_next_position(key_pressed);
    if (Map::canvas.at(head_lock_ahead) == '#')
    {
        wall_position = head_lock_ahead;
    }
    return wall_position;
}

int Head::detect_tail(const char key_pressed)
{
    int tail_position = 0;
    int head_lock_ahead = calculate_next_position(key_pressed);
    if (Map::canvas.at(head_lock_ahead) == 'o')
    {
        tail_position = head_lock_ahead;
    }
    return tail_position;
}

bool Head::detect_shock(const char key_pressed)
{
    bool head_hit_tail = false;
    bool head_hit_wall = false;
    int head_lock_ahead = calculate_next_position(key_pressed);

    /*for(int tail_node : this->tail_list){
        if(tail_node == this->head_position)
        {
            head_hit_tail = true;
        }
    }*/

    if (this->head_position == this->tail_position)
    {
        head_hit_tail = true;
    }

    else if (this->head_position == this->head_last_position)
        head_hit_wall = true;
    if (this->head_position == this->wall_position)
        head_hit_wall = true;

    return head_hit_wall || head_hit_tail;
}

int Head::internal_get_last_position()
{
    return head_last_position;
}

int Head::internal_get_position()
{
    return head_position;
}

bool Head::internal_hit()
{
    return wall_shock;
}

void Head::calculate_next_coord(char key_pressed)
{
    switch (key_pressed)
    {
    case MOVE_UP:
        Head::y -= 1;
        break;
    case MOVE_LEFT:
        Head::x -= 1;
        break;
    case MOVE_DOWN:
        Head::y += 1;
        break;
    case MOVE_RIGHT:
        Head::x += 1;
        break;
    default:
        break;
    }
}

bool Head::detect_wall_colision()
{
    bool colision; // = false;
    gotoxy(Head::x, Head::y);
    if (get_cursor_char() == WALL)
        colision = true;
    else
    {
        colision = false;
    }
    return colision;
}

bool Head::detect_tail_colision()
{
    bool colision; // = false;
    gotoxy(Head::x, Head::y);
    if (get_cursor_char() == TAIL_NODE)
        colision = true;
    else
    {
        colision = false;
    }
    return colision;
}


bool Head::internal_get_colision()
{
    return wall_shock||tail_shock;
}

void Head::internal_set_coord()
{
    Head::x = set_x();
    Head::y = set_y();
}

void Head::internal_print()
{
    gotoxy(Head::x, Head::y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 114);
    cout << HEAD;
}

void Head::internal_move(char key_pressed)
{
    this->head_last_position = head_position;
    gotoxy(Head::x, Head::y);
    cout << ' ';
    calculate_next_coord(key_pressed);
    this->wall_shock = detect_wall_colision();
    this->tail_shock = detect_tail_colision();
    if (!wall_shock)
        this->head_position = convert_coord_to_one_dimendion();
}

int Head::convert_coord_to_one_dimendion()
{
    return y * Map::get_width() + x;
}

tuple<int, int> Head::internal_get_coord()
{
    return tie(x, y);
}

void Tail::internal_update_position()
{
    int head_last_position = Head::get_last_position();

    if (this->tail_list.size() == 1)
    {
        this->tail_list.push_front(head_last_position);
    }
    else
    {
        this->tail_list.push_front(head_last_position);
        this->tail_list.pop_back();
    }
}

void Tail::internal_increase_size()
{
    int head_last_position = Head::get_last_position();
    this->tail_list.push_front(head_last_position);
}

/*
void Tail::internal_draw()
{
    if (this->tail_list.size() == 1)
        Map::canvas.replace(tail_list.front(), 1, "o");
    else
    {
        for (int node : this->tail_list)
        {
            Map::canvas.replace(node, 1, "o"); //Paramters: Position, Size, Content
        }
        Map::canvas.replace(tail_list.back(), 1, " ");
    }
}
*/
void Tail::internal_draw()
{
    const int map_width = Map::get_width();

    if (this->tail_list.size() == 1)
    {
        gotoxy(tail_list.front() % map_width, tail_list.front() / map_width);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 114);
        cout << TAIL_NODE;
    }
    else
    {
        for (int node : this->tail_list)
        {
            gotoxy(node % map_width, node / map_width);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 114);
            cout << TAIL_NODE;
        }
        gotoxy(tail_list.back() % map_width, tail_list.back() / map_width);
        cout << ' ';
    }
}

void Tail::internal_move()
{

    const int map_width = Map::get_width();
    internal_update_position();

    if (this->tail_list.size() > 0)
    {
        internal_draw();
        gotoxy(tail_list.back() % map_width, tail_list.back() / map_width);
        cout << ' ';
    }
}

int set_y()
{
    //2 = upper and lower wall
    return Head::get_position() / Map::get_width();
}
int set_x()
{
    return Head::get_position() % Map::get_width();
}
