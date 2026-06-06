# Physics Engine

<img width="1919" height="1018" alt="image" src="https://github.com/user-attachments/assets/ca81b547-4bea-4f84-b326-ef89c0b589d7" />

This project is a 2D physics simulation written in C++ and powered by SFML. It uses Verlet integration for smooth motion, handles circular rigid-body collisions, and includes simple wall constraints to keep objects within bounds. You can link objects together with spring-like connections, while a spatial grid system ensures collision checks stay fast and efficient. In the demo window, you can spawn, drag, delete, and connect objects to create interactive, cloth-like simulations in real time.

## Features

- Verlet-based object motion
- Gravity, wall constraints, bounce damping, and friction
- Circle-to-circle collision detection and resolution
- Spatial grid broad phase for faster collision checks
- Spring links between objects
- Cloth generation demo
- Runtime toggles for collisions, object rendering, link rendering, and substeps
- SFML rendering with FPS and object count overlays

## Demo Controls

| Input | Action |
| --- | --- |
| Left mouse button | Spawn random circular objects |
| Right mouse button | Drag a non-static object |
| Middle mouse button | Remove the object under the cursor |
| `S` | Clear the scene and create a cloth simulation |
| `C` | Clear all objects and links |
| `1` | Toggle collisions |
| `2` | Toggle object rendering |
| `3` | Toggle link rendering |
| `4` | Toggle substeps |

## Requirements

- Windows
- CMake 3.8 or newer
- A C++17 compiler
- Visual Studio Build Tools or Visual Studio with MSVC

## Build

From a Visual Studio Developer PowerShell or Developer Command Prompt:

```powershell
cmake --preset x64-release
cmake --build out/build/x64-release
```

The build copies the required SFML DLLs and assets into the output folder automatically.
