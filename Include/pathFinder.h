#include <queue>
#include "map.h"

using Coordinate = std::pair<int,int>;

class PathFinder
{
private:
public:
    void flood_fill(Map &map)
    {
        //add coordinate to to que
        //while que not empty:
        //check if top is goal
        //yes:terminate
        //no:add immediate neighbours to que
        Coordinate start = map.getStart_end()[0],end = map.getStart_end()[1];
        if(start==end)
        {return;}

        Coordinate current;
        std::queue<Coordinate> que;
        que.push(start);
        std::cout<<end.first<<","<<end.second<<std::endl;
        std::cout<<start.first<<","<<start.second<<std::endl;
        std::cout<<"..............."<<std::endl;
        
        while(!que.empty())
        {
            current = que.front();
            //std::cout<<current.first<<","<<current.second<<std::endl;
            que.pop();
            if(current==end)
            {
                std::cout<<"found you"<<std::endl;
                break;
            }
            else if(map.getCell(current)!= glm::vec3(0.0f,1.0f,0.0f))
            {
                map.setCell(current,glm::vec3(0.0f,1.0f,0.0f));
                map.getNeighbours(current,que,glm::vec3(0.0f,1.0f,0.0f));
            }                
        }
    }
};