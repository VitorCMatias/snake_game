
#include "Header.hpp"
//#include "Fruit.hpp"

Fruit::Fruit()
{
    this->fruit_position = find_position();
    this->x = System::set_x(fruit_position);
    this->y = System::set_y(fruit_position);
}

int Fruit::find_position()
{
    int fruit_position = Map::canvas.find(FRUIT);
    Map::canvas.replace(fruit_position, 1, " ");

    return fruit_position;
}

int Fruit::get_position()
{
    return fruit_position;
}

void Fruit::generate_position()
{
    int new_fruit_position;
    int fruit_x_position;
    int fruit_y_position;

    do
    {
        new_fruit_position = System::generate_ramdom_number() % Map::canvas.length();
    } while (Map::canvas.at(new_fruit_position) != ' ');

    this->x = new_fruit_position % Map::get_width();
    this->y = new_fruit_position / Map::get_width();
    this->fruit_position = new_fruit_position;
}

void Fruit::draw()
{
    System::gotoxy(x, y);
    cout << YELLOW_CHAR << FRUIT << RESET_COLOR_SCHEME;
}

std::tuple<int, int> Fruit::get_coord()
{
    return tie(x, y);
}

void Fruit::generate()
{
    generate_position();
    draw();
}
