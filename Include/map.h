#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <vector>
#include <queue>
#include <random>
#include <iostream>

using Coordinate = std::pair<int,int>;
using Grid = std::vector<std::vector<glm::vec3>>;

class Map
{
private:
    const int WIDTH,HEIGHT;
    glm::vec3 dead_color,alive_color;
    std::vector<Coordinate> start_end;
    Grid grid,recovery_grid;
public:
    //constructor class randomply populates the map
    Map(int width,int height,glm::vec3 dead, glm::vec3 alive);

    //generates caves using cellular automata
    void generateCaves(unsigned int step_count,unsigned int death_limit,unsigned int birth_limit,//smoothing params
                       unsigned int threshold=50);//initalize param

    //random population function that lets user set probability threshold from 1-100
    //ensures edges are dead
    void randomPopulate(unsigned int threshold);

    //smoothing function denioses based on cellular automata rules
    void smoothMap(unsigned int death_limit,unsigned int birth_limit);

    //OPERATOR OVERLOADS
    friend std::ostream &operator<<(std::ostream &os,const Map &map);

    //SETTERS:
    void setCell(const unsigned int x, const unsigned int y,glm::vec3 newValue)//change color of cell
    {grid[y][x] = newValue;}
    
    void setCell(Coordinate loc,glm::vec3 newValue)//change color of cell
    {grid[loc.second][loc.first] = newValue;}//because outside is y inside is x

    void setStartEndCells(glm::vec3 newValue)//change color of cell
    {
        setCell(start_end[0],newValue);//set start color
        setCell(start_end[1],newValue);//set goal color
    }

    bool setStartEnd(const unsigned int x, const unsigned int y,glm::vec3 newValue)//change color and set start or end point variable
    {
        // if(grid[y][x]==alive_color && start_end.size()<2)
        // {
        //     grid[y][x] = newValue;
        //     start_end.push_back(Coordinate(x,y));
            
        //     if(start_end.size()==2) 
        //     {return 1;}
        // }
        // return 0;

        if(grid[y][x]!=dead_color && start_end.size()<=2)
        {
            grid[y][x] = newValue;
            if(start_end.size()<2)
            {start_end.push_back(Coordinate(x,y));}
            else
            {start_end[1]= (Coordinate(x,y));}

            if(start_end.size()==2) 
            {   std::cout<<"set_goal"<<std::endl;
                grid = recovery_grid;
                return true;}
        }
        return false;
    }
    
    //GETTERS:
    const glm::vec3 getCell(const unsigned int x, const unsigned int y)const
    {return grid[y][x];}

    const glm::vec3 getCell(Coordinate loc)const
    {return grid[loc.second][loc.first];}

    std::vector<Coordinate> getStart_end() const 
    {return start_end;} 

    const unsigned int getNeighbourCount(const unsigned int o_x, const unsigned int o_y) const
    {
        unsigned int neighbour_count = 0;
        for (size_t y = o_y-1; y <= o_y+1; y++)
        {
            for (size_t x = o_x-1; x <= o_x+1; x++)
            {
                if((x!=o_x || y!=o_y) && grid[y][x] != dead_color)
                    {neighbour_count++;}
            }
        }
        return neighbour_count;
    }

    void getNeighbours(const Coordinate loc, std::queue<Coordinate> &que) const
    {
        unsigned int i_x = loc.first, i_y = loc.second;
        for (size_t y = i_y-1; y <= i_y+1; y++)
        {
            for (size_t x = i_x-1; x <= i_x+1; x++)
            {
                if(!(x==i_x && y==i_y) 
                    && (grid[y][x] != dead_color))
                {
                    que.push(Coordinate(x,y));
                }
            }
        }
    }

    std::vector<Coordinate> getNeighbours(const Coordinate loc) const
    {
        unsigned int i_x = loc.first, i_y = loc.second;
        std::vector<Coordinate> neighbours;
        for (size_t y = i_y-1; y <= i_y+1; y++)
        {
            for (size_t x = i_x-1; x <= i_x+1; x++)
            {
                if(!(x==i_x && y==i_y) 
                    && (grid[y][x] != dead_color))
                {
                    neighbours.push_back(Coordinate(x,y));
                }
            }
        }
        return neighbours;
    }
};