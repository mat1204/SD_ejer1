# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/build

# Include any dependencies generated for this target.
include CMakeFiles/plataforma.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/plataforma.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/plataforma.dir/flags.make

CMakeFiles/plataforma.dir/mainPlataforma.o: CMakeFiles/plataforma.dir/flags.make
CMakeFiles/plataforma.dir/mainPlataforma.o: ../mainPlataforma.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/plataforma.dir/mainPlataforma.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/plataforma.dir/mainPlataforma.o -c /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/mainPlataforma.cpp

CMakeFiles/plataforma.dir/mainPlataforma.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/plataforma.dir/mainPlataforma.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/mainPlataforma.cpp > CMakeFiles/plataforma.dir/mainPlataforma.i

CMakeFiles/plataforma.dir/mainPlataforma.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/plataforma.dir/mainPlataforma.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/mainPlataforma.cpp -o CMakeFiles/plataforma.dir/mainPlataforma.s

CMakeFiles/plataforma.dir/mainPlataforma.o.requires:
.PHONY : CMakeFiles/plataforma.dir/mainPlataforma.o.requires

CMakeFiles/plataforma.dir/mainPlataforma.o.provides: CMakeFiles/plataforma.dir/mainPlataforma.o.requires
	$(MAKE) -f CMakeFiles/plataforma.dir/build.make CMakeFiles/plataforma.dir/mainPlataforma.o.provides.build
.PHONY : CMakeFiles/plataforma.dir/mainPlataforma.o.provides

CMakeFiles/plataforma.dir/mainPlataforma.o.provides.build: CMakeFiles/plataforma.dir/mainPlataforma.o

CMakeFiles/plataforma.dir/PlataformaVirtual.o: CMakeFiles/plataforma.dir/flags.make
CMakeFiles/plataforma.dir/PlataformaVirtual.o: ../PlataformaVirtual.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/plataforma.dir/PlataformaVirtual.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/plataforma.dir/PlataformaVirtual.o -c /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/PlataformaVirtual.cpp

CMakeFiles/plataforma.dir/PlataformaVirtual.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/plataforma.dir/PlataformaVirtual.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/PlataformaVirtual.cpp > CMakeFiles/plataforma.dir/PlataformaVirtual.i

CMakeFiles/plataforma.dir/PlataformaVirtual.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/plataforma.dir/PlataformaVirtual.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/PlataformaVirtual.cpp -o CMakeFiles/plataforma.dir/PlataformaVirtual.s

CMakeFiles/plataforma.dir/PlataformaVirtual.o.requires:
.PHONY : CMakeFiles/plataforma.dir/PlataformaVirtual.o.requires

CMakeFiles/plataforma.dir/PlataformaVirtual.o.provides: CMakeFiles/plataforma.dir/PlataformaVirtual.o.requires
	$(MAKE) -f CMakeFiles/plataforma.dir/build.make CMakeFiles/plataforma.dir/PlataformaVirtual.o.provides.build
.PHONY : CMakeFiles/plataforma.dir/PlataformaVirtual.o.provides

CMakeFiles/plataforma.dir/PlataformaVirtual.o.provides.build: CMakeFiles/plataforma.dir/PlataformaVirtual.o

CMakeFiles/plataforma.dir/SemRobots.o: CMakeFiles/plataforma.dir/flags.make
CMakeFiles/plataforma.dir/SemRobots.o: ../SemRobots.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/plataforma.dir/SemRobots.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/plataforma.dir/SemRobots.o -c /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/SemRobots.cpp

CMakeFiles/plataforma.dir/SemRobots.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/plataforma.dir/SemRobots.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/SemRobots.cpp > CMakeFiles/plataforma.dir/SemRobots.i

CMakeFiles/plataforma.dir/SemRobots.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/plataforma.dir/SemRobots.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/SemRobots.cpp -o CMakeFiles/plataforma.dir/SemRobots.s

CMakeFiles/plataforma.dir/SemRobots.o.requires:
.PHONY : CMakeFiles/plataforma.dir/SemRobots.o.requires

CMakeFiles/plataforma.dir/SemRobots.o.provides: CMakeFiles/plataforma.dir/SemRobots.o.requires
	$(MAKE) -f CMakeFiles/plataforma.dir/build.make CMakeFiles/plataforma.dir/SemRobots.o.provides.build
.PHONY : CMakeFiles/plataforma.dir/SemRobots.o.provides

