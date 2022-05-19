#include "map.h"

// Map::Map(glm::vec3 dead, glm::vec3 alive)
//     :dead_color(dead),alive_color(alive)
// {
//     randomPopulate();
// }

// void Map::randomPopulate()
// {
//     //setup random seed
//     std::random_device seed;
//     std::mt19937 generate(seed());
//     std::uniform_int_distribution<> distribution(1, 10);

//     for (size_t y = 0; y < height; y++)
//     {
//         for (size_t x = 0; x < width; x++)
//         {
//             if (distribution(generate)%2==0)
//             {
//                 //grid[y][x] = dead_color;
//                 std::cout<<"1";
//             }
//             else
//             {
//                 //grid[y][x] = alive_color;
//                 std::cout<<"0";
//             }
//         }
//     }
// }

// std::ostream& Map::operator<<(std::ostream& os)
// {
    
//     for (size_t y = 0; y < height; y++)
//     {
//         for (size_t x = 0; x < width; x++)
//         {
//             if (grid[y][x]==dead_color)
//                 os<<0;
//             else if (grid[y][x]==alive_color)
//                 os<<1;
//             else
//                 os<<"error!";
//         }
//         os<<std::endl;
//     }
//     return os;
// }

// inline const glm::vec3 Map::getCell(unsigned int x, unsigned int y)const
// {
//     return grid[y][x];
// }

// void Map::setCell(unsigned int x, unsigned int y,glm::vec3 newValue)
// {
//     grid[y][x] = newValue;
// }