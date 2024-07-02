@echo off
setlocal enabledelayedexpansion

rem Set include directory
set INCLUDE_DIR=include

rem Initialize the variable for source files
set SRC_FILES=

rem Loop through all .c files in the src directory and add them to the SRC_FILES variable
for %%f in (src\*.c) do (
    rem Append each .c file to SRC_FILES
    set SRC_FILES=!SRC_FILES! %%f
)

rem Set additional dependencies (e.g., libraries, object files)
set DEPS=

rem Add libraries to DEPS
set DEPS=!DEPS! -lopengl32
set DEPS=!DEPS! -lglu32
set DEPS=!DEPS! -lfreeglut

rem Compile source files with additional dependencies
gcc -I%INCLUDE_DIR% !SRC_FILES! !DEPS! -o program

rem Print a message indicating the build is complete
echo Build complete.

rem Disable delayed expansion
endlocal
