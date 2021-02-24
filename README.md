![xP](https://socialify.git.ci/theProgrammerDavid/xP/image?description=1&font=Bitter&language=1&owner=1&stargazers=1&theme=Dark)

# xP
C++ native app to test HTTP endpoints
### Dependencies
- CMake
- OpenGL (with supporting drivers)
- CMake supported C++ Compiler

#### Debian/Ubuntu 
You also need the dev libraries for `OpenSSL` installed. 
```bash
sudo apt-get install libx11-dev xorg-dev libglu1-mesa-dev libssl-dev
```
#### Windows
> Note: As of now, HTTPS does [not work](https://github.com/whoshuu/cpr/issues/509) on windows with WINSSL, so HTTP can be used
* Windows systems need the Visual Studio environment setup with the necessary files for C++ development. If required, you need to run 
```powershell
vcvarsall.bat x64
```

Windows has been configured to use `WINSSL`

### Get Started

```bash
git clone https://github.com/theProgrammerDavid/xP.git
```

### Building

- Create a ``build`` folder and `cd` into that, and run ``cmake -DCMAKE_BUILD_TYPE=Release ..`` for a Release build with the build system of choice.
- Configuring CMake might take a while initially as it is downloading dependencies
- Once configured, build it using the selected build system
- The built binary will be in `${XP_ROOT}/build/src/xP`
### Installing

- On unix systems, you can use ``sudo make install`` to add it to your application launcher

### Libraries used
| Library         | URL                              |
|-----------------|----------------------------------|
| ImGui           | https://github.com/ocornut/imgui |
| Glew            | https://glew.sourceforge.net     |
| GLFW            | https://github.com/glfw/glfw     |
| Curl For People | https://whoshuu/cpr              |
| Glad            | https://github.com/Dav1dde/glad.git|