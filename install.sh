#!/bin/bash

if command -v pacman &> /dev/null; then
	echo "Detected Arch Linux (pacman)"
	sudo pacman -S gcc make
elif command -v apt &> /dev/null; then
	echo "Detected Debian/Ubuntu (apt)"
	sudo apt-get update
	sudo apt-get install -y build-essential
fi 

# Build and install
make
sudo make install

echo "systemfetch has been successfully installed!"
