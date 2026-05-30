# Distributed Access Control System (RFID)

## Project Overview
This project implements a multi-architecture Distributed Access Control System. It consists of two primary components:
1. **Embedded Smart Card Reader (`embedded/`)**: Runs on ARM architecture. Responsible for reading RFID badges and enforcing local security logic, including a strict 3-strike brute-force lockout 
mechanism.
2. **Authorization Server (`server/`)**: Runs on x86_64 architecture. Handles the core business logic, simulating a database lookup to authorize or deny badge IDs.

## System Dependencies
To ensure a consistent development and CI/CD environment, this project is containerized. 

### Recommended Setup (Docker)
We highly recommend using Docker to ensure all cross-compilation toolchains and static/dynamic analyzers are configured correctly.
* **Docker Engine** must be installed on your host machine.

### Manual Setup (Ubuntu 22.04)
If you prefer not to use Docker, your host machine must have the following dependencies installed:
* `build-essential` (Native x86_64 compiler)
* `g++-aarch64-linux-gnu` (ARM cross-compiler)
* `cmake` (>= 3.14)
* `qemu-user` & `qemu-user-static` (For emulating ARM test binaries)
* `clang-tidy` (Static analysis)
* `doxygen` (Documentation generation)
* `gcovr` (>= 8.x via `pip3`, for modern C++ code coverage reports)

---

## Configuration and Build Instructions

### 1. Set Up the Docker Environment
Build and enter the unified development environment.

```bash
# Build the Docker image
docker build -t rfid-build-env .

# Run the container interactively
docker run -it rfid-build-env /bin/bash
```

### 2. Configure the Project
Inside the container, use CMake to configure the project. The root `CMakeLists.txt` handles both the server and embedded subdirectories.

```bash
# Standard Configuration
cmake -B build -S .

# Dynamic Analysis Configuration (Optional)
# Compiles with AddressSanitizer and UndefinedBehaviorSanitizer
cmake -B build -S . -DCMAKE_BUILD_TYPE=Sanitize
```

### 3. Build the Binaries
Compile both the embedded ARM logic and the x86_64 server logic simultaneously:

```bash
cmake --build build
```

### 4. Run Unit Tests
The project uses Google Test. Because the environment utilizes `qemu-user-static`, you can run both the x86_64 and ARM tests natively from the build directory.

```bash
cd build
ctest --output-on-failure
```

### 5. Generate Documentation
You can automatically generate HTML documentation from the source code comments using the custom Doxygen target:

```bash
cmake --build build --target docs
```
The documentation will be generated and available in the `build/html/` or `build/Doxyfile` directory.

### 6. Generate Code Coverage
To generate a detailed HTML coverage report, you must first configure the project with coverage enabled, run the tests, and then execute the coverage target:

```bash
# Configure with coverage enabled
cmake -B build -S . -DENABLE_COVERAGE=ON

# Build and generate the HTML report via gcovr
cmake --build build --target coverage
```
The resulting report will be saved to `build/coverage/index.html`.
