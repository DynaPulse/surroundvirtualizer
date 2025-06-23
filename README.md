# Surround Virtualizer

**Surround Virtualizer** is an advanced audio processing application that creates immersive surround sound experiences using Head-Related Transfer Functions (HRTF). It leverages OpenAL and PortAudio for real-time 3D audio processing, and can act as a virtual audio pipeline between any application (such as a game or media player) and your actual audio output device.

---

## Table of Contents
- [Project Structure](#project-structure)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Build Instructions](#build-instructions)
- [Dependencies](#dependencies)
- [Security](#security)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

---

## Project Structure
```plaintext
surroundvirtualizer/
├── app/                   # Main application entry point
├── include/headers/       # Header files for project modules
├── HRTF Files/            # HRTF files for audio processing
├── lib/                   # External libraries (OpenAL, PortAudio)
├── src/                   # Source files for project modules
├── build_script.bat       # Windows build and install script
├── CMakeLists.txt         # CMake build script
├── LICENSE                # License file (GPL v3)
├── README.md              # Project documentation
├── SECURITY.md            # Security policy and reporting
├── .gitignore             # Git ignore file
└── .github/               # GitHub workflows and CI
```

## Features
- Real-time 3D audio processing using HRTF
- Acts as a virtual audio pipeline: receives multi-channel audio from any app, processes it, and outputs stereo
- User-selectable input (virtual) and output (real) devices
- Modular, extensible architecture
- Supports multiple HRTF file formats
- Cross-platform codebase (Windows-focused, but portable)

## Installation

### Prerequisites
- **CMake** (>= 3.10)
- **OpenAL** library
- **PortAudio** library
- **C++17** compatible compiler (MSVC recommended on Windows)

### Clone the Repository
```bash
git clone https://github.com/DynaPulse/surroundvirtualizer.git
cd surroundvirtualizer
```

## Usage

### Virtual Audio Pipeline Setup
1. **(Recommended)** Install a virtual audio device (e.g., [VB-Cable](https://vb-audio.com/Cable/) or [Virtual Audio Cable](https://vac.muzychenko.net/en/)).
2. Set the virtual device as the default output in Windows or in your game/media player.
3. Run Surround Virtualizer, select the virtual device as input and your real device as output.
4. The app will process multi-channel audio from the virtual device and output stereo to your headphones/speakers.

### Running the Application
After building (see below), run:
```bash
./build/bin/SurroundVirtualizer
```
Follow the CLI prompts to select input/output devices and HRTF file.

### Configuration
- HRTF files are in the `HRTF Files/` directory. Select at runtime via the CLI.
- The CLI allows you to choose both the input (virtual) and output (real) devices.

## Build Instructions

### Using the Provided Script (Windows)
```bash
build_script.bat
```
This script cleans, builds, installs, and launches the app. Binaries and DLLs are placed in `install_app/bin/`.

### Manual Build with CMake
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
cmake --install . --prefix ../install_app
```

## Dependencies

### OpenAL
- Used for spatial audio rendering. Ensure `OpenAL32.dll` is in `lib/OpenALlibs/bin/`.

### PortAudio
- Used for audio I/O. Ensure `portaudio_x64.dll` is in `lib/PortAudioLibs/bin/`.

You can use a package manager (e.g., **vcpkg**, **conan**) or place the DLLs manually.

## Security
- See [SECURITY.md](SECURITY.md) for the security policy and how to report vulnerabilities.

## Contributing
- Fork, branch, commit, push, and open a Pull Request.
- Follow code style, document your code, and ensure it builds and runs cleanly.

## License
This project is licensed under the **GNU General Public License (GPL) v3**. See [LICENSE](LICENSE).

## Contact
For questions or suggestions, open an issue or contact the maintainer via GitHub: [DynaPulse](https://github.com/DynaPulse).
