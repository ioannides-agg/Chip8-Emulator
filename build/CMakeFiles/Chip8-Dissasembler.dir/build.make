# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/aggelosioannidhs/Desktop/Work/Personal/Emulators/Chip-8/Dissasembler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/aggelosioannidhs/Desktop/Work/Personal/Emulators/Chip-8/build

# Include any dependencies generated for this target.
include CMakeFiles/Chip8-Dissasembler.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Chip8-Dissasembler.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Chip8-Dissasembler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Chip8-Dissasembler.dir/flags.make

CMakeFiles/Chip8-Dissasembler.dir/Chip8_Disassembler.cpp.o: CMakeFiles/Chip8-Dissasembler.dir/flags.make
CMakeFiles/Chip8-Dissasembler.dir/Chip8_Disassembler.cpp.o: /Users/aggelosioannidhs/Desktop/Work/Personal/Emulators/Chip-8/Dissasembler/Chip8_Disassembler.cpp
CMakeFiles/Chip8-Dissasembler.dir/Chip8_Disassembler.cpp.o: CMakeFiles/Chip8-Dissasembler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/aggelosioannidhs/Desktop/Work/Personal/Emulators/Chip-8/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Chip8-Dissasembler.dir/Chip8_Disassembler.cpp.o"
	/opt/homebrew/bin/aarch64-apple-darwin24-g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Chip8-Dissasembler.dir/Chip8_Disassembler.cpp.o -MF CMakeFiles/Chip8-Dissasembler.dir/Chip8_Disassembler.cpp.o.d -o CMakeFiles/Chip8-Dissasembler.dir/Chip8_Disassembler.cpp.o -c /Users/aggelosioannidhs/Desktop/Work/Personal/Emulators/Chip-8/Dissasembler/Chip8_Disassembler.cpp

CMakeFiles/Chip8-Dissasembler.dir/Chip8_Disassembler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Chip8-Dissasembler.dir/Chip8_Disassembler.cpp.i"
	/opt/homebrew/bin/aarch64-apple-darwin24-g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/aggelosioannidhs/Desktop/Work/Personal/Emulators/Chip-8/Dissasembler/Chip8_Disassembler.cpp > CMakeFiles/Chip8-Dissasembler.dir/Chip8_Disassembler.cpp.i

CMakeFiles/Chip8-Dissasembler.dir/Chip8_Disassembler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Chip8-Dissasembler.dir/Chip8_Disassembler.cpp.s"
	/opt/homebrew/bin/aarch64-apple-darwin24-g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/aggelosioannidhs/Desktop/Work/Personal/Emulators/Chip-8/Dissasembler/Chip8_Disassembler.cpp -o CMakeFiles/Chip8-Dissasembler.dir/Chip8_Disassembler.cpp.s

# Object files for target Chip8-Dissasembler
Chip8__Dissasembler_OBJECTS = \
"CMakeFiles/Chip8-Dissasembler.dir/Chip8_Disassembler.cpp.o"

# External object files for target Chip8-Dissasembler
Chip8__Dissasembler_EXTERNAL_OBJECTS =

Chip8-Dissasembler: CMakeFiles/Chip8-Dissasembler.dir/Chip8_Disassembler.cpp.o
Chip8-Dissasembler: CMakeFiles/Chip8-Dissasembler.dir/build.make
Chip8-Dissasembler: CMakeFiles/Chip8-Dissasembler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/aggelosioannidhs/Desktop/Work/Personal/Emulators/Chip-8/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Chip8-Dissasembler"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Chip8-Dissasembler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Chip8-Dissasembler.dir/build: Chip8-Dissasembler
.PHONY : CMakeFiles/Chip8-Dissasembler.dir/build

CMakeFiles/Chip8-Dissasembler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Chip8-Dissasembler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Chip8-Dissasembler.dir/clean

CMakeFiles/Chip8-Dissasembler.dir/depend:
	cd /Users/aggelosioannidhs/Desktop/Work/Personal/Emulators/Chip-8/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/aggelosioannidhs/Desktop/Work/Personal/Emulators/Chip-8/Dissasembler /Users/aggelosioannidhs/Desktop/Work/Personal/Emulators/Chip-8/Dissasembler /Users/aggelosioannidhs/Desktop/Work/Personal/Emulators/Chip-8/build /Users/aggelosioannidhs/Desktop/Work/Personal/Emulators/Chip-8/build /Users/aggelosioannidhs/Desktop/Work/Personal/Emulators/Chip-8/build/CMakeFiles/Chip8-Dissasembler.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Chip8-Dissasembler.dir/depend

