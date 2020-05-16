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

void Head::internal_move_up()
{
    this->head_last_position = head_position;
    this->wall_position = detect_wall(MOVE_UP);
    this->tail_position = detect_tail(MOVE_UP);
    draw_up();
    this->wall_shock = detect_shock(MOVE_UP);
}

void Head::internal_move_left()
{
    this->head_last_position = head_position;
    this->wall_position = detect_wall(MOVE_LEFT);
    draw_left();
    this->wall_shock = detect_shock(MOVE_LEFT);
}

void Head::internal_move_right()
{
    this->head_last_position = head_position;
    this->wall_position = detect_wall(MOVE_RIGHT);
    draw_right();
    this->wall_shock = detect_shock(MOVE_RIGHT);
}

void Head::internal_move_down()
{
    this->head_last_position = head_position;
    this->wall_position = detect_wall(MOVE_DOWN);
    draw_down();
    this->wall_shock = detect_shock(MOVE_DOWN);
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

void Tail::internal_move()
{
    if (this->tail_list.size() > 0)
    {
        internal_draw();
        Map::canvas.replace(tail_list.back(), 1, " ");
    }
}

int set_y()
{
    //2 = upper and lower wall
    return Head::get_position() % Map::get_height() + 2;
}
int set_x()
{
    return Head::get_position() % Map::get_width();
}
