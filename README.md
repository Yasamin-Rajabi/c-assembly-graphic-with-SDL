# SDL Ball Shooting Game & Assembly Optimization

**Course:** Computer Structure & Language (ساختار زبان کامپیوتر)  
**University:** Sharif University of Technology  
**Semester:** Fall 2024-2025  
**Developer:** Yasamin Rajabi  
**Student ID:** 402111197

## 🎮 Overview

This project is a simple yet engaging game built with C++ and the SDL2 library. The objective is to shoot a ball into a moving goal. The player can adjust the shot's angle, initial velocity, and even choose the ball's trajectory (straight, diagonal, or sinusoidal). The ball also features a spinning animation during flight.

A core academic focus of this project was to explore low-level optimization by rewriting critical performance functions in x86 Assembly, aiming to improve the game's frame rate and efficiency.

## ✨ Features

*   **Gameplay:** Shoot a ball with customizable physics (angle, speed, trajectory type) into a moving goal.
*   **Graphics:** Implemented using the SDL2 library for rendering and window management.
*   **Physics:** Implements real-time calculations for ball movement, including trigonometric functions for different trajectories.
*   **Performance Analysis:** Includes a dedicated testing mode (`test.cpp`) to benchmark performance with and without optimizations.
*   **x86 Assembly Optimization:** Key functions were rewritten in assembly to leverage SIMD instructions and FPU operations for potential performance gains.

## 📊 Performance Results

The `test.cpp` program automates the shooting process and measures execution time.

| Shot Type     | # of Shots | Normal Code (ms) | Assembly Code (ms) | Improvement |
| :------------ | :--------- | :--------------- | :----------------- | :---------- |
| Diagonal      | 50         | 26386            | 25436              | ~4%         |
| Diagonal      | 100        | 51791            | 51070              | ~2%         |
| Straight      | 70         | 14497            | 13526              | ~7%         |
| Straight      | 140        | 37919            | 36592              | ~4%         |

**Conclusion:** The hand-written assembly for ball movement provided a consistent, measurable performance boost.
