# 🎶 Out of Tune 🎼

## Setup Instructions

⚠️ Make sure you're using CMake 3.x (version 4.x won't work).

### 1. Initial Setup (First-Time Only)

Run these commands from the **project root directory**:

#### macOS / Linux
```bash
mkdir build
cd build
cmake ..
cmake --build .
./server    # Run server
./client    # Run client (open a separate terminal for each client)
```

#### Windows (Visual Studio)
```bash
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build .
./Debug/server.exe    # Run server
./Debug/client.exe    # Run client (open a separate terminal for each client)
```
⚠️ Important: Do not run executables from inside the Debug/ folder. Always run them from the **build/** directory–shader paths are resolved relative to the working directory, which is where you run the executable.

### 2. If You Add New .cpp or .hpp Files or Modify CMakeLists.txt

Run these commands from the **build directory**:

#### macOS / Linux
```bash
cmake ..
cmake --build .
./server
./client
```

#### Windows (Visual Studio)
```bash
cmake ..
cmake --build .
./Debug/server.exe
./Debug/client.exe
```

### 3. If You Just Modified Existing Files

Run these commands from the **build directory**:

#### macOS / Linux
```bash
cmake --build .
./server
./client
```

#### Windows (Visual Studio)
```bash
cmake --build .
./Debug/server.exe
./Debug/client.exe
```

## Controls

- **Mouse Movement**
  - Move the mouse up or down to look up and down.
  - Move the mouse left or right to look around and rotate the player's facing direction.

- **Keyboard Movement**
  - Use **W** / **Up Arrow** to move forward.
  - Use **S** / **Down Arrow** to move backward.
  - Use **A** / **Left Arrow** to strafe left.
  - Use **D** / **Right Arrow** to strafe right.
  - Press **Space** to jump.

- **Esc Key**
  - The game starts with the mouse locked and the cursor hidden (you can change direction with the mouse).
  - Press **Esc** to unlock the mouse and show the cursor (you cannot change direction when unlocked).
  - Press **Esc** again to lock the mouse and re-enable mouse input for camera control.
