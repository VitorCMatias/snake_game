#include <iostream>
#include <fstream>
//#include <algorithm>
#include <Windows.h>
#include <conio.h>
#include<random>
#include<chrono>
#include <time.h>
#include <list>
#include <tuple>


#define FRUIT '*'
#define WALL '#'



using namespace std;



void print(string txt);
string get_file_content(const string path);
int calculate_map_width(string map);
int calculate_map_height(string map);
int find_head_position(const string map);
int draw_left(string &map, int &head_position, int map_width, int wall_position);
int draw_right(string &map, int &head_position, int map_width, int wall_position);
int draw_up(string &map, int &head_position, int map_width, int wall_position);
int draw_down(string &map, int &head_position, int map_height, int map_width, int wall_position);

tuple<int,bool> detect_shock(string map, int head_position, int head_last_position, int &lives, int map_width, char key_pressed, int wall_position);
int calculate_next_head_position(int head_position, int map_width, char key_pressed);

int draw_fruit_position(string &map);

void Tail_movenent(list<int> &tail_list, int head_position);
void tail_increase_size(list<int> &tail_list, int head_position);
void draw_snake_tail(string &map, list<int> tail);

void display_list(list<int> l);
void print_score(int map_height, int score, int lives);
int detect_wall(string map, int head_position, int map_width, char key_pressed);