CMakeFiles/plataforma.dir/SemRobots.o.provides.build: CMakeFiles/plataforma.dir/SemRobots.o

CMakeFiles/plataforma.dir/ColaMensajes.o: CMakeFiles/plataforma.dir/flags.make
CMakeFiles/plataforma.dir/ColaMensajes.o: ../ColaMensajes.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/plataforma.dir/ColaMensajes.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/plataforma.dir/ColaMensajes.o -c /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/ColaMensajes.cpp

CMakeFiles/plataforma.dir/ColaMensajes.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/plataforma.dir/ColaMensajes.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/ColaMensajes.cpp > CMakeFiles/plataforma.dir/ColaMensajes.i

CMakeFiles/plataforma.dir/ColaMensajes.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/plataforma.dir/ColaMensajes.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/ColaMensajes.cpp -o CMakeFiles/plataforma.dir/ColaMensajes.s

CMakeFiles/plataforma.dir/ColaMensajes.o.requires:
.PHONY : CMakeFiles/plataforma.dir/ColaMensajes.o.requires

CMakeFiles/plataforma.dir/ColaMensajes.o.provides: CMakeFiles/plataforma.dir/ColaMensajes.o.requires
	$(MAKE) -f CMakeFiles/plataforma.dir/build.make CMakeFiles/plataforma.dir/ColaMensajes.o.provides.build
.PHONY : CMakeFiles/plataforma.dir/ColaMensajes.o.provides

CMakeFiles/plataforma.dir/ColaMensajes.o.provides.build: CMakeFiles/plataforma.dir/ColaMensajes.o

CMakeFiles/plataforma.dir/SalidaPorPantalla.o: CMakeFiles/plataforma.dir/flags.make
CMakeFiles/plataforma.dir/SalidaPorPantalla.o: ../SalidaPorPantalla.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/plataforma.dir/SalidaPorPantalla.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/plataforma.dir/SalidaPorPantalla.o -c /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/SalidaPorPantalla.cpp

CMakeFiles/plataforma.dir/SalidaPorPantalla.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/plataforma.dir/SalidaPorPantalla.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/SalidaPorPantalla.cpp > CMakeFiles/plataforma.dir/SalidaPorPantalla.i

CMakeFiles/plataforma.dir/SalidaPorPantalla.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/plataforma.dir/SalidaPorPantalla.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/SalidaPorPantalla.cpp -o CMakeFiles/plataforma.dir/SalidaPorPantalla.s

CMakeFiles/plataforma.dir/SalidaPorPantalla.o.requires:
.PHONY : CMakeFiles/plataforma.dir/SalidaPorPantalla.o.requires

CMakeFiles/plataforma.dir/SalidaPorPantalla.o.provides: CMakeFiles/plataforma.dir/SalidaPorPantalla.o.requires
	$(MAKE) -f CMakeFiles/plataforma.dir/build.make CMakeFiles/plataforma.dir/SalidaPorPantalla.o.provides.build
.PHONY : CMakeFiles/plataforma.dir/SalidaPorPantalla.o.provides

CMakeFiles/plataforma.dir/SalidaPorPantalla.o.provides.build: CMakeFiles/plataforma.dir/SalidaPorPantalla.o

CMakeFiles/plataforma.dir/PlataformaReal.o: CMakeFiles/plataforma.dir/flags.make
CMakeFiles/plataforma.dir/PlataformaReal.o: ../PlataformaReal.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/plataforma.dir/PlataformaReal.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/plataforma.dir/PlataformaReal.o -c /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/PlataformaReal.cpp

CMakeFiles/plataforma.dir/PlataformaReal.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/plataforma.dir/PlataformaReal.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/PlataformaReal.cpp > CMakeFiles/plataforma.dir/PlataformaReal.i

CMakeFiles/plataforma.dir/PlataformaReal.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/plataforma.dir/PlataformaReal.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/PlataformaReal.cpp -o CMakeFiles/plataforma.dir/PlataformaReal.s

CMakeFiles/plataforma.dir/PlataformaReal.o.requires:
.PHONY : CMakeFiles/plataforma.dir/PlataformaReal.o.requires

CMakeFiles/plataforma.dir/PlataformaReal.o.provides: CMakeFiles/plataforma.dir/PlataformaReal.o.requires
	$(MAKE) -f CMakeFiles/plataforma.dir/build.make CMakeFiles/plataforma.dir/PlataformaReal.o.provides.build
.PHONY : CMakeFiles/plataforma.dir/PlataformaReal.o.provides

