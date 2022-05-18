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
    Map(glm::vec3 dead, glm::vec3 alive, unsigned int threshold = 50)
        :dead_color(dead),alive_color(alive)
    {
        randomPopulate(threshold);
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
                    grid[y][x] = distribution(generate)<50? dead_color:alive_color;
            }
        }
    }

    void SmoothMap()
    {
        for (size_t y = 0; y < HEIGHT; y++)
        {
            for (size_t x = 0; x < WIDTH; x++)
            {
                
            }
        }
    }
    
    //GETTERS:
    inline const glm::vec3 getCell(const unsigned int x, const unsigned int y)const
    {
        return grid[y][x];
    }
    const unsigned int getWallCount(const unsigned int x, const unsigned int y) const
    {
        //IMPLEMENT THIS!!!!
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