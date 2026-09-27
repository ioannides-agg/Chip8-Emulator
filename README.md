# Chip8 Emulator
a chip8 emulator implemented using c++.

The repo contains two programs:

- **Interpreter**: the emulator itself, using [SDL3](https://www.libsdl.org/) for the window, input and sound. It implements all 35 original CHIP-8 instructions.
- **Disassembler**: prints a ROM as CHIP-8 assembly.

## Requirements

- [CMake](https://cmake.org/download/) 3.30 or newer
- A C++20 compiler (Clang, GCC or MSVC)
- Git

SDL3 is included as a git submodule in `Vendored/SDL`. It's built from source and linked statically with the project, so you don't need to install it separately.

Installing the tools on each platform:

- **macOS:** run `xcode-select --install`, then `brew install cmake`.
- **Linux (Debian/Ubuntu):** run `sudo apt install build-essential cmake git`. You also need the video and audio development packages that SDL uses, which are listed in [SDL's Linux guide](https://github.com/libsdl-org/SDL/blob/main/docs/README-linux.md). Some distros ship a CMake older than 3.30 (Ubuntu 24.04, for example), so get a newer one from [cmake.org](https://cmake.org/download/) if you need to.
- **Windows:** install Visual Studio 2022 or newer with the *Desktop development with C++* workload, plus [CMake](https://cmake.org/download/) and [Git](https://git-scm.com/download/win).

## Getting the source

Clone the repo together with its SDL submodule:

```bash
git clone --recurse-submodules https://github.com/ioannides-agg/Chip8-Emulator.git
cd Chip8-Emulator
```

If you've already cloned it without `--recurse-submodules`, download SDL with:

```bash
git submodule update --init
```

## Building

Run these from the repo root:

```bash
cmake -S . -B build
cmake --build build --parallel
```

The first build is slower because SDL3 is compiled too. After that, only the files you change are rebuilt.

The executables end up in:

- `build/Interpreter/Interpreter`
- `build/Disassembler/Disassembler`

Visual Studio and Xcode put them in a folder named after the build configuration instead, for example `build\Interpreter\Debug\Interpreter.exe`.

## Running

Both programs read the path of a ROM from standard input. The path is relative to the folder you run the program from. Two test ROMs are included in `roms/`.

### Disassembler

```bash
echo roms/ibm.ch8 | ./build/Disassembler/Disassembler
```

Each line shows the address, the two bytes of the opcode and the decoded instruction:

```
200 00 e0 CLS
202 a2 2a LD I,#$22a
204 60 0c LD V0,#$0c
206 61 08 LD V1,#$08
208 d0 1f DRW V0,V1,f
```

### Interpreter

```bash
./build/Interpreter/Interpreter
```

When it prints `Select rom:`, type the path to a ROM (for example `roms/ibm.ch8`) and press Enter. The game opens in a new window.

The CHIP-8 has a 16-key hex keypad, which is mapped to the left side of your keyboard:

```
Keyboard        CHIP-8
1 2 3 4         1 2 3 C
Q W E R         4 5 6 D
A S D F         7 8 9 E
Z X C V         A 0 B F
```

Press Escape or close the window to quit.
