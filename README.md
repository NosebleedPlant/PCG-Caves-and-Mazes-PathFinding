# PCG Caves and Mazes + PathFinding
Goals of this mini project is to apply the following knowledge I have aquired: 

- C++ Programming
- Basic OpenGL
- Procedural Caves using Cellular Automata
- Mazes using Randomized Depth First
- Pathfinding

**Currently only tested for windows**
## About:
This is a simple application that randomly generates caves or a maze and allows users to pathfind using A* between two points. The outputs are displayed using opengl. The purpose of this project as stated above was to exercise my understanding of various things I had picked up in classes outside of an academic setting in hopes of better ingraining them into my skillset. The visualization shows the flood fill used to detect if the start and end is actually connected as well as the nodes opened and closed by A*. The yellow nodes represent the optimal path

## Preview:

![main_WkehY7PNUw](https://user-images.githubusercontent.com/42461443/170180387-ee5c4d32-9605-4db9-903a-3c1228d0c44c.gif)

## To compile:

- clone repo
- ensure mingw64 is installed if not adjust the .vscode files accordingly
- open in vscode
- navigate to ```src/main.cpp```
- run build task with ```Ctrl+Shift+B``` in vscode after confirming the directories are correct
- launch using ```./main -Caves``` flag for cave generation or ```./main -Maze``` for maze generation

## Reflection:
Overall I enjoyed working on this off and on for the past month ish. I was able to learn alot and thuroughly review my c++ which was nice. The biggest hurdle was coming to grips with opengl's eccentricities at the beggining, A-star also tripped me up a bit but mostly because of a few silly mistakes. I played the whole project by the ear as I was reviewing and learning along with it so the overall design of the code didnt get much time. Next time I would like to sit down and thuroughly plan out my project before hand.The Maze currently genertaes from the same starting point which reduces vairance a bit which is something I might change in the future. The pathfinding currently uses the same heuristic for both caves and maze which results in unneccissary searching in maze since diagonal movement is not possible. If working on something like this again it would be good to asses such things before hand and incorporate them into my design.
