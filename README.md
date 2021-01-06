![xP](https://socialify.git.ci/theProgrammerDavid/xP/image?description=1&font=Bitter&language=1&owner=1&stargazers=1&theme=Dark)

# xP
C++ native app to test HTTP endpoints
### Dependencies
- CMake
- OpenGL (with supporting drivers)
- CMake supported C++ Compiler
- Debian and Ubuntu systems might need some additional dependencies as given below: 
```bash
sudo apt-get install libx11-dev xorg-dev libglu1-mesa-dev 
```

You also need the dev libraries for `OpenSSL` installed
```bash
sudo apt-get install libssl-dev

```

* Windows systems need the Visual Studio environment setup with the necessary files for C++ development. If required, you need to run 
```powershell
vcvarsall.bat x64
```

### Get Started
- This project contains submodules, so clone recursively
```bash
git clone --recurse-submodules https://github.com/theProgrammerDavid/xP.git
```

- Or if you have it cloned without initialising submodules, you can 
```bash
git submodule init
git submodule update
```

### Building

- Create a ``build`` folder and `cd` into that, and run ``cmake ..``
- Configuring CMake might take a while initially as it is downloading dependencies


### Credits
* [ImGui](https://github.com/ocornut/imgui)
* [Glew Cmake](https://github.com/Perlmint/glew-cmake.git)
* [GLFW](https://github.com/glfw/glfw.git)