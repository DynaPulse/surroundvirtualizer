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

REM Step 5: Run cmake to configure the project
if exist "CMakeCache.txt" del /f /q CMakeCache.txt
if exist "CMakeFiles" rmdir /s /q CMakeFiles

REM Prefer Ninja if available
where ninja >nul 2>nul
if %ERRORLEVEL%==0 (
    echo Ninja detected, using Ninja generator...
    cmake -G "Ninja" ..
) else (
    echo Running cmake with default generator...
    cmake ..
)
if ERRORLEVEL 1 (
    echo cmake configuration failed. Exiting...
    exit /b 1
)

REM Step 6: Build the project
cmake --build . --config Release
if ERRORLEVEL 1 (
    echo Build failed. Exiting...
    exit /b 1
)

REM Step 7: Create a new install directory
if not exist "%CURRENT_DIR%install_app" (
    echo Creating install directory...
    mkdir "%CURRENT_DIR%install_app"
    if ERRORLEVEL 1 (
        echo Failed to create install directory. Exiting...
        exit /b 1
    )
)

REM Step 8: Install the project
cmake --install . --prefix "%CURRENT_DIR%install_app"
if ERRORLEVEL 1 (
    echo Installation failed. Exiting...
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
