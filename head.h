#include <iostream>
#include <fstream>
//#include <algorithm>
#include <Windows.h>
#include <conio.h>
#include <random>
#include <chrono>
#include <time.h>
#include <list>
#include <tuple>
#include <thread>

#define FRUIT '*'
#define WALL '#'

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
    bool wall_shock;
    int wall_position;

public:
    int find_position();
    tuple<int, bool> detect_shock(int &lives, char key_pressed);
    int calculate_next_position(char key_pressed);
    int detect_wall(char key_pressed);
    void draw_left(string &map);                 
    void draw_right(string &map);                //move
    void draw_up(string &map);                   //move
    void draw_down(string &map); //move

public:
    Head();
};

class Move : public Head
{
};

int draw_fruit_position(string &map); //fruit

void Tail_movenent(list<int> &tail_list, int head_position);      //tail
void tail_increase_size(list<int> &tail_list, int head_position); //tail
void draw_snake_tail(string &map, list<int> tail);                //tail

void display_list(list<int> l);
void print_score(int map_height, int score, int lives);
