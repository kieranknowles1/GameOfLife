# Game of Life

Conway's Game of Life, implemented in C++
for CSC8501 Advanced Programming module at Newcastle University.

## Tasks
- [x] Implement the game of life
  - [x] Input for grid size
  - [x] Input for initial alive cells
    - [x] Distribute randomly
  - [x] Input for number of generations
  - [x] Show each step on an ASCII grid
  - [x] Save and load from disk
- [ ] With grid larger than 30x30:
  - [ ] With 25 alive cells
  - [ ] Repeat until [block](https://conwaylife.com/wiki/Block) or [beehive](https://conwaylife.com/wiki/Beehive) pattern is reached
  - [ ] Display number of attempts
  - [ ] Only show iterations of final experiment
- [ ] With 30x30 grid and 25 cells:
  - [ ] Repeat until [blinker](https://conwaylife.com/wiki/Blinker) or [toad](https://conwaylife.com/wiki/Toad) pattern is reached
- [ ] With 30x30 grid and 25 cells:
  - [ ] Repeat until [glider](https://conwaylife.com/wiki/Glider) or [lightweight spaceship](https://conwaylife.com/wiki/Lightweight_spaceship) pattern is reached
- [ ] For all experiments
  - [ ] Input for max generations before stopping
  - [ ] Input for grid size and starting alive cells
  - [ ] Show number of attempts, and the grids of the final attempt's iterations
- [ ] Find the [efficiency resource number](https://conwaylife.com/wiki/Efficiency) for each experiment
  - [ ] Block/beehive
  - [ ] Blinker/toad
  - [ ] Glider/lightweight spaceship

## Techniques
- [ ] Use of functions
- [ ] Object orientation
- [x] Operator overloading
  - [x] The Vec2 struct overloads some math operators to add other vectors or multiply by a scalar
  - [x] Array2D provides a subscript operator that takes a Vec2 position
- [ ] Polyphormism
- [x] Templates
  - [x] Array2D takes a template parameter for its data type
  - [x] CommandFactory takes a template for the command it creates, the command must implement specific fields and a constructor
- [ ] Threading
- [x] Command line interface for all tasks
  - [x] Command line input is parsed using a simple `command <args>` format, `CommandParser` uses DI to construct the correct command.
        Input validation is primitive, but good enough for this project.

## Methodology

- [ ] Generic way of finding patterns<br>
      Use a `Pattern` class to represent a pattern which
      has one or more frames.
      Gliders and spaceships can use a pattern that moves
        across the grid.
      Directions can be represented by checking each
      orientation of the pattern.
