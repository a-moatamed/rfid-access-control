# Base Image
FROM ubuntu:22.04

# Environment
ENV DEBIAN_FRONTEND=noninteractive

# Multi-Architecture Repo Setup (For cross-compiling to ARM)
RUN sed -i 's/deb http/deb [arch=amd64] http/g' /etc/apt/sources.list && \
    echo "deb [arch=arm64] http://ports.ubuntu.com/ubuntu-ports/ jammy main restricted universe multiverse" >> /etc/apt/sources.list && \
    echo "deb [arch=arm64] http://ports.ubuntu.com/ubuntu-ports/ jammy-updates main restricted universe multiverse" >> /etc/apt/sources.list && \
    echo "deb [arch=arm64] http://ports.ubuntu.com/ubuntu-ports/ jammy-security main restricted universe multiverse" >> /etc/apt/sources.list

RUN dpkg --add-architecture arm64

# Install toolchains, utilities, static analysis, and documentation tools
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    g++-aarch64-linux-gnu \
    qemu-user \
    qemu-user-static \
    clang-tidy \
    doxygen \
    python3-pip \
    && pip3 install --no-cache-dir gcovr \
    && rm -rf /var/lib/apt/lists/*

# Workspace
WORKDIR /app

# Keeps the container alive interactively if run manually
CMD ["/bin/bash"]
