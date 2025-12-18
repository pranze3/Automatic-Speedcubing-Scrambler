# Automatic Rubik's Cube Scrambler

This repository contains the firmware and mechanical design files for an automated Rubik's Cube scrambler. The system parses standard WCA (World Cube Association) notation and executes precise motor movements to randomize the puzzle, eliminating the need for manual scrambling during practice sessions.

## <u>**Project Overview**</u>
This project was an exercise in **electromechanical integration**. The goal was to build a device that could take a string input (e.g., "R U R' U'") and translate it into physical actuation with high repeatability. It required tightly coupled firmware to manage motor acceleration profiles and ensure the mechanical grippers remained synchronized during high-speed operation.

## <u>**Firmware & Control**</u>
The core logic runs on an **Arduino** based platform using **C++**.
* **String Parsing:** I implemented a custom parser to interpret standard cube notation (including clockwise, counter-clockwise, and double turns) and convert them into a command queue.
* **Motor Control:** The firmware manages stepper motors using non-blocking interrupt-based timing to ensure smooth acceleration and deceleration. This prevents the cube from locking up during fast transitions.
* **State Machine:** A central state machine handles the operation lifecycle (Idle, clamping, Scrambling, Release).

## <u>**Hardware Design**</u>
The physical assembly consists of 3D-printed structural components and custom actuator mounts.
* **Mechanisms:** Designed 3D-printed grippers that interface with the center caps of the cube to allow for 6-axis rotation (or standard 3-axis depending on specific implementation).
* **Electronics:** Integrated stepper motor drivers and a dedicated power distribution system to handle the current spikes during motor actuation.

## <u>**Tools Used**</u>
C++, Arduino, SolidWorks/Fusion360 (CAD), 3D Printing, Stepper Motor Drivers.

