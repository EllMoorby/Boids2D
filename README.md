# Boids 2D with Quadtress using SMFL

A small project which implements [boids](https://cs.stanford.edu/people/eroberts/courses/soco/projects/2008-09/modeling-natural-systems/boids.html) and [quadtrees](https://en.wikipedia.org/wiki/Quadtree) in 2D using [SFML](https://www.sfml-dev.org/) in C++.

<img src="https://github.com/user-attachments/assets/b1cc29bb-42e5-4f54-b5f9-7f017e7112e6" alt="drawing" width="600"/>

## Building and running on your own machine
### Prerequisites
You will need:
- [CMake](https://cmake.org/download/) (≥ 3.28)
- [Git](https://git-scm.com/downloads)
- C++ compiler (GCC ≥ 9, Clang ≥ 10, or MSVC ≥ 2019)

And SFML dependencies:
Linux (Ubuntu/Debian)
```
sudo apt install libopenal-dev libx11-dev libxrandr-dev libfreetype6-dev libgl1-mesa-dev libudev-dev
```
macOS (Homebrew)
```
brew install openal-soft freetype
```
Windows (vcpkg)
```
vcpkg install openal-soft freetype
```

### Build
```sh
# Clone the repository
git clone https://github.com/EllMoorby/Boids2D.git
cd Boids2D

# Build using cmake
cmake -B build && cmake --build build
```
### Run
Linux/macOS
```
./build/bin/Boids2D
```
Windows
```
.\build\bin\Boids2D.exe
```
