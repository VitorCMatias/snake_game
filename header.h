#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <random>
#include <chrono>
#include <time.h>
#include <list>
#include <thread>
//#include <graphics.h>

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
public:
    void start();
    void stop();
    double elapsedMilliseconds();

private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool m_bRunning = false;
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

/*class Map
{

public:
    static string canvas;

protected:
    const int width;
    const int height;

    //private:
public:
    int get_width();
    int get_height();
    int calculate_width();
    int calculate_height();
    //string get_file_content(const string path);

public:
    void print();
    Map();

    //private:
};
*/
class Snake
{
public:
    void mtr(int v);
    /*Head head;
    Tail tail;*/
};

class Head
{
private:
    int head_position;
    int head_last_position;
    int wall_position;
    int tail_position;

private:
    int find_position();
    bool detect_shock(char key_pressed);
    int calculate_next_position(char key_pressed);
    int detect_wall(char key_pressed);
    int detect_tail(char key_pressed);
    void draw_left();
    void draw_right();
    void draw_up();
    void draw_down();

public:
    bool wall_shock;
    Head();
    void set_last_position();
    int inform_position();
    void move_up();
    void move_left();
    void move_right();
    void move_down();
    int get_last_position();
    int get_position();
    bool hit();
};

class Tail /*: public Head*/
{
public:
    list<int> tail_list;
    Tail();
    void Tail_movenent(int head_last_position);
    void tail_increase_size(int head_position);
    void draw_snake_tail(string &map);
    void move(string &map);
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