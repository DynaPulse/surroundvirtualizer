@echo off
setlocal

REM Get the current directory of the script
set "CURRENT_DIR=%~dp0"

REM Step 1: Remove the build directory if it exists
if exist "%CURRENT_DIR%build" (
    echo Removing build directory...
    rmdir /s /q "%CURRENT_DIR%build"
    if ERRORLEVEL 1 (
        echo Failed to remove build directory. Exiting...
        exit /b 1
    )
) else (
    echo Build directory not found. Skipping removal.
)

REM Step 2: Remove the install directory if it exists
if exist "%CURRENT_DIR%install_app" (
    echo Removing install_app directory...
    rmdir /s /q "%CURRENT_DIR%install_app"
    if ERRORLEVEL 1 (
        echo Failed to remove install_app directory. Exiting...
        exit /b 1
    )
) else (
    echo Install directory not found. Skipping removal.
)

REM Step 3: Create a new build directory
if not exist "%CURRENT_DIR%build" (
    echo Creating build directory...
    mkdir "%CURRENT_DIR%build"
    if ERRORLEVEL 1 (
        echo Failed to create build directory. Exiting...
        exit /b 1
    )
)

REM Step 4: Change to the build directory
cd "%CURRENT_DIR%build"
if ERRORLEVEL 1 (
    echo Failed to change to build directory. Exiting...
    exit /b 1
)

REM Step 5: Compile all source files with gcc and gcc directly
cd "%CURRENT_DIR%/src"
if ERRORLEVEL 1 (
    echo Failed to change to src directory. Exiting...
    exit /b 1
)

REM Compile all .cpp files into object files
for %%f in (*.cpp) do g++ -c "%%f" -I"%CURRENT_DIR%include/headers" -I"%CURRENT_DIR%lib/PortAudioLibs/include" -I"%CURRENT_DIR%lib/OpenALlibs/include" -o "%%~nf.o"
if ERRORLEVEL 1 (
    echo Compilation failed. Exiting...
    exit /b 1
)

cd "%CURRENT_DIR%/app"
g++ -c main.cpp -I"%CURRENT_DIR%include/headers" -I"%CURRENT_DIR%lib/PortAudioLibs/include" -I"%CURRENT_DIR%lib/OpenALlibs/include" -o main.o
if ERRORLEVEL 1 (
    echo Compilation of main.cpp failed. Exiting...
    exit /b 1
)

cd "%CURRENT_DIR%/src"
move *.o "%CURRENT_DIR%/build/"
cd "%CURRENT_DIR%/app"
move main.o "%CURRENT_DIR%/build/"
cd "%CURRENT_DIR%/build"

REM Link all object files into the final executable

g++ main.o openal_setup.o portaudio_setup.o hrtf_processor.o cli_interface.o -o SurroundVirtualizer -L"%CURRENT_DIR%lib/PortAudioLibs/lib" -L"%CURRENT_DIR%lib/OpenALlibs/lib" -lportaudio_x64 -lOpenAL32
if ERRORLEVEL 1 (
    echo Linking failed. Exiting...
    exit /b 1
)

REM Step 7: Create a new install directory
if not exist "%CURRENT_DIR%install_app\bin" (
    echo Creating install_app/bin directory...
    mkdir "%CURRENT_DIR%install_app\bin"
    if ERRORLEVEL 1 (
        echo Failed to create install_app/bin directory. Exiting...
        exit /b 1
    )
)

REM Step 8: Copy the executable to the install directory
copy SurroundVirtualizer.exe "%CURRENT_DIR%install_app\bin\" /Y
if ERRORLEVEL 1 (
    echo Failed to copy SurroundVirtualizer.exe. Exiting...
    exit /b 1
)

REM Step 9: Copy DLLs to the install directory
if exist "%CURRENT_DIR%lib\PortAudioLibs\bin\portaudio_x64.dll" copy "%CURRENT_DIR%lib\PortAudioLibs\bin\portaudio_x64.dll" "%CURRENT_DIR%install_app\bin\" /Y
if exist "%CURRENT_DIR%lib\OpenALlibs\bin\OpenAL32.dll" copy "%CURRENT_DIR%lib\OpenALlibs\bin\OpenAL32.dll" "%CURRENT_DIR%install_app\bin\" /Y

REM Step 10: Launch SurroundVirtualizer.exe
if exist "%CURRENT_DIR%install_app\bin\SurroundVirtualizer.exe" (
    echo Launching SurroundVirtualizer.exe...
    start "" "%CURRENT_DIR%install_app\bin\SurroundVirtualizer.exe"
) else (
    echo SurroundVirtualizer.exe not found in install_app/bin. Exiting...
    exit /b 1
)

echo All steps completed successfully.
endlocal
exit /b 0
