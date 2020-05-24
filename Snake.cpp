#include "header.h"

Head::Head()
{
    this->head_position = find_position();
    this->wall_shock = false;
    this->head_last_position = this->head_position;
}

int Head::find_position()
{
    return Map::canvas.find(HEAD);
}

int Head::internal_get_last_position()
{
    return head_last_position;
}

int Head::internal_get_position()
{
    return head_position;
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
    bool colision;
    System::gotoxy(x, y);
    if (System::get_cursor_char() == WALL)
        colision = true;
    else
        colision = false;
    return colision;
}

bool Head::detect_tail_colision()
{
    bool colision;
    System::gotoxy(x, y);
    if (System::get_cursor_char() == TAIL_NODE)
        colision = true;
    else
        colision = false;
    return colision;
}

bool Head::internal_get_colision()
{
    return wall_shock || tail_shock;
}

void Head::internal_set_coord()
{
    this->x = System::set_x(head_position);
    this->y = System::set_y(head_position);
}

void Head::internal_print()
{
    System::gotoxy(x, y);

    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 114);
    cout << GREEN_CHAR << HEAD << RESET_COLOR_SCHEME;
    //cout << HEAD;
}

void Head::internal_move(char key_pressed)
{
    this->head_last_position = head_position;
    System::gotoxy(x, y);
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

void Tail::update_position()
{
    int head_last_position = Head::get_last_position();

    if (tail_list.size() == 1)
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

void Tail::internal_draw()
{
    const int map_width = Map::get_width();
    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 114);

    if (this->tail_list.size() == 1)
    {
        System::go_to_console_position(tail_list.front());
        cout << GREEN_CHAR << TAIL_NODE << RESET_COLOR_SCHEME;
        
        //cout << TAIL_NODE;
        System::go_to_console_position(tail_list.back());
        //cout << ' ';
        ///cout << ' ' <<RESET_COLOR_SCHEME;
        cout << ' ';
    }
    else
    {
        for (int node : this->tail_list)
        {
            System::go_to_console_position(node);
            cout << GREEN_CHAR << TAIL_NODE << RESET_COLOR_SCHEME;
        }
        System::go_to_console_position(tail_list.back());
        cout << ' ';
    }
}

void Tail::internal_move()
{
    update_position();
    if (this->tail_list.size() > 0)
    {
        internal_draw();
    }
}

