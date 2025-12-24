# COPY FILES UTILITY CLI

Easily copy all files from subdirectories

## Requirements

- C++20 compatible compiler (GCC 10+, Clang 13+, or Apple Clang 13+)
- CMake 3.15+ (recommended) or Make

## Building

### Using CMake

```bash
# Configure the project
cmake -S . -B build

# Build
cmake --build build

# The binary will be at: build/cf
```

## Installation

### System-wide installation (Unix/Linux/macOS)

```bash
# After building with CMake
sudo cmake --install build --prefix /usr/local

# Or manually copy the binary
sudo cp build/cf /usr/local/bin/
```

### Local user installation

```bash
# Copy to your local bin directory
mkdir -p ~/.local/bin
cp build/cf ~/.local/bin/

# Make sure ~/.local/bin is in your PATH
echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.bashrc  # or ~/.zshrc
source ~/.bashrc  # or ~/.zshrc
```

## Usage

After installation, you can run the tool from anywhere:

```bash
cf [options]
```
