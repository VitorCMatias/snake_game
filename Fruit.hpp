#include <tuple>



class Fruit
{
private:
    int fruit_position;
    int x;
    int y;

private:
    int find_position();

public:
    Fruit();
    void generate();
    int get_position();
    std::tuple<int, int> get_coord();
    void draw();
    int get_fruit_position() { return fruit_position; }

private:
    void generate_position();
};