#include "header.h"

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

void Snake::mtr(int v)
{
    Map::canvas.replace(v, 1, "9");
}

bool Head::hit()
{
    return this->wall_shock;
}

int Head::find_position()
{
    return Map::canvas.find('0');
}

int Head::detect_wall(char key_pressed)
{
    int wall_position = 0;
    int head_lock_ahead = calculate_next_position(key_pressed);
    if (Map::canvas.at(head_lock_ahead) == '#')
    {
        wall_position = head_lock_ahead;
    }
    return wall_position;
}

int Head::detect_tail(char key_pressed)
{
    int tail_position = 0;
    int head_lock_ahead = calculate_next_position(key_pressed);
    if (Map::canvas.at(head_lock_ahead) == 'o')
    {
        tail_position = head_lock_ahead;
    }
    return tail_position;
}

bool Head::detect_shock(char key_pressed)
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

void Head::draw_left()
{
    const int width = Map::get_width();
    if (head_position % width > 1 && head_position - 1 != wall_position)
    {
        Map::canvas.replace(head_position - 1, 2, "0 "); //Paramters: Position, Size, Content
        this->head_position--;
    }
}

void Head::draw_right()
{
    const int width = Map::get_width();
    if (head_position % width < width - 3 && head_position + 1 != wall_position) // 3 por causa das duas paredes '#' e do \n
    {
        Map::canvas.replace(head_position, 2, " 0"); //Paramters: Position, Size, Content
        this->head_position++;
    }
}

void Head::draw_up()
{
    const int width = Map::get_width();
    if (head_position / width > 1 && head_position - width != wall_position)
    {
        Map::canvas.replace(head_position, 1, " "); //Paramters: Position, Size, Content
        this->head_position = head_position - width;
        Map::canvas.replace(head_position, 1, "0"); //Paramters: Position, Size, Content
    }
}
void Head::draw_down()
{
    const int height = Map::get_height();
    const int width = Map::get_width();
    if (head_position < (height - 2) * width && head_position + width != wall_position)
    {
        Map::canvas.replace(head_position, 1, " "); //Paramters: Position, Size, Content
        this->head_position = head_position + width;
        Map::canvas.replace(head_position, 1, "0"); //Paramters: Position, Size, Content
    }
}

int Head::inform_position()
{
    return this->head_position;
}

void Head::move_up()
{
    this->wall_position = detect_wall(MOVE_UP);
    this->tail_position = detect_tail(MOVE_UP);
    draw_up();
    this->wall_shock = detect_shock(MOVE_UP);
}

void Head::move_left()
{
    this->wall_position = detect_wall(MOVE_LEFT);
    draw_left();
    this->wall_shock = detect_shock(MOVE_LEFT);
}

void Head::move_right()
{
    this->wall_position = detect_wall(MOVE_RIGHT);
    draw_right();
    this->wall_shock = detect_shock(MOVE_RIGHT);
}

void Head::move_down()
{
    this->wall_position = detect_wall(MOVE_DOWN);
    draw_down();
    this->wall_shock = detect_shock(MOVE_DOWN);
}

void Head::set_last_position()
{
    this->head_last_position = this->head_position;
}

int Head::get_last_position()
{
    return this->head_last_position;
}
int Head::get_position()
{
    return this->head_position;
}

void Tail::Tail_movenent(int head_last_position)
{
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

void Tail::tail_increase_size(int head_last_position)
{
    this->tail_list.push_front(head_last_position);
}

void Tail::draw_snake_tail(string &map)
{
    if (this->tail_list.size() == 1)
        map.replace(this->tail_list.front(), 1, "o");
    else
    {
        for (int node : this->tail_list)
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

Tail::Tail() {}