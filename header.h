#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <random>
#include <chrono>
#include <list>
#include <thread>

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
    static auto move_up() { return get_instance().internal_move_up(); }
    static auto move_left() { return get_instance().internal_move_left(); }
    static auto move_right() { return get_instance().internal_move_right(); }
    static auto move_down() { return get_instance().internal_move_down(); }
    static int get_last_position() { return get_instance().internal_get_last_position(); }
    static int get_position() { return get_instance().internal_get_position(); }
    static bool hit() { return get_instance().internal_hit(); }

private:
    Head();
    void internal_move_up();
    void internal_move_left();
    void internal_move_right();
    void internal_move_down();
    int internal_get_last_position();
    int internal_get_position();
    bool internal_hit();
    int find_position();
    bool detect_shock(char key_pressed);
    int calculate_next_position(char key_pressed);
    int detect_wall(char key_pressed);
    int detect_tail(char key_pressed);
    void draw_left();
    void draw_right();
    void draw_up();
    void draw_down();
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