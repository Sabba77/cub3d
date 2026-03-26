*This project has been created as part of the 42 curriculum by lrosati, tisabbat.*

# cub3D

## Description
**cub3D** is a graphical project inspired by the early days of 3D rendering, notably the game *Wolfenstein 3D*. The goal of the project is to build a basic 3D engine using raycasting techniques, allowing the player to navigate through a maze from a first-person perspective.

The project was developed strictly following the subject requirements of the 42 curriculum. It focuses on understanding low-level graphics, mathematical concepts behind raycasting, and handling user input in real time.

## Features
- First-person 3D view using raycasting
- Player movement (forward, backward, rotation)
- Wall rendering with textures
- Map parsing from `.cub` file
- Collision detection
- Basic game loop and rendering system

## Instructions

### Requirements
- Linux or macOS
- GCC compiler
- Make

### Compilation
make

### Execution
./cub3D map.cub

Replace `map.cub` with the path to your map file.

### Controls
- W / S → Move forward / backward  
- A / D → Strafe left / right  
- Arrow keys → Rotate view  
- ESC → Exit the game  

## Technical Choices
The project is implemented in C using the MiniLibX graphical library provided by 42.  
Raycasting is used to simulate a 3D environment from a 2D map, projecting walls based on distance calculations.

Particular attention was given to:
- Efficient rendering
- Proper memory management
- Clean parsing of configuration files

## Resources
During the development of this project, we relied on various classic resources related to raycasting and graphics programming, such as:
- Lode's Computer Graphics Tutorial (raycasting)
- MiniLibX documentation
- General C programming references

Artificial Intelligence was used only as a support tool to:
- Better understand specific concepts (e.g., raycasting, math behind projections)
- Help debug certain issues encountered during development

It was not used to generate the core implementation of the project.

## Authors
- lrosati  
- tisabbat  
