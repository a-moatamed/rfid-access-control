# RFID Access Control System

![C++](https://img.shields.io/badge/C++-17-blue.svg) ![CMake](https://img.shields.io/badge/CMake-Build-success.svg) ![Docker](https://img.shields.io/badge/Docker-Environment-2496ED.svg) ![GitLab 
CI](https://img.shields.io/badge/GitLab-CI%2FCD-FC6D26.svg) ![Coverage](https://img.shields.io/badge/Coverage-100%25-brightgreen.svg)

The **Distributed Access Control System** is a C++17 project that simulates a secure RFID-based door access solution composed of two independent subsystems. The project was developed using modern 
C++ development practices, including automated testing, static analysis, dynamic analysis, code coverage reporting, containerization, and continuous integration.

## Table of Contents
- [System Architecture](#system-architecture)
- [Security Features](#security-features)
- [Project Structure](#project-structure)
- [Getting Started (Build & Run)](#getting-started-build--run)
- [Advanced Analysis](#advanced-analysis)
- [Development Environment](#development-environment)
- [Documentation](#documentation)
- [Contributors](#contributors)

---

## System Architecture

The system is divided into two major components:

### 1. Embedded Component
Models the behavior of a physical door controller.
* **Responsibilities:** Maintaining door security state, processing authorization results, tracking failed authentication attempts, triggering lockout protection, and supporting administrative 
recovery.
* **States:**

| State | Description |
| :--- | :--- |
| `LOCKED` | Default secure state. |
| `UNLOCKED` | Access granted. |
| `ALARM_LOCKOUT` | Security lockout triggered after repeated failed attempts. |

### 2. Server Component
Simulates backend credential verification.
* **Responsibilities:** Managing authorized RFID badge identifiers, validating badge credentials, rejecting invalid badge IDs, and supporting badge registration/removal.

---

## Security Features

* **Failed Attempt Protection:** The embedded controller tracks consecutive failed badge scans. After **three** consecutive failures, the controller enters `ALARM_LOCKOUT` and ignores further scans, 
simulating physical brute-force protection.
* **Administrative Recovery:** An administrator can restore normal operation, clearing the lockout and resetting the system to `LOCKED` with zero failed attempts, using `reader.adminReset();`.

---

## Project Structure

```text
rfid-access-control/
├── embedded/
│   ├── include/          # Embedded headers (DoorReader.hpp)
│   ├── src/              # Embedded source logic
│   └── tests/            # GoogleTest suite for Embedded
├── server/
│   ├── include/          # Server headers (AuthServer.hpp)
│   ├── src/              # Server source logic
│   └── tests/            # GoogleTest suite for Server
├── CMakeLists.txt        # Master build configuration
├── Dockerfile            # Containerized environment
├── Doxyfile.in           # Documentation configuration
└── README.md
```

---

## Getting Started (Build & Run)

### Requirements
* CMake 3.14+
* GCC or Clang with C++17 support
* Git

### 1. Build the Project
Configure and compile the project using CMake:
```bash
# Create the build directory and enter it
mkdir -p build && cd build

# Configure the project
cmake ..

# Compile the code
make
```

### 2. Run the Unit Tests
The project relies on **GoogleTest** to validate authorization, lockouts, recovery transitions, and server management. Run the test suite:
```bash
# From inside the build directory
ctest --output-on-failure
```

---

## Advanced Analysis

### Code Coverage
Coverage reporting is implemented using **gcovr**. To generate an HTML report of your test coverage:
```bash
# Configure with coverage enabled
cmake -S . -B build -DENABLE_COVERAGE=ON

# Run the tests and generate the report
cd build
make coverage
```
*The generated report will be located at:* `build/coverage/index.html`

### Static & Dynamic Analysis
* **Static Analysis:** **clang-tidy** is integrated directly into the CMake build process to enforce modern C++ practices and maintainability during compilation.
* **Dynamic Analysis:** AddressSanitizer (ASan) and UndefinedBehaviorSanitizer (UBSan) are available via a custom build configuration to detect memory leaks and undefined behavior.
```bash
# Run the dynamic analysis build
cmake -S . -B build-san -DCMAKE_BUILD_TYPE=Sanitize
cmake --build build-san
ctest --test-dir build-san
```

---

## Development Environment

A Docker environment is provided to ensure reproducible builds, equipped with GCC, CMake, GoogleTest, clang-tidy, gcovr, Doxygen, QEMU, and an ARM64 cross-compilation toolchain.

```bash
# Build the container image
docker build -t rfid-builder .

# Run the container interactively (with local directory synced)
docker run -it --rm -v ${PWD}:/app rfid-builder
```
*Note: A GitLab CI/CD pipeline is also configured to automatically run compilation, testing, coverage, and documentation generation on every push.*

---

## Documentation

To generate the HTML documentation locally using **Doxygen**:
```bash
cmake -S . -B build-docs
cmake --build build-docs --target docs
```
*Output location:* `build-docs/docs/html`

---

## Contributors

**Version 1.0**

* **Abdelrahman ABOMOSA**
* **MAHAZOASY Narindra Elthéor Dylane**
* **Ștefan-Ioan VOINESCU**
* **Waleed HUSSAIN**

