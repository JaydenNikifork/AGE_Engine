# AGE Engine

## Overview

The AGE Engine is a modular and extensible game engine designed to facilitate game development by providing a structured approach to managing game components and interactions. This README provides an overview of how to utilize the AGE Engine, its design philosophy, and the key components involved.

## Getting Started

To begin using the AGE Engine, follow these steps:

1. **Create a Game**: Instantiate a game object, which owns four key managers:
   - **Input Manager**: Scans for user input and sends data to logic components.
   - **Output Manager**: Processes data from logic components and outputs it.
   - **Scene Manager**: Manages the game's scenes.
   - **Game Clock**: Controls the game loop and timing.

2. **Attach Input Controllers and Output Views**: Default options include a keyboard controller for input and a terminal view for output. Custom controllers and views can also be created and attached.

3. **Develop Game Content**: 
   - **Create Scenes**: Scenes manage the state of different game levels and are controlled by the scene manager.
   - **Create Game Objects**: Define entities like players and enemies by inheriting from the abstract game object class. Implement their initialization and update methods.

4. **Utilize Components and Handlers**: 
   - **Components**: Encapsulate parts of a game object's state (e.g., position, appearance).
   - **Handlers**: Control how game objects react to different game states (e.g., input handling, collision response).

## Design Philosophy

The AGE Engine is designed with modularity and extensibility in mind. Key principles include:

- **Modularity**: Clients can create custom components, detectors, and handlers.
- **Extensibility**: The engine allows for easy addition of new features without modifying the core structure.

## Core Concepts

### Scenes and Game Objects

- **Scenes**: Represent different levels or game states. Each scene contains game objects and detectors.
- **Game Objects**: Abstract entities within the game. Clients define their behavior by implementing initialization and update methods.

### Detectors and Handlers

- **Detectors**: Identify events within the game state (e.g., input detection, collision detection).
- **Handlers**: Respond to detected events. Game objects inherit from handlers to define their reactions.

### Data Flow

The data flow within the engine follows the Model-Controller-Model-View pattern:

1. **Game Clock**: Initiates the loop and handles input scanning.
2. **Scene Manager**: Notified by the game clock, updates the active scene.
3. **Active Scene**: Updates game objects and runs detectors.
4. **Output Manager**: Receives data from the scene and outputs it.

### Custom Input and Output Streams

The engine uses customized input (`std::cin`-like) and output (`std::cout`-like) streams for handling global input and output operations.

## Extra Credit Features

### Scenes

Scenes simplify the management of different game states, allowing for easy transitions between levels or screens.

### Modularity and Extensibility

The engine supports the creation of custom components, handlers, detectors, input controllers, and output views. Default implementations are provided for ease of use.

## Development Insights

### Design and Development

A balance between design and development phases is crucial. Iterative development alongside UML diagramming can enhance efficiency and solution quality.

## Conclusion

The AGE Engine is a robust and flexible framework for game development, meeting project specifications while offering extensive customization options for client programmers. Its modular design encourages creativity and simplifies the extension of engine capabilities.

## Resources

- [Updated UML Diagram](https://drive.google.com/file/d/1eRmh9_VVjucdPjPLT2CcpFdZL7zfhung/view?usp=sharing)
