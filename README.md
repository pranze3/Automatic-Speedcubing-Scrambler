# Automatic Speedcubing Scrambler

This repository contains the firmware and mechanical design files for an automated speedcubing scrambler. The system parses standard WCA (World Cube Association) notation and executes precise motor movements to randomize the puzzle, eliminating the need for manual scrambling during practice sessions.

## <u>**Project Overview**</u>
The goal of this project was to build a precision device capable of taking a string input (e.g., "R U R' U'") and translating it into physical motion with high repeatability. This required synchronizing C++ firmware with stepper motor drivers to manage acceleration profiles and ensure the mechanical grippers remained aligned during high-speed operation.

## <u>**Firmware & Control**</u>
The core logic runs on an **Arduino** platform using **C++**.
* **String Parsing:** I implemented a custom parser to interpret standard cube notation (including clockwise, counter-clockwise, and double turns) and convert them into a structured command queue.
* **Motor Control:** The firmware manages stepper motors using non-blocking interrupt-based timing. This allows for smooth acceleration and deceleration curves, preventing the cube from jamming during fast transitions.
* **Finite State Machine (FSM):** A central FSM handles the operational lifecycle (Idle, Clamp, Scramble, Release) to ensure safety and logic stability.

## <u>**Hardware Design**</u>
The physical assembly consists of custom 3D-printed components and actuator mounts.
* **Mechanisms:** Designed custom grippers in CAD that interface with the center caps of the cube, allowing for reliable torque transfer during rotation.
* **Electronics:** Integrated stepper motor drivers with a dedicated power distribution system to handle current spikes during simultaneous motor actuation.

## <u>**Tools Used**</u>
C++, Arduino, SolidWorks/Fusion360 (CAD), 3D Printing, Stepper Motor Drivers.
