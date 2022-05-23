#pragma once
#include <queue>
#include <map>
#include <algorithm>
#include <math.h>
#include "GMap.h"

using Coordinate = std::pair<int,int>;

struct Node
{
    float g =0;
    float h =0;
    float f =0;
    Coordinate parent;
    Coordinate coord;

    Node(){}

    Node(const Node *node)
        :g(node->g),h(node->h),f(node->f),parent(node->parent),coord(node->coord)
    {}

    Node(float G, float H, Coordinate prev,Coordinate self)
        :g(G),h(H),parent(prev),coord(self)
    {f=g+h;}

    Node(float G, float H, float F,Coordinate prev,Coordinate self)
        :g(G),h(H),f(F),parent(prev),coord(self)
    {}
};

// struct Compare
// {
//     bool operator()(Node const& n1,Node const&  n2)
//     {
//         //return n2.f < n1.f;
//         if(n1.f > n2.f)
//             {return true;}
//         else if (n1.f == n2.f)
//             {return n1.g < n2.g;}//high g-value tie breaking
//         else 
//             {return false;}
//     }
// };

struct Compare
{
    bool operator()(Node const* n1,Node const*  n2)
    {
        //return n2.f < n1.f;
        if(n1->f > n2->f)
            {return true;}
        else if (n1->f == n2->f)
            {return n1->g < n2->g;}//high g-value tie breaking
        else 
            {return false;}
    }
};

class PathFinder
{
private:
    const int WIDTH,HEIGHT;
    const float D1=1,D2=std::sqrt(2);
public:
    PathFinder(int width,int height)
        :WIDTH(width),HEIGHT(height)
    {}

    bool flood_fill(GMap &map,glm::vec3 flood_color);

    bool aStar(GMap &map)
    {
        Coordinate start(map.getStart_end()[0]);
        Coordinate goal(map.getStart_end()[1]);

        std::map<Coordinate,Node> closed;
        std::map<Coordinate,Node> open;
        std::priority_queue<Node*,std::vector<Node*>,Compare> open_que;
        std::vector<Coordinate> neighbours;

        //insert start into open
        addToOpen(Node(0,heuristic_function(start,goal),start,start),open,open_que);
        // addToOpen(Node(0,1,1,start,Coordinate(1,1)),open,open_que);
        // addToOpen(Node(0,1,2,start,Coordinate(1,2)),open,open_que);
        //std::cout<<current.f<<std::endl;
        
        //while open not empty
        while(open_que.size()!=0)
        {        
            //current = top of priority
            Node current(*open_que.top());
            //remove current from open
            open_que.pop();
            open.erase(current.coord);
            //add current to closed
            closed[current.coord] = current;
            
            if (current.coord == goal)
            {
                //reconstruct
                return true;
            }
            
            neighbours = map.getNeighbours(current.coord);//get neighbours

            for (auto& nbr:neighbours)//for each neighbour
            {
                //consider neighbour
                //newg = current.g + cost(current,nbr)
                float newg = current.g + cost_function(current.coord,nbr);
                //if nbr in closed
                auto check_membership = closed.find(nbr);
                if(check_membership!=closed.end())
                {
                    if(check_membership->second.g<=newg)
                    {continue;}
                    else
                    {open.erase(nbr);}//remove nbr from closed because better path found
                }

                check_membership = open.find(nbr);
                if(check_membership!=open.end())
                {
                    if(check_membership->second.g<=newg)
                    {continue;}
                    else
                    {open.erase(nbr);}//remove nbr from open because better path found
                }
                //node = new Node(nbr)
                map.setCell(nbr,glm::vec3(1.0f,0.0f,0.0f));
                addToOpen(Node(newg,heuristic_function(nbr,goal),current.coord,nbr),open,open_que);
                //add node to open
            }
            map.setCell(current.coord,glm::vec3(1.0f,0.0f,1.0f));
        }
        return false;
    }

    void addToOpen(Node n,std::map<Coordinate,Node>& set,std::priority_queue<Node*,std::vector<Node*>,Compare>& que)
    {
        set[n.coord]=n;
        que.push(&set[n.coord]);
    }

    float heuristic_function(Coordinate start,Coordinate goal)
    {
        float dx = abs(start.first - goal.first);
        float dy = abs(start.first - goal.second);
        float cost = std::sqrt((dx*dx)+(dy*dy));//euclid
        return cost;
    }

    float cost_function(Coordinate start,Coordinate goal)
    {
        if(start.first==goal.first||start.second==goal.second)
        {return D1;}
        
        return D2; 
    }
};