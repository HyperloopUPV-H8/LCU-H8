# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/build"

# Include any dependencies generated for this target.
include CMakeFiles/LCU_MASTER.elf.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/LCU_MASTER.elf.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/LCU_MASTER.elf.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LCU_MASTER.elf.dir/flags.make

CMakeFiles/LCU_MASTER.elf.dir/Core/Src/main.cpp.obj: CMakeFiles/LCU_MASTER.elf.dir/flags.make
CMakeFiles/LCU_MASTER.elf.dir/Core/Src/main.cpp.obj: ../Core/Src/main.cpp
CMakeFiles/LCU_MASTER.elf.dir/Core/Src/main.cpp.obj: CMakeFiles/LCU_MASTER.elf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LCU_MASTER.elf.dir/Core/Src/main.cpp.obj"
	/usr/local/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/LCU_MASTER.elf.dir/Core/Src/main.cpp.obj -MF CMakeFiles/LCU_MASTER.elf.dir/Core/Src/main.cpp.obj.d -o CMakeFiles/LCU_MASTER.elf.dir/Core/Src/main.cpp.obj -c "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/Core/Src/main.cpp"

CMakeFiles/LCU_MASTER.elf.dir/Core/Src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LCU_MASTER.elf.dir/Core/Src/main.cpp.i"
	/usr/local/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/Core/Src/main.cpp" > CMakeFiles/LCU_MASTER.elf.dir/Core/Src/main.cpp.i

CMakeFiles/LCU_MASTER.elf.dir/Core/Src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LCU_MASTER.elf.dir/Core/Src/main.cpp.s"
	/usr/local/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/Core/Src/main.cpp" -o CMakeFiles/LCU_MASTER.elf.dir/Core/Src/main.cpp.s

CMakeFiles/LCU_MASTER.elf.dir/Core/Src/syscalls.c.obj: CMakeFiles/LCU_MASTER.elf.dir/flags.make
CMakeFiles/LCU_MASTER.elf.dir/Core/Src/syscalls.c.obj: ../Core/Src/syscalls.c
CMakeFiles/LCU_MASTER.elf.dir/Core/Src/syscalls.c.obj: CMakeFiles/LCU_MASTER.elf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/LCU_MASTER.elf.dir/Core/Src/syscalls.c.obj"
	/usr/local/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/LCU_MASTER.elf.dir/Core/Src/syscalls.c.obj -MF CMakeFiles/LCU_MASTER.elf.dir/Core/Src/syscalls.c.obj.d -o CMakeFiles/LCU_MASTER.elf.dir/Core/Src/syscalls.c.obj -c "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/Core/Src/syscalls.c"

CMakeFiles/LCU_MASTER.elf.dir/Core/Src/syscalls.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LCU_MASTER.elf.dir/Core/Src/syscalls.c.i"
	/usr/local/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/Core/Src/syscalls.c" > CMakeFiles/LCU_MASTER.elf.dir/Core/Src/syscalls.c.i

CMakeFiles/LCU_MASTER.elf.dir/Core/Src/syscalls.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LCU_MASTER.elf.dir/Core/Src/syscalls.c.s"
	/usr/local/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/Core/Src/syscalls.c" -o CMakeFiles/LCU_MASTER.elf.dir/Core/Src/syscalls.c.s

CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_hal_msp.c.obj: CMakeFiles/LCU_MASTER.elf.dir/flags.make
CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_hal_msp.c.obj: ../Core/Src/stm32h7xx_hal_msp.c
CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_hal_msp.c.obj: CMakeFiles/LCU_MASTER.elf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_hal_msp.c.obj"
	/usr/local/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_hal_msp.c.obj -MF CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_hal_msp.c.obj.d -o CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_hal_msp.c.obj -c "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/Core/Src/stm32h7xx_hal_msp.c"

CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_hal_msp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_hal_msp.c.i"
	/usr/local/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/Core/Src/stm32h7xx_hal_msp.c" > CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_hal_msp.c.i

CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_hal_msp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_hal_msp.c.s"
	/usr/local/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/Core/Src/stm32h7xx_hal_msp.c" -o CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_hal_msp.c.s

CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_it.c.obj: CMakeFiles/LCU_MASTER.elf.dir/flags.make
CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_it.c.obj: ../Core/Src/stm32h7xx_it.c
CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_it.c.obj: CMakeFiles/LCU_MASTER.elf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_it.c.obj"
	/usr/local/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_it.c.obj -MF CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_it.c.obj.d -o CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_it.c.obj -c "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/Core/Src/stm32h7xx_it.c"

CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_it.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_it.c.i"
	/usr/local/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/Core/Src/stm32h7xx_it.c" > CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_it.c.i

CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_it.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_it.c.s"
	/usr/local/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/Core/Src/stm32h7xx_it.c" -o CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_it.c.s

CMakeFiles/LCU_MASTER.elf.dir/Core/Src/sysmem.c.obj: CMakeFiles/LCU_MASTER.elf.dir/flags.make
CMakeFiles/LCU_MASTER.elf.dir/Core/Src/sysmem.c.obj: ../Core/Src/sysmem.c
CMakeFiles/LCU_MASTER.elf.dir/Core/Src/sysmem.c.obj: CMakeFiles/LCU_MASTER.elf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/LCU_MASTER.elf.dir/Core/Src/sysmem.c.obj"
	/usr/local/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/LCU_MASTER.elf.dir/Core/Src/sysmem.c.obj -MF CMakeFiles/LCU_MASTER.elf.dir/Core/Src/sysmem.c.obj.d -o CMakeFiles/LCU_MASTER.elf.dir/Core/Src/sysmem.c.obj -c "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/Core/Src/sysmem.c"

CMakeFiles/LCU_MASTER.elf.dir/Core/Src/sysmem.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LCU_MASTER.elf.dir/Core/Src/sysmem.c.i"
	/usr/local/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/Core/Src/sysmem.c" > CMakeFiles/LCU_MASTER.elf.dir/Core/Src/sysmem.c.i

CMakeFiles/LCU_MASTER.elf.dir/Core/Src/sysmem.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LCU_MASTER.elf.dir/Core/Src/sysmem.c.s"
	/usr/local/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/Core/Src/sysmem.c" -o CMakeFiles/LCU_MASTER.elf.dir/Core/Src/sysmem.c.s

CMakeFiles/LCU_MASTER.elf.dir/Core/Src/system_stm32h7xx.c.obj: CMakeFiles/LCU_MASTER.elf.dir/flags.make
CMakeFiles/LCU_MASTER.elf.dir/Core/Src/system_stm32h7xx.c.obj: ../Core/Src/system_stm32h7xx.c
CMakeFiles/LCU_MASTER.elf.dir/Core/Src/system_stm32h7xx.c.obj: CMakeFiles/LCU_MASTER.elf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/LCU_MASTER.elf.dir/Core/Src/system_stm32h7xx.c.obj"
	/usr/local/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/LCU_MASTER.elf.dir/Core/Src/system_stm32h7xx.c.obj -MF CMakeFiles/LCU_MASTER.elf.dir/Core/Src/system_stm32h7xx.c.obj.d -o CMakeFiles/LCU_MASTER.elf.dir/Core/Src/system_stm32h7xx.c.obj -c "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/Core/Src/system_stm32h7xx.c"

CMakeFiles/LCU_MASTER.elf.dir/Core/Src/system_stm32h7xx.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LCU_MASTER.elf.dir/Core/Src/system_stm32h7xx.c.i"
	/usr/local/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/Core/Src/system_stm32h7xx.c" > CMakeFiles/LCU_MASTER.elf.dir/Core/Src/system_stm32h7xx.c.i

CMakeFiles/LCU_MASTER.elf.dir/Core/Src/system_stm32h7xx.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LCU_MASTER.elf.dir/Core/Src/system_stm32h7xx.c.s"
	/usr/local/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/Core/Src/system_stm32h7xx.c" -o CMakeFiles/LCU_MASTER.elf.dir/Core/Src/system_stm32h7xx.c.s

