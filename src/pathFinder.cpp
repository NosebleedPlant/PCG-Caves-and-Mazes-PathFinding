#include "pathFinder.h"

bool PathFinder::flood_fill(GMap &map,glm::vec3 flood_color)
{
    Coordinate start = map.getStart_end()[0],end = map.getStart_end()[1];
    if(start==end)
    {return true;}

    Coordinate current = start;
    std::queue<Coordinate> que;
    map.getNeighbours(current,que);

    while(!que.empty())
    {
        current = que.front();
        que.pop();
        if(current==end)
        {
            return true;
        }
        else if(map.getCell(current)!= flood_color)
        {
            map.setCell(current,flood_color);
            map.getNeighbours(current,que);
        }                
    }
    std::cout<<"NO PATH TO GOAL"<<std::endl;
    return false;
}

float PathFinder::heuristic_function(Coordinate start,Coordinate goal)
{
    float dx = abs(start.first - goal.first);
    float dy = abs(start.second - goal.second);
    float cost = (D1 *(dx + dy)) + ((D2 - (2 * D1))* std::min(dx, dy));//octile distance
    return cost;
}

float PathFinder::cost_function(Coordinate start,Coordinate goal)
{
    if(start.first==goal.first||start.second==goal.second)
    {return D1;}
    
    return D2; 
}

void PathFinder::path_reconstruction(GMap &map,std::map<Coordinate,Node>& set, Node* current, Coordinate start)
{
    float cost=0;
    std::cout<<"cost of path: "<<current->g<<std::endl;
    while(current->coord!=start)
    {
        map.setCell(current->coord,PATH_COLOR);
        current = &set[current->parent];
    }
}

bool PathFinder::aStar(GMap &map)
{
    Coordinate start(map.getStart_end()[0]),goal(map.getStart_end()[1]);
            
    std::priority_queue<Node,std::vector<Node>,Compare> open;
    open.push(Node(0,heuristic_function(start,goal),start,start));

    std::map<Coordinate,Node> closed;
    std::vector<Coordinate> neighbours;        
 
    while(open.size()!=0)
    {
        //get new current node
        Node current(open.top());
        open.pop();

        //if current is already in closed
        auto check_membership = closed.find(current.coord);
        if(check_membership!=closed.end() && check_membership->second.coord==current.coord)
        {continue;}//continue

        //add current to closed
        closed[current.coord] = current;
        
        //if node is goal
        if(current.coord==goal)
        {
            std::cout<<"FOUND GOAL"<<std::endl;
            path_reconstruction(map,closed,&current,start);
            return true;
        }

        //get neighbours
        neighbours = map.getNeighbours(current.coord);

        //for each neighbour
        //std::cout<<current.coord.first<<","<<current.coord.second<<std::endl;
        for (auto& nbr:neighbours)
        {
            //if neighbour in closed
            check_membership = closed.find(nbr);
            if(check_membership!=closed.end())
            {continue;}//continue
                            
            //add neighbour to open
            map.setCell(nbr,OPENED_COLOR);
            float g = current.g + cost_function(current.coord,nbr);
            float h =heuristic_function(nbr,goal);
            //std::cout<<nbr.first<<","<<nbr.second<<": "<<g<<","<<h<<std::endl;
            open.push(Node(g,h,current.coord,nbr));
        }
        map.setCell(current.coord,CLOSED_COLOR);
    }
    return false;
}