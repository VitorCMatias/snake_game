#include <iostream>
#include <fstream>
//#include <algorithm>
#include <Windows.h>
#include <conio.h>
#include <random>
#include <chrono>
#include <time.h>
#include <list>
// #include <tuple>
#include <thread>

#define FRUIT '*'
#define WALL '#'
#define MOVE_UP 'W'
#define MOVE_LEFT 'A'
#define MOVE_RIGHT 'D'
#define MOVE_DOWN 'S'

using namespace std;

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

class Map
{
    //protected:
public:
    string map;
    int width;
    int height;

private:
    int calculate_width();
    int calculate_height();
    string get_file_content(const string path);

public:
    void print();
    Map();

    //private:
};

class Head : public Map
{
public:
    int head_position;
    int head_last_position;

private:
    int wall_position;

private:
    int find_position();                           //priv
    bool detect_shock(char key_pressed);           //priv
    int calculate_next_position(char key_pressed); //priv
    int detect_wall(char key_pressed);             //priv
    void draw_left(string &map);                   //priv
    void draw_right(string &map);                  //priv
    void draw_up(string &map);                     //priv
    void draw_down(string &map);                   //priv
public:
    bool wall_shock;

public:
    Head();
    int inform_position();
    void move_up(string &map);
    void move_left(string &map);
    void move_right(string &map);
    void move_down(string &map);
};

class Tail : public Head
{
public:
    list<int> tail_list;

    void Tail_movenent(list<int> &tail_list, int head_position);      //tail
    void tail_increase_size(list<int> &tail_list, int head_position); //tail
    void draw_snake_tail(string &map, list<int> tail_list);           //tail
    void move(string &map);
};

int draw_fruit_position(string &map); //fruit

void display_list(list<int> l);
void print_score(int map_height, int score, int lives);