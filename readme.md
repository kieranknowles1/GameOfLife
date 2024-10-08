# Game of Life

Conway's Game of Life, implemented in C++
for CSC8501 Advanced Programming module at Newcastle University.

## Tasks
- [ ] Implement the game of life
  - [ ] Input for grid size
  - [ ] Input for initial alive cells
    - [ ] Distribute randomly
  - [ ] Input for number of generations
  - [ ] Show each step on an ASCII grid
  - [ ] Save and load from disk
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
  - [ ] Show number of attempts, and the grids of the final attempt's iterations
- [ ] Find the [efficiency resource number](https://conwaylife.com/wiki/Efficiency) for each experiment
  - [ ] Block/beehive
  - [ ] Blinker/toad
  - [ ] Glider/lightweight spaceship

## Techniques
- [ ] Use of functions
- [ ] Object orientation
- [ ] Operator overloading
- [ ] Polyphormism
- [ ] Templates
- [ ] Threading
- [ ] Command line interface for all tasks

## Methodology

- [ ] Generic way of finding patterns<br>
      Use a `Pattern` class to represent a pattern which
      has one or more frames.
      Gliders and spaceships can use a pattern that moves
        across the grid.
      Directions can be represented by checking each
      orientation of the pattern.
