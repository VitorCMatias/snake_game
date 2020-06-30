#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <random>
#include <chrono>
#include <tuple>
#include <list>
#include <stdlib.h>

#define HEAD '0'
#define TAIL_NODE 'o'
#define FRUIT '*'
#define APPLE '@'
#define WALL '#'
#define MOVE_UP 'W'
#define MOVE_LEFT 'A'
#define MOVE_RIGHT 'D'
#define MOVE_DOWN 'S'

#define GREEN_CHAR "\033[92m"
#define YELLOW_CHAR "\033[33m"
#define GRAY_CHAR "\033[90m"
#define RED_CHAR "\033[31m"
#define MENU_SELECTOR "\033[100m"
#define RESET_COLOR_SCHEME "\033[m"

using namespace std;

class System
{
public:
    System(const System &) = delete;
    static System &get_instance()
    {
        static System instance;
        return instance;
    }

    static int generate_ramdom_number() { return get_instance().internal_generate_ramdom_number(); }
    static auto show_consol_cursor() { return get_instance().internal_hide_consol_cursor(); }
    static string get_file_content(const string path) { return get_instance().internal_get_file_content(path); }
    static int set_x(int one_dimension_position) { return get_instance().internal_set_x(one_dimension_position); }
    static int set_y(int one_dimension_position) { return get_instance().internal_set_y(one_dimension_position); }
    static void gotoxy(short x, short y) { return get_instance().internal_gotoxy(x, y); }
    static void go_to_console_position(int one_dimension_position) { return get_instance().internal_go_to_console_position(one_dimension_position); }
    static COORD getxy(CONSOLE_SCREEN_BUFFER_INFO *csbi) { return get_instance().internal_getxy(csbi); }
    static char get_cursor_char() { return get_instance().internal_get_cursor_char(); }
    static auto welcome_screen() { return get_instance().internal_welcome_screen(); }
    static auto write_file() { return get_instance().internal_write_file(); }
    static int convert_coord_to_one_dimendion(const int x, const int y) { return get_instance().internal_convert_coord_to_one_dimendion(x, y); }
    static auto update_map_to_print(int fruit_position) { return get_instance().internal_update_map_to_print(fruit_position); }

private:
    System() {}
    int internal_generate_ramdom_number();
    void internal_hide_consol_cursor();
    string internal_get_file_content(const string path);
    int internal_set_y(int one_dimension_position);
    int internal_set_x(int one_dimension_position);

    void internal_gotoxy(short x, short y);
    void internal_go_to_console_position(int one_dimension_position);
    COORD internal_getxy(CONSOLE_SCREEN_BUFFER_INFO *csbi);
    char internal_get_cursor_char();

    void internal_welcome_screen();
    void internal_write_file();
    int internal_convert_coord_to_one_dimendion(const int x, const int y);
    void internal_update_map_to_print(int fruit_position);
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

class Head
{
private:
    int x;
    int y;
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
    static list<int> get_tail() { return get_instance().internal_get_tail(); }

private:
    Tail() {}
    void update_position();
    void internal_increase_size();
    void internal_draw();
    void internal_move();
    list<int> internal_get_tail() { return tail_list; }
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
    int get_fruit_position() { return fruit_position; }

private:
    void generate_position();
};

void print_score(int map_height, int score, int lives);
void print_colour_scheme();
void set_console_size();
void test_sound();
void increase_points(Fruit &fruit, int &score);
void updade_score(Fruit &fruit, int &score);
int calculate_digits(int val);
void print_information(int lives, int score, Timer &timer);
void imprimir_selecao_menu(char choice);
void weite_file();
