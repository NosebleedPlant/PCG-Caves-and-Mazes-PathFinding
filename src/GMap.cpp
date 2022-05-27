#include "GMap.h"

GMap::GMap(int dim,glm::vec3 dead, glm::vec3 alive)
    :DIM(dim),dead_color(dead),alive_color(alive),grid(91,std::vector<glm::vec3>(91))
{}

//CELLULAR AUTOMATA:
// ------------------------------------------------------------------------
void GMap::generateCaves(unsigned int step_count,unsigned int death_limit,unsigned int birth_limit,unsigned int threshold)
{
    randomPopulate(threshold);//randomly populate
    for (size_t i = 0; i < step_count; i++)//smooth the map till specified step
    {smoothMap(death_limit,birth_limit);}
}

void GMap::randomPopulate(unsigned int threshold)
{
    //setup random seed
    std::random_device seed;
    std::mt19937 generate(seed());
    std::uniform_int_distribution<> distribution(1, 100);

    for (int y = 0; y < DIM; y++)
    {
        for (int x = 0; x < DIM; x++)
        {
            if(x==0||x==DIM-1||y==0||y==DIM-1)
                {grid[y][x] = dead_color;}
            else
                {grid[y][x] = distribution(generate)<threshold? alive_color:dead_color;}//if not an outside wall then randomly dead or alive
        }
    }
}

void GMap::smoothMap(unsigned int death_limit,unsigned int birth_limit)
{
    //std::array<std::array<glm::vec3,DIM>,DIM> post_smoothing(grid);
    Grid post_smoothing(grid);
    for (int y = 1; y < DIM-1; y++)
    {
        for (int x = 1; x < DIM-1; x++)
        {
            glm::vec3 current_cell = grid[y][x];
            unsigned int ngbrs = getNeighbourCount(x,y);
            if(current_cell == alive_color && ngbrs<death_limit)
                {post_smoothing[y][x]=dead_color;}//if alive but too few neighbours then dead                        
            else if(ngbrs>birth_limit)
                {post_smoothing[y][x]=alive_color;}//if dead but too many neighbours then alive
        }
    }
    grid = post_smoothing;//assign the smoothed grid to our grid variable
    recovery_grid = post_smoothing;//back up the grid to allow undo
}

//PRIMS ALGO:
// ------------------------------------------------------------------------

//GETTERS
// ------------------------------------------------------------------------
const glm::vec3 GMap::getCell(const unsigned int x, const unsigned int y) const
{return grid[y][x];}

const glm::vec3 GMap::getCell(Coordinate loc)const
{return grid[loc.second][loc.first];}

const std::vector<Coordinate> GMap::getStart_end() const 
{return start_end;} 

const unsigned int GMap::getNeighbourCount(const unsigned int i_x, const unsigned int i_y) const
{
    unsigned int neighbour_count = 0;
    for (int y = i_y-1; y <= i_y+1; y++)
    {
        for (int x = i_x-1; x <= i_x+1; x++)
        {
            if(!(x==i_x && y==i_y)
                && (x>=0 && x<DIM && y>=0 && y<DIM) 
                && (grid[y][x] != dead_color))//make sure neighbour is not dead and increment
            {neighbour_count++;}
        }
    }
    return neighbour_count;
}

void GMap::getNeighbours(const Coordinate loc, std::queue<Coordinate> &que) const
{
    int i_x = loc.first, i_y = loc.second;
    for (int y = i_y-1; y <= i_y+1; y++)
    {
        for (int x = i_x-1; x <= i_x+1; x++)
        {
            if(!(x==i_x && y==i_y)
                && (x>=0 && x<DIM && y>=0 && y<DIM) 
                && (grid[y][x] != dead_color))//make sure neighbour is not dead and push to que
            {
                que.push(Coordinate(x,y));
            }
        }
    }
}

void GMap::getNeighbours(const Coordinate loc, std::vector<Coordinate> &list) const
{
    int i_x = loc.first, i_y = loc.second;
    for (int y = i_y-1; y <= i_y+1; y++)
    {
        for (int x = i_x-1; x <= i_x+1; x++)
        {
            if(!(x==i_x && y==i_y)
                && (x>=0 && x<DIM && y>=0 && y<DIM) 
                && (grid[y][x] != dead_color))//make sure neighbour is not dead and add to vector
            {
                list.push_back(Coordinate(x,y));
            }
        }
    }
    return;
}

//SETTERS
// ------------------------------------------------------------------------
void GMap::setCell(const unsigned int x, const unsigned int y,glm::vec3 newValue)
{grid[y][x] = newValue;}//because outside is y inside is x

void GMap::setCell(Coordinate loc,glm::vec3 newValue)
{grid[loc.second][loc.first] = newValue;}//because outside is y inside is x

void GMap::setStartEndCells(glm::vec3 newValue)
{
    setCell(start_end[0],newValue);//set start color
    setCell(start_end[1],newValue);//set goal color
}

bool GMap::setStartEnd(const unsigned int x, const unsigned int y,glm::vec3 newValue)
{
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

//OPERATOR OVERLOADS
// ------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &os,const GMap &map)
{
    for (int y = 0; y < map.DIM; y++)
    {
        for (int x = 0; x < map.DIM; x++)
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
