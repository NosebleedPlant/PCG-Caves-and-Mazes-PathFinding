#include "map.h"

Map::Map(int width,int height,glm::vec3 dead, glm::vec3 alive)
    :WIDTH(width),HEIGHT(height),dead_color(dead),alive_color(alive),grid(91,std::vector<glm::vec3>(91))
{}

void Map::generateCaves(unsigned int step_count,unsigned int death_limit,unsigned int birth_limit,unsigned int threshold)
{
    randomPopulate(threshold);
    for (size_t i = 0; i < step_count; i++)
    {smoothMap(death_limit,birth_limit);}
}

void Map::randomPopulate(unsigned int threshold)
{
    //setup random seed
    std::random_device seed;
    std::mt19937 generate(seed());
    std::uniform_int_distribution<> distribution(1, 100);

    for (size_t y = 0; y < HEIGHT; y++)
    {
        for (size_t x = 0; x < WIDTH; x++)
        {
            if(x==0||x==WIDTH-1||y==0||y==HEIGHT-1)
                {grid[y][x] = dead_color;}
            else
                {grid[y][x] = distribution(generate)<50? alive_color:dead_color;}
        }
    }
}

void Map::smoothMap(unsigned int death_limit,unsigned int birth_limit)
{
    //std::array<std::array<glm::vec3,WIDTH>,HEIGHT> post_smoothing(grid);
    Grid post_smoothing(grid);
    for (size_t y = 1; y < HEIGHT-1; y++)
    {
        for (size_t x = 1; x < WIDTH-1; x++)
        {
            glm::vec3 current_cell = grid[y][x];
            unsigned int ngbrs = getNeighbourCount(x,y);
            if(current_cell == alive_color && ngbrs<death_limit)
                {post_smoothing[y][x]=dead_color;}//if alive but too few neighbours then dead                        
            else if(ngbrs>birth_limit)
                {post_smoothing[y][x]=alive_color;}//if dead but too many neighbours then alive
        }
    }
    grid = post_smoothing;
}

//OPERATOR OVERLOADS
std::ostream &operator<<(std::ostream &os,const Map &map)
{
    for (size_t y = 0; y < map.HEIGHT; y++)
    {
        for (size_t x = 0; x < map.WIDTH; x++)
        {
            if (map.grid[y][x]==map.dead_color)
                {os<<0;}
            else if (map.grid[y][x]==map.alive_color)
                {os<<1;}
            else
                {os<<"error!";}
        }
        os<<std::endl;
    }
    return os;
}
