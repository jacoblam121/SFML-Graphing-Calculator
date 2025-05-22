# Graphing Calculator in C++/SFML

This project is a graphing calculator implemented in C++ using the SFML library for its graphical interface. It parses mathematical expressions using the Shunting-yard algorithm and evaluates them using Reverse Polish Notation (RPN). This allows for a robust way to handle operator precedence and function calls.

## Features:
- **Mathematical Functions:**
    - Comprehensive trigonometric functions (e.g., sin, cos, tan, csc, sec, cot)
    - Inverse trigonometric functions (e.g., asin, acos, atan)
    - Hyperbolic trigonometric functions (e.g., sinh, cosh, tanh)
    - Absolute value (`abs`)
    - Natural logarithm (`ln`) and common logarithm (`log`)
- **Coordinate Systems:**
    - Cartesian coordinates (standard `x` input)
    - Polar coordinates (using `theta` as the variable)
- **Interactive Controls:**
    - Pan the graph view (Left/Right arrow keys)
    - Zoom in/out (Enter for zoom in, Shift+Enter for zoom out)
    - Input expression history and recall (via sidebar clicks)
    - Clear input history (Delete key)
- **Graphical Interface:**
    - Real-time graph plotting
    - Interactive sidebar for input and function history

## Key Components

The calculator is built from several key modules:

- **`Token` System (`includes/token/`):**
    - Defines various types of tokens (e.g., `Number`, `Operator`, `Function`, `LeftParen`, `RightParen`).
    - These tokens represent the individual parts of a mathematical expression.
- **`ShuntingYard` Algorithm (`includes/shunting_yard/`):**
    - Implements the Shunting-yard algorithm, which parses a list of tokens in infix notation (standard mathematical notation) and converts it into a postfix notation queue (Reverse Polish Notation - RPN).
    - This is crucial for correctly handling operator precedence and function calls.
- **`RPN` Evaluator (`includes/rpn/`):**
    - Takes the RPN queue produced by the Shunting-yard algorithm.
    - Evaluates the expression to produce a numerical result for a given `x` (or `theta`) value.
- **`Graph` Module (`includes/graph/`):**
    - Responsible for rendering the graph on the screen.
    - Handles coordinate transformations between mathematical coordinates and screen pixels.
    - Plots the points calculated by the RPN evaluator.
- **`Animate` Class (`includes/animate.h`, `includes/animate.cpp`):**
    - Manages the main SFML application window and the event loop.
    - Processes user input (keyboard and mouse) for panning, zooming, and expression entry.
    - Orchestrates rendering of the graph and sidebar.
- **Core Data Structures (`includes/array_functions/`, `includes/linked_list_functions/`, `includes/node/`, `includes/queue/`, `includes/stack/`):**
    - Provides fundamental data structures like dynamic arrays, linked lists, queues, and stacks.
    - These are used extensively by other components (e.g., Shunting-yard and RPN rely heavily on stacks and queues).
- **`Sidebar` UI (`includes/sidebar.h`, `includes/sidebar.cpp`):**
    - Manages the interactive sidebar in the GUI.
    - Displays input history, allows users to select previous expressions, and shows the current input.
- **`System` Orchestrator (`includes/system.h`, `includes/system.cpp`):**
    - Acts as a central coordinator for many operations.
    - Handles input from the `Animate` class, sends it for parsing and evaluation, and updates the `Graph` and `Sidebar`.

## How to Build

To build the graphing calculator, you will need:

- A C++ compiler that supports C++11 (e.g., GCC, Clang, MSVC).
- CMake (version 3.5 or higher).
- SFML libraries.

**SFML Installation:**

Ensure you have SFML installed on your system. You can typically install it using your system's package manager (e.g., `sudo apt-get install libsfml-dev` on Debian/Ubuntu, `brew install sfml` on macOS) or by downloading it from the [official SFML website](https://www.sfml-dev.org/download.php) and following their installation instructions.

**Build Steps:**

1.  **Create a build directory and navigate into it:**
    Assuming you are in the project's root directory:
    ```bash
    mkdir build
    cd build
    ```
