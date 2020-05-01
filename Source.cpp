#include "header.h"






System::System(/* args */)
{
}

System::~System()
{
}

void System::show_consol_cursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

int System::generate_ramdom_number()
{
    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937 mt_rand(seed);
    return mt_rand();
}

void Timer::start()
{
    m_StartTime = std::chrono::system_clock::now();
    m_bRunning = true;
}

void Timer::stop()
{
    m_EndTime = std::chrono::system_clock::now();
    m_bRunning = false;
}

double Timer::elapsedMilliseconds()
{
    std::chrono::time_point<std::chrono::system_clock> endTime;

    if (m_bRunning)
        endTime = std::chrono::system_clock::now();
    else
        endTime = m_EndTime;

    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
}

void gotoxy(short x, short y)
{
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

string Map::get_file_content(const string path)
{
    /*
	    Utiliza um iterator - ponteiros para enderecos de memoria- para construir uma string com os dados da ifstream - input file stream.
		- istreambuf_iterator<char>(file)) = iterator para o inicio do arquivo
		- istreambuf_iterator<char>() = iterator para o final do arquivo
	*/

    ifstream file("Map.txt"); // Ponteiro para o local do arquivo
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    return content;
}

int Map::calculate_width()
{
    return (canvas.find('\n') + 1);
}

int Map::calculate_height()
{
    return (canvas.size() / width) + 1;
}

Map::Map()
{
    this->canvas = get_file_content("Map.txt");
    this->width = calculate_width();
    this->height = calculate_height();
}

void Map::print()
{
    gotoxy(0, 0);
    cout << canvas << endl;
}



bool Head::hit(){
    return this->wall_shock;

}
int Head::find_position()
{
    return canvas.find('0');
}

int Head::detect_wall(char key_pressed)
{
    int wall_position = 0;
    int head_lock_ahead = calculate_next_position(key_pressed);
    if (canvas.at(head_lock_ahead) == '#')
    {
        wall_position = head_lock_ahead;
    }
    return wall_position;
}

int Head::detect_tail(char key_pressed)
{
    int tail_position = 0;
    int head_lock_ahead = calculate_next_position(key_pressed);
    if (canvas.at(head_lock_ahead) == 'o')
    {
        tail_position = head_lock_ahead;
    }
    return tail_position;
}




bool Head::detect_shock(char key_pressed)
{
    bool head_hit_tail = false;
    bool head_hit_wall = false;
    int head_lock_ahead = calculate_next_position(key_pressed);

    /*for(int tail_node : this->tail_list){
        if(tail_node == this->head_position)
        {
            head_hit_tail = true;
        }
    }*/

    if (this->head_position == this->tail_position){
        head_hit_tail = true;
        
    }
        
    else if (this->head_position == this->head_last_position)
        head_hit_wall = true;
    if (this->head_position == this->wall_position)
        head_hit_wall = true;

    return head_hit_wall||head_hit_tail;
}



void print_score(int map_height, int score, int lives)
{
    gotoxy(1, map_height + 2);
    cout << "Score: " << score << endl;
    gotoxy(1, map_height + 3);
    cout << "Lives: " << lives << endl;
}

Fruit::Fruit()
{
    this->fruit_position = find_position(canvas);
}

int Fruit::find_position(string& map)
{
    int fruit_position = canvas.find('*');

    if (canvas.find('*') == string::npos)
    {
        System sys;

        fruit_position = sys.generate_ramdom_number() % canvas.length();

        while (canvas.at(fruit_position) != ' ')
            fruit_position = sys.generate_ramdom_number() % canvas.length();

        map.replace(fruit_position, 1, "*"); //Paramters: Position, Size, Content

    }

    return fruit_position;
}
int Fruit::get_position()
{
    return this->fruit_position;
}

void Fruit::draw(string &map)
{
    System sys;

    int fruit_position = sys.generate_ramdom_number() % map.length();

    while (map.at(fruit_position) != ' ')
        fruit_position = sys.generate_ramdom_number() % map.length();

    map.replace(fruit_position, 1, "*"); //Paramters: Position, Size, Content

    this->fruit_position = fruit_position;
}



