# Dying Light Trainer
## Timeline
- Project Started:     2021/12/13
- Converted to C++:    2021/12/14
- Converted back to C: 2021/12/16

## Overview
**[ UNFINISHED ]**

## Table of Contents
- [What I Learned](#what-i-learned)
- [How It Works](#how-it-works)
- [Build Instructions](#build-instructions)
- [Known Issues](#known-issues)
- [Goals](#Goals)

## What I Learned
 [ TODO ]

## How It Works
Use any DLL injector that you are comfortable with to inject the daylight-savings.dll into  
the <code>DyingLightGame.exe</code> process. 

Once the DLL is injected, you will have access to the following Hacks:
- [x] F1: God Mode
- [x] F2: One shot kill
- [x] F3: Infinite Stamina
- [ ] F4: Noclip
- [ ] F5: Flash (5x Speed)

## Build Instructions
### Debian
#### Toolchain
```bash
# Install toolchain for the required compiler
chmod +x ./install-toolchain.sh
sudo ./install-toolchain.sh # Modify it as you please before executing
```
#### Build
```bash
make -j$(nproc) # defaults to both release and debug builds
```

### Windows
#### Build
```powershell
# Requires C++ Desktop package for visual studio
cmake.exe -B win-build
cmake.exe --build win-build
```

## Known Issues
[ None at the moment ]