CMakeFiles/plataforma.dir/PlataformaReal.o.provides.build: CMakeFiles/plataforma.dir/PlataformaReal.o

CMakeFiles/plataforma.dir/ArchConfiguracion.o: CMakeFiles/plataforma.dir/flags.make
CMakeFiles/plataforma.dir/ArchConfiguracion.o: ../ArchConfiguracion.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/plataforma.dir/ArchConfiguracion.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/plataforma.dir/ArchConfiguracion.o -c /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/ArchConfiguracion.cpp

CMakeFiles/plataforma.dir/ArchConfiguracion.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/plataforma.dir/ArchConfiguracion.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/ArchConfiguracion.cpp > CMakeFiles/plataforma.dir/ArchConfiguracion.i

CMakeFiles/plataforma.dir/ArchConfiguracion.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/plataforma.dir/ArchConfiguracion.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/ArchConfiguracion.cpp -o CMakeFiles/plataforma.dir/ArchConfiguracion.s

CMakeFiles/plataforma.dir/ArchConfiguracion.o.requires:
.PHONY : CMakeFiles/plataforma.dir/ArchConfiguracion.o.requires

CMakeFiles/plataforma.dir/ArchConfiguracion.o.provides: CMakeFiles/plataforma.dir/ArchConfiguracion.o.requires
	$(MAKE) -f CMakeFiles/plataforma.dir/build.make CMakeFiles/plataforma.dir/ArchConfiguracion.o.provides.build
.PHONY : CMakeFiles/plataforma.dir/ArchConfiguracion.o.provides

CMakeFiles/plataforma.dir/ArchConfiguracion.o.provides.build: CMakeFiles/plataforma.dir/ArchConfiguracion.o

# Object files for target plataforma
plataforma_OBJECTS = \
"CMakeFiles/plataforma.dir/mainPlataforma.o" \
"CMakeFiles/plataforma.dir/PlataformaVirtual.o" \
"CMakeFiles/plataforma.dir/SemRobots.o" \
"CMakeFiles/plataforma.dir/ColaMensajes.o" \
"CMakeFiles/plataforma.dir/SalidaPorPantalla.o" \
"CMakeFiles/plataforma.dir/PlataformaReal.o" \
"CMakeFiles/plataforma.dir/ArchConfiguracion.o"

# External object files for target plataforma
plataforma_EXTERNAL_OBJECTS =

plataforma: CMakeFiles/plataforma.dir/mainPlataforma.o
plataforma: CMakeFiles/plataforma.dir/PlataformaVirtual.o
plataforma: CMakeFiles/plataforma.dir/SemRobots.o
plataforma: CMakeFiles/plataforma.dir/ColaMensajes.o
plataforma: CMakeFiles/plataforma.dir/SalidaPorPantalla.o
plataforma: CMakeFiles/plataforma.dir/PlataformaReal.o
plataforma: CMakeFiles/plataforma.dir/ArchConfiguracion.o
plataforma: CMakeFiles/plataforma.dir/build.make
plataforma: CMakeFiles/plataforma.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable plataforma"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/plataforma.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/plataforma.dir/build: plataforma
.PHONY : CMakeFiles/plataforma.dir/build

CMakeFiles/plataforma.dir/requires: CMakeFiles/plataforma.dir/mainPlataforma.o.requires
CMakeFiles/plataforma.dir/requires: CMakeFiles/plataforma.dir/PlataformaVirtual.o.requires
CMakeFiles/plataforma.dir/requires: CMakeFiles/plataforma.dir/SemRobots.o.requires
CMakeFiles/plataforma.dir/requires: CMakeFiles/plataforma.dir/ColaMensajes.o.requires
CMakeFiles/plataforma.dir/requires: CMakeFiles/plataforma.dir/SalidaPorPantalla.o.requires
CMakeFiles/plataforma.dir/requires: CMakeFiles/plataforma.dir/PlataformaReal.o.requires
CMakeFiles/plataforma.dir/requires: CMakeFiles/plataforma.dir/ArchConfiguracion.o.requires
.PHONY : CMakeFiles/plataforma.dir/requires

CMakeFiles/plataforma.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/plataforma.dir/cmake_clean.cmake
.PHONY : CMakeFiles/plataforma.dir/clean

CMakeFiles/plataforma.dir/depend:
	cd /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/build /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/build /home/knoppix/Desktop/Proyectos/Ejercicio1/Fuente/build/CMakeFiles/plataforma.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/plataforma.dir/depend

