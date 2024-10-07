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
echo Creating build directory...
mkdir "%CURRENT_DIR%build"
if ERRORLEVEL 1 (
    echo Failed to create build directory. Exiting...
    exit /b 1
)

REM Step 4: Change to the build directory
echo Changing to build directory...
cd "%CURRENT_DIR%build"
if ERRORLEVEL 1 (
    echo Failed to change to build directory. Exiting...
    exit /b 1
)

REM Step 5: Run cmake to configure the project
echo Running cmake...
cmake ..
if ERRORLEVEL 1 (
    echo cmake configuration failed. Exiting...
    exit /b 1
)

REM Step 6: Build the project
echo Building the project...
cmake --build . --config Release
if ERRORLEVEL 1 (
    echo Build failed. Exiting...
    exit /b 1
)

REM Step 7: Create a new install directory
echo Creating install directory...
mkdir "%CURRENT_DIR%install_app"
if ERRORLEVEL 1 (
    echo Failed to create install directory. Exiting...
    exit /b 1
)

REM Step 8: Install the project
echo Installing the project...
cmake --install . --prefix "%CURRENT_DIR%install_app"
if ERRORLEVEL 1 (
    echo Installation failed. Exiting...
    exit /b 1
)

REM Step 9: Copy portaudio_x64.dll to the install directory
echo Copying portaudio_x64.dll...
copy "%CURRENT_DIR%lib\PortAudioLibs\bin\portaudio_x64.dll" "%CURRENT_DIR%install_app\bin\"
if ERRORLEVEL 1 (
    echo Failed to copy portaudio_x64.dll. Exiting...
    exit /b 1
)

REM Step 10: Launch SurroundVirtualizer.exe
echo Launching SurroundVirtualizer.exe...
start "" "%CURRENT_DIR%install_app\bin\SurroundVirtualizer.exe"
if ERRORLEVEL 1 (
    echo Failed to launch SurroundVirtualizer.exe. Exiting...
    exit /b 1
)

echo All steps completed successfully.
endlocal
exit /b 0
