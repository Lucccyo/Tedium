#include "../include/maze.h"

int main() {

    printf("Maze creation test\n");
    // Create the maze from folder maze/ and initialise the player to coordinate (0;0)
    Maze * maze = create_maze("maze/", 0, 0);
    printf("Maze created succesfully !\n");
    return 0;
}
