#!/bin/bash
echo "Building Auth Server (Legacy Script)..."
g++ src/AuthServer.cpp -Iinclude -o auth_server.bin
echo "Build complete. (Warning: No tests executed)"
