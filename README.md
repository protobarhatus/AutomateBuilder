# AutomateBuilder
This is my C++/Qt school project program. This is a program that allows to create and then run *cellular automaton*. It gives a variaty of tools to create wide range of
different automatons.
## Cellular automaton
A cellular automaton is a discrete model of computation studied in automata theory. Cellular automata are also called cellular spaces,
tessellation automata, homogeneous structures, cellular structures, tessellation structures, and iterative arrays. Cellular automata have found application in various
areas, including physics, theoretical biology and microstructure modeling.
A cellular automaton consists of a regular grid of cells, each in one of a finite number of *states*, such as on and off (in contrast to a coupled map lattice).
The grid can be in any finite number of dimensions (but in this program, it's 2-dimensional). For each cell, a set of cells called its neighborhood is defined relative
to the specified cell. An initial state (time t = 0) is selected by assigning a *state* for each cell. A new generation is created (advancing t by 1), according to some
fixed *rule* that determines the new *state* of each cell in terms of the current *state* of the cell and the *states* of the cells in its *neighborhood*. The rule of updating
the cell is the same for all cells and all cells are updated simultaneously.

## Creation of automaton

Window of creation of automaton (in empty automaton) looks like that: 

![image](https://user-images.githubusercontent.com/51193423/178118953-25da28ee-0e40-4343-a048-8ece3868cc51.png)

### States

The left most column shows existing in automaton *states* - discrete values. Each *cell* at any moment is in one of this states. States have *name*, *value* and
*texture* - color or uploaded image.

### Functions of neighborhood

The next column shows *functions of neighborhood*. These functions refer to some cell (relatively to current) and return it's value. User may prepare unlimited
amount of these functions. By default exists 8 functions - neighboring up, upper right, right, down right, down, down left, left, up left cells.
If function is *"ALLOWED"* - then it is participating in forming cell's *neighborhood* - cells that have distance = 1 with the current cell. 
By default the *Moore neighborhood* is set. Functions can be "banned" or "allowed" dynamicly by rules.

### Variables

The third column is a list of *variables*. Variables are counted each step before execution of the *rules* and can be used in rules. They can be *logical*
or *numerical*. Also, they can be *local* or *global* - local variable is calculated individually for each cell, and global is calculated once for a turn.

### Rules

Finally, the last column containes list of *rules*. Their structure looks like that: `condition ? action if true : action if false ` (actions are optional in both cases).
Conditions are set by arithmetical and logical operators, variables, neighborhood functions and different build-in functions.
Action can be two types - set a *state* to current cell, or ban/allow neighborhood function.

## Simulation of automaton

After creation of automaton it can be simulated. In simulation window, there is main field where automaton is executed. At the top there are buttons -
start, pause, stop simulation, turn on/off build mode, flush all from the field, and return camera to the center. At the right there is list
of all states. To set some state to the cell, just choose it at the right and click on the cell:

![simulation field](https://user-images.githubusercontent.com/51193423/178119447-5b7acffb-2cca-4aa2-a043-3ab1fffb58ba.gif)

### Configurations

You can save as many fields at a time as you want. In each *configuration*, the field size, default state and initial layouts are all saved.

## Example
Here is an example of *Conway's Game of Life* - very simple and famous automaton that can be created here in just a minute.

![image](https://user-images.githubusercontent.com/51193423/178119645-4046b24b-27cc-4502-9f92-f1dae929bf84.png)




![Glider gun demo (2)](https://user-images.githubusercontent.com/51193423/178119813-c7463a86-a424-4c9d-899c-b97ad2670000.gif)


## Installation
If you are on Windows 10 or higher, just launch setup.exe file that is in repository or compile it yourself on Qt 5.14.1+ with MSVC17





