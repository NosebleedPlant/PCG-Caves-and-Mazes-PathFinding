#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <vector>
#include <queue>
#include <random>
#include <stack>
#include <iostream>

using Coordinate = std::pair<int,int>;
using Grid = std::vector<std::vector<glm::vec3>>;

/*
Author: Yalmaz
This class handels the creation of the maps and adjusts of cells in that map
*/
class GMap
{
private:
    const glm::vec3 dead_color,alive_color;
    std::vector<Coordinate> start_end;
    Grid grid,recovery_grid;
public:
    const int DIM;
    //constructor class randomply populates the map
    GMap(int dim,glm::vec3 dead, glm::vec3 alive);

    //CELLULAR AUTOMATA:
    // ------------------------------------------------------------------------
    //generates caves using cellular automata
    void generateCaves(unsigned int step_count,unsigned int death_limit,unsigned int birth_limit,//smoothing params
                       unsigned int threshold=50);//initalize param

    //random population function that lets user set probability threshold from 1-100
    //ensures edges are dead
    void randomPopulate(unsigned int threshold);

    //smoothing function denioses based on cellular automata rules
    void smoothMap(unsigned int death_limit,unsigned int birth_limit);
    
    //PRIMS ALGO:
    // ------------------------------------------------------------------------
    void initalize()
    {
        for (size_t y = 0; y < DIM; y++)
        {
            for (size_t x = 0; x < DIM; x++)
            {
                if (y%2==1||x%2==1)
                {grid[y][x]=dead_color;}
            }
        }
    }
    
    void getOrthogonalNeighbours(Coordinate loc,std::vector<Coordinate> &list)
    {
        const int i_x=loc.first;
        const int i_y=loc.second;       

        for (int y = i_y-2; y <= i_y+2;)
        {
            for (int x = i_x-2; x <= i_x+2;)
            { 
                if((x==i_x || y==i_y)//only orthogonal
                    && !(x==i_x && y==i_y)//not self
                    && (x>=0 && x<DIM && y>=0 && y<DIM)//in range 
                    && (grid[y][x] != alive_color))//alive
                {
                    list.push_back(Coordinate(x,y));
                    if(x==0&&y==0)
                    std::cout<<"pushed "<<std::endl;
                }
                x+=2;
            }
            y+=2;
        }
    }

    std::vector<Coordinate>::iterator select_randomly(std::vector<Coordinate>::iterator start, std::vector<Coordinate>::iterator end) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
        std::advance(start, dis(gen));
        return start;
    }

    void removeWall(Coordinate start, Coordinate end)
    {
        int wall_x = (end.first-start.first)/2;
        int wall_y = (end.second-start.second)/2;
        Coordinate wall = Coordinate(start.first+wall_x,start.second+wall_y);
        setCell(wall,alive_color);
        // std::cout<<"start: "<<start.first<<","<<start.second<<std::endl;
        // std::cout<<"wall: "<<wall.first<<","<<wall.second<<std::endl;
        // std::cout<<"end: "<<end.first<<","<<end.second<<std::endl;
        // std::cout<<"------------"<<std::endl;
    }

    void generateMaze()
    {
        initalize();//initalize map with walls

        Coordinate current(40,40);//choose start point(randomize this)
        std::stack<Coordinate> stack;//stack
       
        stack.push(current);//push to stack
        //get unvisted neighbours
        //while stack not empty
        //for (size_t i = 0; i < 100; i++)        
        while (stack.empty()!=true)
        {
            //pop top as current
            current = stack.top();
            stack.pop();

            std::vector<Coordinate> neighbours;
            getOrthogonalNeighbours(current,neighbours);
            //if current has unvisted neighbours
            if(neighbours.size()>0)
            {
                stack.push(current);//push current back on to stack, work incomplete
                Coordinate selection = *select_randomly(neighbours.begin(),neighbours.end());//choose unvisted neighbour
                //Coordinate selection = neighbours[0];
                removeWall(current,selection);//remove wall between current and chosen neighbour
                setCell(selection,alive_color);//mark chosen as visited
                stack.push(selection);//push to stack
                //std::cout<<"current: "<<current.first<<","<<current.second<<std::endl;
                //std::cout<<"selection: "<<selection.first<<","<<selection.second<<std::endl;
            }
        }
        recovery_grid = grid;
    }

    //SETTERS:
    // ------------------------------------------------------------------------
    //change color of cell given x,y
    void setCell(const unsigned int x, const unsigned int y,glm::vec3 newValue);
    
    //change color of cell given Coordinate
    void setCell(Coordinate loc,glm::vec3 newValue);
    
    //change location of and set start or end point variable
    bool setStartEnd(const unsigned int x, const unsigned int y,glm::vec3 newValue);

    //change color of start and end cell given
    void setStartEndCells(glm::vec3 newValue);

    //GETTERS:
    // ------------------------------------------------------------------------
    //get cell given x,y
    const glm::vec3 getCell(const unsigned int x, const unsigned int y)const;

    //get cell given coordinate
    const glm::vec3 getCell(Coordinate loc)const;

    //get start and end location
    const std::vector<Coordinate> getStart_end() const;

    //get number of living neighbours given x,y
    const unsigned int getNeighbourCount(const unsigned int i_x, const unsigned int i_y) const;

    //get coordinates of neighbours and add to que 
    void getNeighbours(const Coordinate loc, std::queue<Coordinate> &que) const;

    //get coordinates of neighbours and return as vector
    void getNeighbours(const Coordinate loc, std::vector<Coordinate> &list) const;

    //OPERATOR OVERLOADS:
    // ------------------------------------------------------------------------
    friend std::ostream &operator<<(std::ostream &os,const GMap &map);
};