CMakeFiles/LCU_MASTER.elf.dir/Core/Startup/startup_stm32h723zgtx.s.obj: CMakeFiles/LCU_MASTER.elf.dir/flags.make
CMakeFiles/LCU_MASTER.elf.dir/Core/Startup/startup_stm32h723zgtx.s.obj: ../Core/Startup/startup_stm32h723zgtx.s
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building ASM object CMakeFiles/LCU_MASTER.elf.dir/Core/Startup/startup_stm32h723zgtx.s.obj"
	/usr/local/bin/arm-none-eabi-gcc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/LCU_MASTER.elf.dir/Core/Startup/startup_stm32h723zgtx.s.obj -c "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/Core/Startup/startup_stm32h723zgtx.s"

CMakeFiles/LCU_MASTER.elf.dir/Core/Startup/startup_stm32h723zgtx.s.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing ASM source to CMakeFiles/LCU_MASTER.elf.dir/Core/Startup/startup_stm32h723zgtx.s.i"
	/usr/local/bin/arm-none-eabi-gcc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -E "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/Core/Startup/startup_stm32h723zgtx.s" > CMakeFiles/LCU_MASTER.elf.dir/Core/Startup/startup_stm32h723zgtx.s.i

CMakeFiles/LCU_MASTER.elf.dir/Core/Startup/startup_stm32h723zgtx.s.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling ASM source to assembly CMakeFiles/LCU_MASTER.elf.dir/Core/Startup/startup_stm32h723zgtx.s.s"
	/usr/local/bin/arm-none-eabi-gcc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -S "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/Core/Startup/startup_stm32h723zgtx.s" -o CMakeFiles/LCU_MASTER.elf.dir/Core/Startup/startup_stm32h723zgtx.s.s

# Object files for target LCU_MASTER.elf
LCU_MASTER_elf_OBJECTS = \
"CMakeFiles/LCU_MASTER.elf.dir/Core/Src/main.cpp.obj" \
"CMakeFiles/LCU_MASTER.elf.dir/Core/Src/syscalls.c.obj" \
"CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_hal_msp.c.obj" \
"CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_it.c.obj" \
"CMakeFiles/LCU_MASTER.elf.dir/Core/Src/sysmem.c.obj" \
"CMakeFiles/LCU_MASTER.elf.dir/Core/Src/system_stm32h7xx.c.obj" \
"CMakeFiles/LCU_MASTER.elf.dir/Core/Startup/startup_stm32h723zgtx.s.obj"

# External object files for target LCU_MASTER.elf
LCU_MASTER_elf_EXTERNAL_OBJECTS =

LCU_MASTER.elf: CMakeFiles/LCU_MASTER.elf.dir/Core/Src/main.cpp.obj
LCU_MASTER.elf: CMakeFiles/LCU_MASTER.elf.dir/Core/Src/syscalls.c.obj
LCU_MASTER.elf: CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_hal_msp.c.obj
LCU_MASTER.elf: CMakeFiles/LCU_MASTER.elf.dir/Core/Src/stm32h7xx_it.c.obj
LCU_MASTER.elf: CMakeFiles/LCU_MASTER.elf.dir/Core/Src/sysmem.c.obj
LCU_MASTER.elf: CMakeFiles/LCU_MASTER.elf.dir/Core/Src/system_stm32h7xx.c.obj
LCU_MASTER.elf: CMakeFiles/LCU_MASTER.elf.dir/Core/Startup/startup_stm32h723zgtx.s.obj
LCU_MASTER.elf: CMakeFiles/LCU_MASTER.elf.dir/build.make
LCU_MASTER.elf: /opt/malva/ST-LIB/build/libst-lib.a
LCU_MASTER.elf: CMakeFiles/LCU_MASTER.elf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable LCU_MASTER.elf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LCU_MASTER.elf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LCU_MASTER.elf.dir/build: LCU_MASTER.elf
.PHONY : CMakeFiles/LCU_MASTER.elf.dir/build

CMakeFiles/LCU_MASTER.elf.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LCU_MASTER.elf.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LCU_MASTER.elf.dir/clean

CMakeFiles/LCU_MASTER.elf.dir/depend:
	cd "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER" "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER" "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/build" "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/build" "/home/stefancostea/Documents/LCU FINAL/LCU_MASTER/build/CMakeFiles/LCU_MASTER.elf.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/LCU_MASTER.elf.dir/depend

