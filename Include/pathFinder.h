#include <queue>
#include <map>
#include <algorithm>
#include <math.h>
#include "GMap.h"

using Coordinate = std::pair<int,int>;

struct Node
{
    float f =0;
    float g =0;
    float h =0;
    Coordinate parent;
    Coordinate coord;

    Node(){}

    Node(const Node &node)
        :g(node.g),h(node.h),f(node.f),parent(node.parent),coord(node.coord)
    {}

    Node(float G, float H, Coordinate prev,Coordinate self)
        :g(G),h(H),parent(prev),coord(self)
    {f=g+h;}
};

struct Compare
{
    bool operator()(Node const& n1, Node const& n2)
    {
        //return n2.f < n1.f;
        if(n1.f > n2.f)
            {return true;}
        else if (n2.f == n1.f)
            {return n1.g < n2.g;}//high g-value tie breaking
        else 
            {return false;}
    }
};

class PathFinder
{
private:
    const glm::vec3 OPENED_COLOR,CLOSED_COLOR,PATH_COLOR;
    const float D1=1,D2=1.5;
public:
    PathFinder(glm::vec3 opened,glm::vec3 closed,glm::vec3 path)
        :OPENED_COLOR(opened),CLOSED_COLOR(closed),PATH_COLOR(path)
    {}

    //Floodfill to confirm connection
    bool flood_fill(GMap &map,glm::vec3 flood_color);

    //A* utility functions
    float heuristic_function(Coordinate start,Coordinate goal);
    float cost_function(Coordinate start,Coordinate goal);
    void path_reconstruction(GMap &map,std::map<Coordinate,Node>& set, Node* current, Coordinate start);
    
    //A*
    bool aStar(GMap &map);
};