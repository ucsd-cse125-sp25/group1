import subprocess
import platform
import sys
import os
from pathlib import Path


if platform.system() == "Windows":
    print("Please use WSL")
    sys.exit(1)

# Command-line arguments
source = sys.argv[1]
arguments = sys.argv[2:]

# Check if source file exists
if not os.path.isfile(source):
    print(f"No such source file: {source}")
    sys.exit(1)

# Construct compile command
compileCommand = [
    "g++",
    source,
    "-o", "script",
    "-lassimp"
]

executeCommand = "./script"

# Download libraries
if input("Type (Y) to install dependencies: ") == "Y":
    # macOS
    if platform.system() == "Darwin":
        packageManager = ["brew"]
        packages = ["assimp", "glm", "nlohmann-json"]

    # linux
    else:
        packageManager = ["sudo", "apt"]
        packages = ["libassimp-dev", "libglm-dev", "nlohmann-json3-dev"]

    print(f"Compiling: {' '.join(compileCommand)}")
    subprocess.run(["sudo", "apt", "update"])
    result = subprocess.run(packageManager + ["install"] + packages)
    if result.returncode != 0:
        print("Library download failed.")
        sys.exit(1)

# Run compile
print(f"Compiling: {' '.join(compileCommand)}")
result = subprocess.run(compileCommand)
if result.returncode != 0:
    print("Compilation failed.")
    sys.exit(1)

# Run executable
print(f"Running: {executeCommand} {' '.join(arguments)}")
result = subprocess.run([executeCommand] + arguments)
if result.returncode != 0:
    print("Program execution failed.")
    sys.exit(1)

# Cleanup
Path("script").unlink(missing_ok=True)