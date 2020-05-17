#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <random>
#include <chrono>
#include <tuple>
#include <list>
#include <thread>
#include <stdlib.h>

#define HEAD '0'
#define TAIL_NODE 'o'
#define FRUIT '*'
#define WALL '#'
#define MOVE_UP 'W'
#define MOVE_LEFT 'A'
#define MOVE_RIGHT 'D'
#define MOVE_DOWN 'S'

#define HEIGHT
#define WIDTH

using namespace std;

struct System
{
    System(/* args */);
    int generate_ramdom_number();
    string get_file_content(const string path);
    void show_consol_cursor(bool showFlag);
    ~System();
};

class Timer
{
private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool m_bRunning = false;
    double clock;

private:
    void stop();
    double elapsedMilliseconds();

public:
    void start();
    Timer update();
    Timer print();
    Timer();
};

/*
///Singleton
class Ramdom
{
public:
    Ramdom(const Ramdom &) = delete;
    static Ramdom &get_instance()
    {
        static Ramdom instance;
        return instance;
    }

    static float Float() { return get_instance().IFloat(); }

private:
    Ramdom() {}
    float IFloat() { return m_q; }
    float m_q = 2.0;
};
*/

class Map
{
public:
    static string canvas;

private:
    const int width;
    const int height;

public:
    Map(const Map &) = delete;
    static Map &get_instance()
    {
        static Map s_instance;
        return s_instance;
    }

    static int get_width() { return get_instance().internal_get_width(); }
    static int get_height() { return get_instance().internal_get_height(); }
    static auto print() { return get_instance().internal_print(); }

private:
    Map();
    int internal_get_width();
    int internal_get_height();
    int calculate_width();
    int calculate_height();
    void internal_print();
};

class Snake
{
public:
};

class Head
{
private:
    static int x;
    static int y;
    int head_position;
    int head_last_position;
    bool wall_shock;
    bool tail_shock;

public:
    Head(const Head &) = delete;
    static Head &get_instance()
    {
        static Head instance;
        return instance;
    }

    static int get_last_position() { return get_instance().internal_get_last_position(); }
    static int get_position() { return get_instance().internal_get_position(); }
    static bool get_colision() { return get_instance().internal_get_colision(); }
    static auto print() { return get_instance().internal_print(); }
    static auto move(char key_pressed) { return get_instance().internal_move(key_pressed); }
    static auto set_coord() { return get_instance().internal_set_coord(); }
    static auto get_coord() { return get_instance().internal_get_coord(); }

    /*
    static auto print_coord() { return get_instance().internal_print_coord(); }
    static int get_x() { return get_instance().internal_get_x(); }
    static int get_y() { return get_instance().internal_get_y(); }
    */

private:
    Head();
    void internal_print();
    void internal_move(char key_pressed);
    void internal_set_coord();
    int internal_get_last_position();
    int internal_get_position();
    bool internal_get_colision();
    tuple<int, int> internal_get_coord();

    void calculate_next_coord(char key_pressed);
    int convert_coord_to_one_dimendion();
    int find_position();
    bool detect_wall_colision();
    bool detect_tail_colision();

    /*
    int internal_get_x() { return x; }
    int internal_get_y() { return y; }
    void internal_print_coord() { cout << "H_x:" << x << "H_y: " << y << '\n'; }
    */
};

class Tail
{
private:
    list<int> tail_list;

public:
    Tail(const Tail &) = delete;
    static Tail &get_instance()
    {
        static Tail instance;
        return instance;
    }
    static auto increase_size() { return get_instance().internal_increase_size(); }
    static auto draw() { return get_instance().internal_draw(); }
    static auto move() { return get_instance().internal_move(); }

private:
    Tail() {}
    void update_position();
    void internal_increase_size();
    void internal_draw();
    void internal_move();
};

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
    tuple<int, int> get_coord();
    void draw();
    //void print_coord() { cout << "F_x:" << x << "f_y: " << y << '\n' << "f_p: " << fruit_position << '\n'; }

private:
    int set_y();
    int set_x();
    void generate_position();
};

void print_score(int map_height, int score, int lives);
void gotoxy(short x, short y);
void go_to_console_position(int one_dimension_position);
COORD getxy(CONSOLE_SCREEN_BUFFER_INFO *csbi);
char get_cursor_char();
int set_y();
int set_x();