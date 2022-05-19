#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <array>
#include <random>
#include <iostream>

template<int WIDTH,int HEIGHT>
class Map
{
private:
    glm::vec3 dead_color,alive_color;
    std::array<std::array<glm::vec3,WIDTH>,HEIGHT> grid;
public:
    //constructor class randomply populates the map
    Map(glm::vec3 dead, glm::vec3 alive)
        :dead_color(dead),alive_color(alive)
    {}

    void generateCaves(unsigned int step_count,unsigned int death_limit,unsigned int birth_limit,//smoothing params
                       unsigned int threshold=50)//initalize param
    {
        randomPopulate(threshold);

        for (size_t i = 0; i < step_count; i++)
        {
            smoothMap(death_limit,birth_limit);
        }
        
    }

    //random population function that lets user set probability threshold from 1-100
    //ensures edges are dead
    void randomPopulate(unsigned int threshold)
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
                    grid[y][x] = dead_color;
                else
                    grid[y][x] = distribution(generate)<50? alive_color:dead_color;
            }
        }
    }

    void smoothMap(unsigned int death_limit,unsigned int birth_limit)
    {
        std::array<std::array<glm::vec3,WIDTH>,HEIGHT> post_smoothing(grid);
        for (size_t y = 1; y < HEIGHT-1; y++)
        {
            for (size_t x = 1; x < WIDTH-1; x++)
            {
                glm::vec3 current_cell = grid[y][x];
                unsigned int ngbrs = getNeighbourCount(x,y);
                if(current_cell == alive_color && ngbrs<death_limit)
                    post_smoothing[y][x]=dead_color;//if alive but too few neighbours then dead                        
                else if(ngbrs>birth_limit)
                    post_smoothing[y][x]=alive_color;//if dead but too many neighbours then alive
            }
        }
        grid = post_smoothing;
    }
    
    //GETTERS:
    inline const glm::vec3 getCell(const unsigned int x, const unsigned int y)const
    {
        return grid[y][x];
    }
    const unsigned int getNeighbourCount(const unsigned int o_x, const unsigned int o_y) const
    {
        unsigned int neighbour_count = 0;
        for (size_t y = o_y-1; y <= o_y+1; y++)
        {
            for (size_t x = o_x-1; x <= o_x+1; x++)
            {
                if((x!=o_x || y!=o_y) && grid[y][x] == alive_color)
                {
                    neighbour_count++;
                }
            }
        }
        return neighbour_count;
    }

    //SETTERS:
    void setCell(const unsigned int x, const unsigned int y,glm::vec3 newValue)
    {
        grid[y][x] = newValue;
    }

    //OVERLOADS
    friend std::ostream &operator<<(std::ostream &os,const Map &map)
    {
        for (size_t y = 0; y < HEIGHT; y++)
        {
            for (size_t x = 0; x < WIDTH; x++)
            {
                if (map.grid[y][x]==map.dead_color)
                    os<<0;
                else if (map.grid[y][x]==map.alive_color)
                    os<<1;
                else
                    os<<"error!";
            }
            os<<std::endl;
        }
        return os;
    }
};