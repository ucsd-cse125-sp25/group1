# 🎶 Out of Tune 🎼

## Setup Instructions

Cmake of version 3.x is required to build the project. Cmake build will fail with cmake version 4.x.

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
