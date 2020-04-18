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

private:

};

int find_head_position(const string map); //head

int draw_left(string &map, int &head_position, int map_width, int wall_position);                 //move
int draw_right(string &map, int &head_position, int map_width, int wall_position);                //move
int draw_up(string &map, int &head_position, int map_width, int wall_position);                   //move
int draw_down(string &map, int &head_position, int map_height, int map_width, int wall_position); //move

tuple<int, bool> detect_shock(string map, int head_position, int head_last_position, int &lives, int map_width, char key_pressed, int wall_position);
int calculate_next_head_position(int head_position, int map_width, char key_pressed); //head

int draw_fruit_position(string &map); //fruit

void Tail_movenent(list<int> &tail_list, int head_position);      //tail
void tail_increase_size(list<int> &tail_list, int head_position); //tail
void draw_snake_tail(string &map, list<int> tail);                //tail

int detect_wall(string map, int head_position, int map_width, char key_pressed); //head

void display_list(list<int> l);
void print_score(int map_height, int score, int lives);
