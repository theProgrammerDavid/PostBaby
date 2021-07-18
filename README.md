![PostBaby](https://socialify.git.ci/theProgrammerDavid/PostBaby/image?description=1&font=Bitter&language=1&owner=1&stargazers=1&theme=Dark)

![PostBaby master cicd status ](https://github.com/theProgrammerDavid/PostBaby/actions/workflows/build.yml/badge.svg?branch=master) ![GitHub](https://img.shields.io/github/license/theProgrammerDavid/PostBaby)
# PostBaby 

C++ native app to test HTTP endpoints
### Dependencies
- CMake
- OpenGL (with supporting drivers)
- CMake supported C++ Compiler
- Python 3 (to generate GL bindings)

#### Debian/Ubuntu 
You also need the dev libraries for `OpenSSL` installed. 
```bash
sudo apt-get install libx11-dev xorg-dev libglu1-mesa-dev libssl-dev
```
#### Windows
> Note: As of now, HTTPS does not work (as mentioned in [this issue](https://github.com/whoshuu/cpr/issues/520)) on windows with WINSSL
* Windows systems need the Visual Studio environment setup with the necessary files for C++ development. If required, you need to run 
```powershell
vcvarsall.bat x64
```

Windows has been configured to use `WINSSL`

### Get Started

```bash
git clone https://github.com/theProgrammerDavid/PostBaby.git
```

### Building

- Create a ``build`` folder and `cd` into that, and run ``cmake -DCMAKE_BUILD_TYPE=Release ..`` for a Release build with the build system of choice.
- Configuring CMake might take a while initially as it is downloading dependencies
- Once configured, build it using the selected build system. On *nix systems you can use ``
make -j$(nproc)
``
- The built binary will be in `${PostBaby_ROOT}/build/src/PostBaby`
### Installing
- Quick Install MacOS
```bash
git clone https://github.com/theProgrammerDavid/PostBaby.git && \
cd PostBaby && \
mkdir build && \
cd build && \
export PATH="/usr/local/opt/openssl/bin:$PATH" && \
CXX=clang++ CC=clang cmake -DOPENSSL_ROOT_DIR=/usr/local/opt/openssl -DOPENSSL_LIBRARIES=/usr/local/opt/openssl/lib -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
```
- Quick Install Linux
```bash
git clone https://github.com/theProgrammerDavid/PostBaby.git && \
cd PostBaby && \
mkdir build && \
cd build && \
cmake -DCMAKE_BUILD_TYPE=Release .. && \
make -j$(nproc) && \
sudo make install
```
> ``sudo make install`` will add it to your system and application launcher
> You can also use ``cpack -C Release`` to build the package for your OS (`.deb` for Debian derivatives)

- Quick Install Windows
> Initialize your cmd with `vcvarsall.bat x64`
```cmd
git clone https://github.com/theProgrammerDavid/PostBaby.git && \
cd PostBaby && \
mkdir build && \
cd build && \
cmake .. && \
MSBuild.exe /p:Configuration=Release PostBaby.sln
cpack -C Release
```
- `MSBuild.exe PostBaby.sln` takes additional arguments like `/m:12` where `12` is the number of threads available

### Config Files

On Windows, the config files are stored in `%APPDATA%\PostBaby`
On Linux, the config files are stored in `$HOME/.config/PostBaby`

### Libraries used
| Library         | URL                              |
|-----------------|----------------------------------|
| ImGui           | https://github.com/ocornut/imgui |
| Glew            | https://glew.sourceforge.net     |
| GLFW            | https://github.com/glfw/glfw     |
| Curl For People | https://github.com/whoshuu/cpr   |
| Glad            | https://github.com/Dav1dde/glad.git|
| tidy-html5      | https://github.com/htacg/tidy-html5 |
| Nlohmann JSON   | https://github.com/nlohmann/json |

### Resources

- [CPack with CMake](https://gitlab.kitware.com/cmake/community/-/wikis/doc/cpack/Packaging-With-CPack)
- [CMake CPack](https://embeddeduse.com/2020/03/21/creating-simple-installers-with-cpack/)
- [CMake tutorial](https://foonathan.net/2016/07/cmake-dependency-handling/)
- [CMake NSIS](https://martinrotter.github.io/it-programming/2014/05/09/integrating-nsis-cmake/)
- [Absolute Path CPack error fix](https://cmake.org/pipermail/cmake/2013-May/054656.html)
- [CPack Start Menu Link](https://crascit.com/2015/08/07/cmake_cpack_nsis_shortcuts_with_parameters/)
- [CPack NSIS](https://cmake.org/cmake/help/latest/cpack_gen/nsis.html)
