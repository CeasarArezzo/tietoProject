# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ceasar/tieto

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ceasar/tieto

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/ceasar/tieto/CMakeFiles /home/ceasar/tieto/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/ceasar/tieto/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -P /home/ceasar/tieto/CMakeFiles/VerifyGlobs.cmake
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named main

# Build rule for target.
main: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 main
.PHONY : main

# fast build rule for target.
main/fast:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/build
.PHONY : main/fast

src/analyzer.o: src/analyzer.c.o

.PHONY : src/analyzer.o

# target to build an object file
src/analyzer.c.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/analyzer.c.o
.PHONY : src/analyzer.c.o

src/analyzer.i: src/analyzer.c.i

.PHONY : src/analyzer.i

# target to preprocess a source file
src/analyzer.c.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/analyzer.c.i
.PHONY : src/analyzer.c.i

src/analyzer.s: src/analyzer.c.s

.PHONY : src/analyzer.s

# target to generate assembly for a file
src/analyzer.c.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/analyzer.c.s
.PHONY : src/analyzer.c.s

src/circular_buffer.o: src/circular_buffer.c.o

.PHONY : src/circular_buffer.o

# target to build an object file
src/circular_buffer.c.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/circular_buffer.c.o
.PHONY : src/circular_buffer.c.o

src/circular_buffer.i: src/circular_buffer.c.i

.PHONY : src/circular_buffer.i

# target to preprocess a source file
src/circular_buffer.c.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/circular_buffer.c.i
.PHONY : src/circular_buffer.c.i

src/circular_buffer.s: src/circular_buffer.c.s

.PHONY : src/circular_buffer.s

# target to generate assembly for a file
src/circular_buffer.c.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/circular_buffer.c.s
.PHONY : src/circular_buffer.c.s

src/lifetime_struct.o: src/lifetime_struct.c.o

.PHONY : src/lifetime_struct.o

# target to build an object file
src/lifetime_struct.c.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/lifetime_struct.c.o
.PHONY : src/lifetime_struct.c.o

src/lifetime_struct.i: src/lifetime_struct.c.i

.PHONY : src/lifetime_struct.i

# target to preprocess a source file
src/lifetime_struct.c.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/lifetime_struct.c.i
.PHONY : src/lifetime_struct.c.i

src/lifetime_struct.s: src/lifetime_struct.c.s

.PHONY : src/lifetime_struct.s

# target to generate assembly for a file
src/lifetime_struct.c.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/lifetime_struct.c.s
.PHONY : src/lifetime_struct.c.s

src/main.o: src/main.c.o

.PHONY : src/main.o

# target to build an object file
src/main.c.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/main.c.o
.PHONY : src/main.c.o

src/main.i: src/main.c.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.c.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/main.c.i
.PHONY : src/main.c.i

src/main.s: src/main.c.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.c.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/main.c.s
.PHONY : src/main.c.s

src/reader.o: src/reader.c.o

.PHONY : src/reader.o

# target to build an object file
src/reader.c.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/reader.c.o
.PHONY : src/reader.c.o

src/reader.i: src/reader.c.i

.PHONY : src/reader.i

# target to preprocess a source file
src/reader.c.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/reader.c.i
.PHONY : src/reader.c.i

src/reader.s: src/reader.c.s

.PHONY : src/reader.s

# target to generate assembly for a file
src/reader.c.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/reader.c.s
.PHONY : src/reader.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... main"
	@echo "... src/analyzer.o"
	@echo "... src/analyzer.i"
	@echo "... src/analyzer.s"
	@echo "... src/circular_buffer.o"
	@echo "... src/circular_buffer.i"
	@echo "... src/circular_buffer.s"
	@echo "... src/lifetime_struct.o"
	@echo "... src/lifetime_struct.i"
	@echo "... src/lifetime_struct.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/reader.o"
	@echo "... src/reader.i"
	@echo "... src/reader.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -P /home/ceasar/tieto/CMakeFiles/VerifyGlobs.cmake
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

