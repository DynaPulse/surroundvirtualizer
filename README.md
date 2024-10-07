# Surround Virtualizer

**Surround Virtualizer** is an audio processing project designed to create immersive surround sound experiences using Head-Related Transfer Functions (HRTF). The project leverages OpenAL and PortAudio libraries to provide 3D audio processing and playback capabilities.

## Table of Contents

- [Project Structure](#project-structure)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Build Instructions](#build-instructions)
- [Dependencies](#dependencies)
- [Contributing](#contributing)
- [License](#license)

## Project Structure

```plaintext
surroundVirtualizer/
├── app/                   # Contains the main application entry point
├── include/headers/       # Header files for the project's modules
├── HRTF Files/            # HRTF files used for audio processing
├── lib/                   # External libraries (OpenAL and PortAudio)
├── src/                   # Source files for the project modules
├── build_setup.bat        # Script for setting up the build environment
├── CMakeLists.txt         # CMake build script
├── LICENSE                # License file (GPL v3)
├── README.md              # Project documentation (this file)
└── .gitignore             # Git ignore file
```

## Features

- Real-time 3D audio processing using HRTF.
- Integration with OpenAL and PortAudio libraries for cross-platform audio support.
- Configurable and modular architecture for easy extension.
- Supports multiple HRTF file formats for flexibility.

## Installation

### Prerequisites

Make sure you have the following dependencies installed:

- **CMake** (version >= 3.10)
- **OpenAL** library
- **PortAudio** library

Clone the repository to your local machine:

```bash
git clone https://github.com/sagartx31/surroundvirtualizer.git
cd surroundvirtualizer
```

### Directory Setup

Ensure that your directory structure matches the one outlined in the [Project Structure](#project-structure) section. This will help in finding the necessary dependencies and libraries during the build process.

## Usage

### Running the Application

To run the application, build it first (instructions below), then execute the following command:

```bash
./build/bin/SurroundVirtualizer
```

The application will initialize and start processing audio using the default HRTF settings.

### Configuration

- HRTF files are located in the **HRTF Files/** directory. You can switch between different HRTF profiles by replacing the files in this directory or modifying the code to load specific files at runtime.
- The **cli_interface** module provides a command-line interface for configuring and controlling the audio processing parameters.

## Build Instructions

### Using the Provided Script (Windows Only)

If you're using Windows, you can use the `build_setup.bat` script:

```bash
build_setup.bat
```

This will set up the build environment and generate the necessary binaries.

### Manual Build with CMake

Alternatively, you can build the project manually using CMake:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

This will compile the project and place the executable in the `build/bin` directory.

## Dependencies

### OpenAL
- **OpenAL** is an open-source audio API designed for cross-platform audio functionality. It is used for spatial audio rendering in this project.
- Make sure OpenAL is correctly installed, and the required binaries (e.g., `OpenAL32.dll`) are located in `lib/OpenALlibs/`.

### PortAudio
- **PortAudio** is a cross-platform library for audio I/O. It supports multiple platforms and provides the necessary framework for integrating HRTF processing.
- Ensure the `portaudio_x64.dll` file is in the `lib/PortAudioLibs/bin/` directory.

To manage these dependencies, you can either download and place them manually in the `lib/` directory, or use a package manager like **vcpkg** or **conan** to automate the installation.

## Contributing

Contributions are welcome! To contribute:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature/YourFeature`).
3. Commit your changes (`git commit -m 'Add some feature'`).
4. Push to the branch (`git push origin feature/YourFeature`).
5. Open a Pull Request.

### Coding Guidelines

- Follow consistent naming conventions and code structure.
- Document all your functions and modules using comments.
- Ensure your code compiles without errors or warnings using CMake.

## License

This project is licensed under the **GNU General Public License (GPL) v3**. See the [LICENSE](LICENSE) file for more information.

## Contact

For any questions or suggestions, feel free to open an issue on the GitHub repository or contact the maintainer directly via the GitHub profile: [DynaPulse](https://github.com/DynaPulse).
