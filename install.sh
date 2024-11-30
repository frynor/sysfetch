#!/bin/bash

if command -v pacman &> /dev/null; then
	echo "Detected Arch Linux (pacman)"
	sudo pacman -S gcc make
elif command -v apt &> /dev/null; then
	echo "Detected Debian/Ubuntu (apt)"
	sudo apt-get update
	sudo apt-get install -y build-essential
elif command -v brew &> /dev/null; then
	echo "Detected macOS (Homebrew)"
	brew install gcc make
else 
	echo "No supported package manager found. Please install build tools manually."
	exit 1
fi 

# Build and install
make
sudo make install

echo "systemfetch has been successfully installed!"
