# Elevator Simulation

## About
A simple console-based simulation of an elevator given a starting floor and a list of floors to visit. Written in C++ by Nathan Glick.

## Usage
Compile and run the executable. Originally compiled using g++ and make, see the [makefile](https://github.com/nxg9997/ElevatorSimulation/blob/master/makefile) for more details. Instruction input should be in the form of `start=NUM floor=A,B,C,D`.

## Assumptions
 - Elevator can only move up and down
 - Floors are equidistant
 - There will be no additional floors added to the queue after starting
 - There is no maximum or minimum floor number (including allowing for negative floors if there is a basement)
 - Zero is a valid floor
 - There is only one elevator
 - Elevator should attempt to visit all floors efficiently
 - The time between multiple floors is equal to `n*SingleFloorTravelTime`, where `n` is the number of floors difference between the starting floor and the target floor
 - No requirement for time complexity consideration (although the final algorithm is O(n))

## Unimplemented Features
 - Real-time elevator with "call button" interrupts
 - Multiple Elevators
 - Multi-axis Elevators (more than up and down)
 - Reading input from a file (console input seemed fine for this project)
 - Main loop to allow for multiple runs without restarting the program