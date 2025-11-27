# COMP2401 - FINAL PROJECT PHASMAPHOBIA SIMULATION

## 📘 Introduction
This project demonstrates my understanding of the topics covered in COMP2401.

Designed specifically for CUGHS to simulate the procedures of their operation.

A map of connected rooms. Four hunters, each with a single device to take readings of evidence from a room. A ghost, wandering around and leaving
evidence for hunters to find. When a hunter is in a room with a ghost, their fear level goes from 0 to 100, and when they reach 100, they’re out of there!

Every ghost leaves behind three distinct kinds of evidence. We get readings in every room of course. There’s also sounds and temperatures to track, but a ghost leaves behind a special form of evidence. If we can find all three of those special kinds of evidence, we can identify the ghost and get rid of it


## 📝 Description

The program performs a straightforward sequence of operations:
- Generate a determined map/terrain/layout.
- Randomly spawn one of 24 ghosts available in our database in any of the room in the map.
- User will be asked to create many hunters as they wishes by providing name and id repeatedly. Finish with a hunter name 'done'
- The simulation will run automatically.
- The result of the match will be output to the screen.
- The program will output a log file for each entity in the simulation under .csv file
- The provided python program will be used to validate the accuracy of the logs in accordance to the actual program execution.

The project consists of these multiple files:
- ghost.h/ghost.c: containing the implementations of the methods to be used by ghost entity.
- helpers.h/helpers.c: containing the implementations of the miscellanious helper methods including logging, convert strings, etc.
- room.h/room.c: containing the implementations of the utilities belong to room.
- hunter.h/hunter.c: containing the implementations of the methods to be used by hunter entity.
- defs.h: containing definition of the business models in the project.
- main.c: the entry point to the program
- makefile: quick compilation source.

## 🔁 How to run

Please strictly adhere to the provided guide:

    # code block
    cd to the directory that contains the source codes (including main.c and makefile)
    ```

    Compile the code automatically with makefike:
     ```
    # code block
    make
    ```

    After compilation, run below command to execute:
    # code block
    ./main
    ```

    A set of provided inputs have been given in the input folder:
    # code block
    ./main < [NUMBER_OF_INPUT].txt
    ```

    Validate the log by using the Python file
    # code block
    python3 validate_logs.py
    ```