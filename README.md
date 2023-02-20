# Maze project

## Background Context
The goal of this project is to create a game in 3D using raycasting with the C programming language using SDL2.

## Installation

### Ubuntu/Debian
Ensure you have both gcc and make installed on your system. Once done, install SDL2 and SDL2_gfx from your distro's package manager.

Installing gcc and make with the build-essential metapackage:

    sudo apt install build-essential

Installing SDL2 and SDL2_gfx:

    sudo apt install libsdl2-2.0-0 libsdl2-dev libsdl2-gfx-1.0-0 libsdl2-gfx-dev

### Install support for Linux GUI apps

You will need to be on Windows 10 Build 19044+ or Windows 11 to access this feature.

* Installed driver for vGPU

To run Linux GUI apps, you should first install the driver matching your system below. This will enable you to use a virtual GPU (vGPU) so you can benefit from hardware accelerated OpenGL rendering.

  [Intel GPU driver for WSL](https://www.intel.com/content/www/us/en/download/19344/intel-graphics-windows-dch-drivers.html)

  [AMD GPU driver for WSL](https://www.amd.com/en/support/kb/release-notes/rn-rad-win-wsl-support)

  [NVIDIA GPU driver for WSL](https://developer.nvidia.com/cuda/wsl)

  Windows Subsystem for Linux (WSL) now supports running Linux GUI applications (X11 and Wayland) on Windows in a fully integrated desktop experience.

WSL 2 enables Linux GUI applications to feel native and natural to use on Windows.

* Launch Linux apps from the Windows Start menu
* Pin Linux apps to the Windows task bar
* Use alt-tab to switch between Linux and Windows apps
* Cut + Paste across Windows and Linux apps
* You can now integrate both Windows and Linux applications into your workflow for a seamless desktop experience.

## Setup

- Make sure that SDL2 libraries are installed on your computer
- Clone this repository

      git clone https://github.com/Vozudo/Maze-Project.git

- Compile it with:
     * make : Compile your sources
     * make clean : Remove all the object files (".o")
     * make fclean : Remove all the object files + the executable file
     * make re : Recompile everything (even the unmodified files)

- Launch the project with

      ./maze

## How to use

This Raycaster uses the following inputs:

- `Up` Move forward
- `Down` Move backward
- `Left` Turn left
- `Right` Turn right

## Team Members:

* Juan Pablo Lopera
* Jesus Macias
* Santiago Arias

## Support Link:
 - [Installing SDL](https://wiki.libsdl.org/SDL2/Installation)
 - [Raycasting](https://lodev.org/cgtutor/raycasting.html)
 - [Lesson 01 - Setup & Windowing](https://thenumb.at/cpp-course/sdl2/01/01.html)
 - [Beginning Game Programming v2.0 SDL](http://lazyfoo.net/tutorials/SDL/index.php)
 - [Functions provided by SDL2](https://wiki.libsdl.org/SDL2/CategoryAPI)
 - [Run Linux GUI apps on the Windows Subsystem for Linux](https://wiki.libsdl.org/SDL2/CategoryAPI](https://learn.microsoft.com/en-us/windows/wsl/tutorials/gui-apps))
