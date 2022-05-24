#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <vector>
#include <queue>
#include <random>
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
    std::vector<Coordinate> getNeighbours(const Coordinate loc) const;

    //OPERATOR OVERLOADS:
    // ------------------------------------------------------------------------
    friend std::ostream &operator<<(std::ostream &os,const GMap &map);
};