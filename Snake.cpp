#include "header.h"

Head::Head()
{
    this->head_position = find_position();
    this->wall_shock = false;
    this->head_last_position = this->head_position;
}


int Head::calculate_next_position(char key_pressed)
{

    int head_next_position;

    switch (key_pressed)
    {
    case 'W':
        head_next_position = head_position - width;
        break;
    case 'A':
        head_next_position = head_position - 1;
        break;
    case 'S':
        head_next_position = head_position + width;
        break;
    case 'D':
        head_next_position = head_position + 1;
        break;

    default:
        break;
    }

    return head_next_position;
}



void Head::draw_left(string* map)
{
    if (head_position % width > 1 && head_position - 1 != wall_position)
    {
        map->replace(head_position - 1, 2, "0 "); //Paramters: Position, Size, Content
        this->head_position--;
    }
}

void Head::draw_right(string* map)
{
    if (head_position % width < width - 3 && head_position + 1 != wall_position) // 3 por causa das duas paredes '#' e do \n
    {
        map->replace(head_position, 2, " 0"); //Paramters: Position, Size, Content
        this->head_position++;
    }
}

void Head::draw_up(string* map)
{
    if (head_position / width > 1 && head_position - width != wall_position)
    {
        map->replace(this->head_position, 1, " "); //Paramters: Position, Size, Content
        this->head_position = head_position - this->width;
        map->replace(this->head_position, 1, "0"); //Paramters: Position, Size, Content
    }
}
void Head::draw_down(string* map)
{
    if (head_position < (height - 2) * width && head_position + width != wall_position)
    {
        map->replace(head_position, 1, " "); //Paramters: Position, Size, Content
        this->head_position = head_position + width;
        map->replace(head_position, 1, "0"); //Paramters: Position, Size, Content
    }
}

int Head::inform_position()
{
    return head_position;
}

void Head::move_up(string* map)
{
    this->wall_position = detect_wall(MOVE_UP);
    this->tail_position = detect_tail(MOVE_UP);
    draw_up(map);
    this->wall_shock = detect_shock(MOVE_UP);
}

void Head::move_left(string* map)
{
    this->wall_position = detect_wall(MOVE_LEFT);
    draw_left(map);
    this->wall_shock = detect_shock(MOVE_LEFT);
}

void Head::move_right(string* map)
{
    this->wall_position = detect_wall(MOVE_RIGHT);
    draw_right(map);
    this->wall_shock = detect_shock(MOVE_RIGHT);
}

void Head::move_down(string* map)
{
    this->wall_position = detect_wall(MOVE_DOWN);
    draw_down(map);
    this->wall_shock = detect_shock(MOVE_DOWN);
}

void Head::set_last_position()
{
    this->head_last_position = head_position;
}

int Head::get_last_position()
{
    return head_last_position;
}
int Head::get_position()
{
    return head_position;
}

void Tail::Tail_movenent(int head_last_position)
{
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

void Tail::tail_increase_size(int head_last_position)
{
    this->tail_list.push_front(head_last_position);
}

void Tail::draw_snake_tail(string &map)
{
    if (tail_list.size() == 1)
        map.replace(this->tail_list.front(), 1, "o");
    else
    {
        for (int node : tail_list)
        {
            map.replace(node, 1, "o"); //Paramters: Position, Size, Content
        }
        map.replace(this->tail_list.back(), 1, " ");
    }
}

void Tail::move(string &map)
{
    if (this->tail_list.size() > 0)
    {
        draw_snake_tail(map);
        map.replace(this->tail_list.back(), 1, " ");
    }
}