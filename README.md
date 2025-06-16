# C++ Project Init Tool

A simple tool for setting up a simple C++ project file structure.

---

## Features
- Creates project folder with `src/`, `include/` and `target/` directories.
- Sets up `debug/` and `release/` directories inside of target directory.
- Generates base `.cpp` and `.clangd` file based on user config templates.

---

## Usage
- If the executable is run with a command line argument, it uses that as the project name.
  - `./project-init $PROJECT_NAME`
- If no command line arguments are given, the program prompts the user to enter a name.

---

## Requirements
- C++ compiler with C++17 support (for `std::filesystem` support)
