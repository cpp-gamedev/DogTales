# Super Mario World Remake with BAVE

## Overview

This project is a C++ remake of the classic Super Mario World game, utilizing the BAVE 2D graphics engine. The goal is to recreate the iconic gameplay and experience of the original Super Mario World with modern programming techniques and graphics capabilities.

## Features

- Classic Super Mario World gameplay mechanics.
- Utilizes the BAVE 2D graphics engine for rendering.
- Cross-platform support (Windows, Linux, macOS).
- Developed in VSCode with the most recent CMake release and C++20 features.

## Requirements

- C++ IDE (recommended: [Visual Studio](https://visualstudio.microsoft.com/) or [Visual Studio Code](https://code.visualstudio.com/))
- C++20 compiler and standard library.
- CMake 3.23+.

## Building

### Visual Studio

1. Use Open Folder and select the project root. (Or use Open CMake and select the CMakeLists.txt in the project root.)
1. If using CMake presets, select `vs22`. Else select the build configuration (`x64-Debug` by default).
1. Select the build and debug target (name of the executable, currently `cppSMW`).
1. Build and debug/run.

### VSCode

1. Install related extensions such as clangd, CMake Tools, etc.
1. Open the project root as a folder.
1. Use the command palette (press Ctrl + Shift + P) and select "CMake: Configure". Select a preset: `default` or `ninja-ubsan` is recommended.
1. Use "CMake: Build" to build, "CMake: Debug" to debug.

## Installation - Linux / UNIX (TBD)

1. **Clone the repository:**

   ```bash
   git clone https://github.com/yourusername/super-mario-world-remake.git # this is incorrect
   cd super-mario-world-remake # this is incorrect

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

## Installation - Windows (TBD)

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
