# COPY FILES UTILITY CLI

Easily copy all files from subdirectories

## Requirements

- C++20 compatible compiler (GCC 10+, Clang 13+, or Apple Clang 13+)
- CMake 3.15+
- Make (optional, for simplified workflow)

## Building

### Using Make (Recommended)

```bash
# Build in Release mode (optimized)
make build

# The binary will be at: build/cf
```

### Using CMake directly

```bash
# Configure the project in Release mode
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build build

# The binary will be at: build/cf
```

## Installation

### System-wide installation (Unix/Linux/macOS)

```bash
# Using Make (builds in Release mode automatically)
make install

# Or using CMake directly
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
sudo cmake --install build --prefix /usr/local
```

### Local user installation

```bash
# Using Make (builds in Release mode automatically)
make install-user

# Make sure ~/.local/bin is in your PATH
echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.bashrc  # or ~/.zshrc
source ~/.bashrc  # or ~/.zshrc
```

## Usage

After installation, you can run the tool from anywhere:

```bash
cf [options]
```
