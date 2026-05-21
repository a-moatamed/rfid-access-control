#!/bin/bash
echo "Building Embedded Door Reader (Legacy Script)..."
# Hardcoded to local gcc, no cross-compilation support!
g++ src/DoorReader.cpp -Iinclude -o door_reader.bin
echo "Build complete. (Warning: No tests executed)"
