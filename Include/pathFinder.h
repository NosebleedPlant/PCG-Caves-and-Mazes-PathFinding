#include <queue>
#include <map>
#include <algorithm>
#include "map.h"

using Coordinate = std::pair<int,int>;

struct Node
{
    int f =0;
    int g =0;
    int h =0;
    Coordinate parent;
    Coordinate coord;

    Node(){}

    Node(const Node &node)
        :g(node.g),h(node.h),parent(node.parent),coord(node.coord)
    {f=g+h;}

    Node(int G, int H, Coordinate prev,Coordinate self)
        :g(G),h(H),parent(prev),coord(self)
    {f=g+h;}

    friend bool operator<(Node const& n1, Node const& n2)
    {
        return n2.f < n1.f;
    }
};

class PathFinder
{
private:
    const int WIDTH,HEIGHT;
    const int D1=1,D2=1;
public:
    PathFinder(int width,int height)
        :WIDTH(width),HEIGHT(height)
    {}

    bool flood_fill(Map &map,glm::vec3 flood_color)
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

    int heuristic_function(Coordinate start,Coordinate goal)
    {
        int dx = abs(start.first - goal.first);
        int dy = abs(start.second - goal.second);
        return (D1 * ((dx + dy) + (D2 - 2 * D1)) * std::min(dx, dy));
    }

    int cost_function(Coordinate start,Coordinate goal)
    {
        if(start.first==goal.first||start.second==goal.second)
        {return D1;}
        
        return D2; 
    }

    void path_reconstruction(Map &map,std::map<Coordinate,Node>& set, Node* current, Coordinate start)
    {
        while(current->coord!=start)
        {
            map.setCell(current->coord,glm::vec3(0.0f,0.0f,1.0f));
            current = &set[current->parent];
        }
    }

    bool aStar(Map &map)
    {
        Coordinate start(map.getStart_end()[0]);
        Coordinate goal(map.getStart_end()[1]);
                
        std::priority_queue<Node> open;
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
            for (auto& nbr:neighbours)
            {
                //CONSISTENT
                //if neighbour in closed
                check_membership = closed.find(nbr);
                if(check_membership!=closed.end() && check_membership->second.coord==current.coord)
                {continue;}//continue
                map.setCell(nbr,glm::vec3(1.0f,0.0f,0.0f));
                
                //add neighbour to open
                int g = current.g + cost_function(nbr,goal);
                int h =heuristic_function(nbr,goal);
                open.push(Node(g,h,current.coord,nbr));
            }
        }
        return false;
    }
};