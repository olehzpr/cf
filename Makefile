.PHONY: all build install clean

# Default target
all: build

# Configure and build in Release mode
build:
	@echo "Configuring project in Release mode..."
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
	@echo "Building project..."
	cmake --build build

# Install the binary (system-wide)
install: build
	@echo "Installing cf to /usr/local/bin..."
	sudo cmake --install build --prefix /usr/local
	@echo "Installation complete! You can now use 'cf' from anywhere."

# Install the binary (local user)
install-user: build
	@echo "Installing cf to ~/.local/bin..."
	@mkdir -p ~/.local/bin
	@cp build/cf ~/.local/bin/
	@echo "Installation complete!"
	@echo "Make sure ~/.local/bin is in your PATH:"
	@echo "  export PATH=\"\$$HOME/.local/bin:\$$PATH\""

# Clean build artifacts
clean:
	@echo "Cleaning build directory..."
	@rm -rf build
	@echo "Clean complete!"