2.  **Run CMake to configure the project:**
    ```bash
    cmake ..
    ```
    If SFML is installed in a non-standard location, you might need to help CMake find it. You can do this by setting the `SFML_DIR` CMake variable to the path of your SFML installation (where `SFMLConfig.cmake` is located). For example:
    ```bash
    cmake -DSFML_DIR=/path/to/sfml/lib/cmake/SFML ..
    ```
    Refer to the SFML and CMake documentation for more details.
3.  **Compile the project:**
    On Linux or macOS:
    ```bash
    make
    ```
    On Windows with Visual Studio:
    Open the generated solution file (`.sln`) in Visual Studio and build from there, or use MSBuild via the command line:
    ```bash
    cmake --build .
    ```

This will create the executables in a `bin` directory inside your `build` directory (e.g., `build/bin/main` or `build\bin\Debug\main.exe` on Windows).

## How to Run

After successfully building the project:

-   **Main Application:**
    The main graphing calculator executable is typically found at `build/bin/main`.
    Run it from the project's root directory:
    ```bash
    ./build/bin/main
    ```
-   **Tests:**
    The project includes tests built with Google Test. The test executables are typically found at `build/bin/basic_test` and `build/bin/testB`.
    You can run them similarly:
    ```bash
    ./build/bin/basic_test
    ./build/bin/testB
    ```
    These tests check basic functionality but appear to be templates. For more comprehensive testing, further development of test cases would be needed.

Upon running the main application, a window will open displaying the graph area and a sidebar for inputting mathematical expressions.

## Project Structure

The project's codebase is organized as follows:

-   **`main.cpp`**: The entry point for the main graphing calculator application.
-   **`includes/`**: Contains all header (`.h`) and implementation (`.cpp`) files for the core logic of the calculator.
    -   **`animate.h/.cpp`**: Manages the SFML window, event loop, and user interactions.
    -   **`array_functions/`**: Custom array data structure.
    -   **`constants.h`**: Defines various constants used throughout the project.
    -   **`exceptions/`**: Custom exception classes (e.g., `DivideByZero`).
    -   **`graph/`**: Handles graph plotting, coordinate systems, and related information.
    -   **`linked_list_functions/`**: Custom linked list data structure.
    -   **`node/`**: Node structures for linked lists and potentially other data structures.
    -   **`queue/`**: Custom queue data structure.
    -   **`random.h/.cpp`**: Utilities for random number generation (if used).
    -   **`rpn/`**: Implementation of the Reverse Polish Notation (RPN) evaluator.
    -   **`shunting_yard/`**: Implementation of the Shunting-yard parsing algorithm.
    -   **`sidebar.h/.cpp`**: Manages the UI sidebar.
    -   **`stack/`**: Custom stack data structure.
    -   **`stub/`**: Placeholder or template files, possibly for new module development.
    -   **`system.h/.cpp`**: Orchestrates interactions between different components.
    -   **`token/`**: Defines token types for expression parsing.
-   **`_tests/`**: Contains test files.
    -   **`_test_files/`**: Specific test case implementations (e.g., `basic_test.cpp`, `testB.cpp`).
-   **`CMakeLists.txt`**: The main CMake build script for the project.
-   **`README.md`**: This file.

This structure separates the main application logic, core components, and testing infrastructure.

## Contributing

Contributions to this project are welcome! If you'd like to contribute, please consider the following:

-   **Reporting Bugs:** If you find a bug, please open an issue in the project's issue tracker, providing as much detail as possible.
-   **Suggesting Enhancements:** Feel free to open an issue to suggest new features or improvements.
-   **Pull Requests:**
    1.  Fork the repository.
    2.  Create a new branch for your feature or bug fix (e.g., `git checkout -b feature/awesome-feature` or `git checkout -b fix/annoying-bug`).
    3.  Make your changes.
    4.  Add or update tests for your changes. (Currently, the test framework is in place but needs more comprehensive test cases.)
    5.  Ensure your code builds and tests pass.
    6.  Commit your changes and push to your fork.
    7.  Submit a pull request to the main repository.

Please try to adhere to the existing coding style and provide clear commit messages.
