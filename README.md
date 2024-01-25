# Super Mario World Remake with BAVE

## Overview

This project is a C++ remake of the classic Super Mario World game, utilizing the BAVE 2D graphics engine. The goal is to recreate the iconic gameplay and experience of the original Super Mario World with modern programming techniques and graphics capabilities.

## Features

- Classic Super Mario World gameplay mechanics.
- Utilizes the BAVE 2D graphics engine for rendering.
- Cross-platform support (Windows, Linux, macOS).
- Developed in VSCode with the most recent CMake release and C++20 features.

## Requirements

- [Visual Studio Code](https://code.visualstudio.com/)
- C++ compiler compatible with C++20 standard.
- Most recent CMake release.
- BAVE 2D graphics engine (link to BAVE GitHub repository).
- Additional dependencies (if any) listed in the BAVE documentation.

## NOTE: Project is currently being developed. It is not able to be run currently.

## Installation - Linux / UNIX

1. **Clone the repository:**

   ```bash
   git clone https://github.com/yourusername/super-mario-world-remake.git
   cd super-mario-world-remake

2. **Open the repository in VSCode:**

   ```bash
   code .

3. **Build the project using CMake**

   ```bash
   mkdir build
   cd build
   cmake ..
   make

4. **Run the executable**
   
   ```bash
   ./super_mario_world

## Installation - Windows

1. **Clone the repository:**
   
   ```bash
   git clone https://github.com/yourusername/super-mario-world-remake.git
   cd super-mario-world-remake

2. **Open the repository:**

   ```bash
   code .

3. **Build the project using CMake** (Notw: you may want to use the VSCode CMake Tools extension).

   ```bash
   mkdir build
   cd build
   cmake ..

3.(Extended) **Open the project in Visual Studio** (If you're not using VSCode as a dev environment).

- Open the generated solution in Visual Studio:
- Navigate to the build directory and open the super_mario_world.sln file in Visual Studio.
- Build and run the project in Visual Studio:
- Build and run the project using Visual Studio's build tools and debugger.

After building the project in Visual Studio, you can also run the executable from the output directory.

  
4. **Run the executable**

   ```bash
   cd Debug  # Or Release, depending on your build configuration
   ./super_mario_world
   
NOTE: On Windows, you might need to run the executable from the command prompt or directly from the file explorer.


## Contributing
- Fork the repository.
- Create a new branch: git checkout -b feature/your-feature.
- Commit your changes: git commit -m 'Add some feature'.
- Push to the branch: git push origin feature/your-feature.
- Open a pull request.

## License
This project is licensed under the MIT License.

## Acknowledgments
- BAVE 2D graphics engine contributors ([https://github.com/karnkaul/bave]).
- Nintendo for the original Super Mario World.
- Kaul (Core dev.)
- Arms / Mooshroom (Core dev.)
- Ian (Part-time dev.)
- Jake (Part-time dev.)
  
## Contact
For any questions or feedback, please contact armsgotarms@gmail.com.
