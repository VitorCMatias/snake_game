#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <random>
#include <chrono>
#include <list>
#include <thread>
#include <stdlib.h>

#define HEAD '0'
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
    int wall_position;
    int tail_position;
    bool wall_shock;

public:
    Head(const Head &) = delete;
    static Head &get_instance()
    {
        static Head instance;
        return instance;
    }

    static int get_last_position() { return get_instance().internal_get_last_position(); }
    static int get_position() { return get_instance().internal_get_position(); }
    static bool hit() { return get_instance().internal_hit(); }
    static bool get_colision() { return get_instance().internal_get_colision(); }
    static auto print() { return get_instance().internal_print(); }
    static auto move(char key_pressed) { return get_instance().internal_move(key_pressed); }
    static auto set_coord(){ return get_instance().internal_set_coord(); }

private:
    Head();
    int internal_get_last_position();
    int internal_get_position();
    bool internal_hit();
    int find_position();
    bool detect_shock(char key_pressed);
    int calculate_next_position(char key_pressed);
    int detect_wall(char key_pressed);
    int detect_tail(char key_pressed);
    void calculate_next_coord(char key_pressed);
    void detect_colision();
    bool internal_get_colision();
    void internal_print();
    void internal_move(char key_pressed);
    void internal_set_coord();
};

class Tail
{
public:
    list<int> tail_list;

public:
    Tail(const Tail &) = delete;
    static Tail &get_instance()
    {
        static Tail instance;
        return instance;
    }

    static auto update_position() { return get_instance().internal_update_position(); }
    static auto increase_size() { return get_instance().internal_increase_size(); }
    static auto draw() { return get_instance().internal_draw(); };
    static auto move() { return get_instance().internal_move(); };

private:
    Tail() {}
    void internal_update_position();
    void internal_increase_size();
    void internal_draw();
    void internal_move();
};

class Fruit
{
private:
    int fruit_position;
    int find_position();

public:
    Fruit();
    int get_position();
    void draw(string &map);
};

void print_score(int map_height, int score, int lives);
void gotoxy(short x, short y);
COORD getxy(CONSOLE_SCREEN_BUFFER_INFO *csbi);
char get_cursor_char();
int set_y();
int set_x();
