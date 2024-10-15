# Game of Life

Conway's Game of Life, implemented in C++
for CSC8501 Advanced Programming module at Newcastle University.

## Use of AI

GitHub Copilot was used during development to generate code, primarily to speed up the process of writing boilerplate code
and when it correctly predicted the next step in a work-in-progress function.

## Tasks
- [x] Implement the game of life
  - [x] Input for grid size
  - [x] Input for initial alive cells
    - [x] Distribute randomly
  - [x] Input for number of generations
  - [x] Show each step on an ASCII grid
  - [x] Save and load from disk
- [x] With grid larger than 30x30:
  - [x] With 25 alive cells
  - [x] Repeat until [block](https://conwaylife.com/wiki/Block) or [beehive](https://conwaylife.com/wiki/Beehive) pattern is reached
  - [x] Display number of attempts
  - [x] Only show iterations of final experiment
- [x] With 30x30 grid and 25 cells:
  - [x] Repeat until [blinker](https://conwaylife.com/wiki/Blinker) or [toad](https://conwaylife.com/wiki/Toad) pattern is reached
- [x] With 30x30 grid and 25 cells:
  - [x] Repeat until [glider](https://conwaylife.com/wiki/Glider) or [lightweight spaceship](https://conwaylife.com/wiki/Lightweight_spaceship) pattern is reached
- [x] For all experiments
  - [x] Input for max generations before stopping
  - [x] Input for grid size and starting alive cells
  - [x] Show number of attempts, and the grids of the final attempt's iterations
- [x] Find the [efficiency resource number](https://conwaylife.com/wiki/Efficiency) for each experiment
  - [x] Block/beehive
  - [x] Blinker/toad
  - [x] Glider/lightweight spaceship

## Techniques
- [x] Use of functions
  - [x] Behaviour is divided into functions with limited responsibility
- [x] Object orientation
  - [x] Board, Experiment, and Controller are all independednt classes
- [x] Operator overloading
  - [x] The Vec2 struct overloads some math operators to add other vectors or multiply by a scalar
  - [x] Array2D provides a subscript operator that takes a Vec2 position
- [x] Polyphormism
  - [x] Command and CommandFactory are abstract classes that are implemented by individual commands
- [x] Templates
  - [x] Array2D takes a template parameter for its data type
  - [x] CommandFactory takes a template for the command it creates, the command must implement specific fields and a constructor
- [x] Threading
  - [x] Experiment spawns multiple threads, each takes one task at a time until all are complete or one succeeds
- [x] Command line interface for all tasks
  - [x] Command line input is parsed using a simple `command <args>` format, `CommandParser` uses DI to construct the correct command.
        Input validation is primitive, but good enough for this project.

## Methodology

- [x] Generic way of finding patterns<br>
      Use a `Pattern` class to represent a pattern which
      has one or more frames.
      Gliders and spaceships can use a pattern that moves
        across the grid.
      Directions can be represented by checking each
      orientation of the pattern.
