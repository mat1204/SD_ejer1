project(ejer5)

set( CMAKE_TYPE_BUILD Debug)

aux_source_directory(../../comun comun)

set( dep Mutex.cpp SalaVirtual.cpp )

add_executable(lanzador mainLanzador.cpp ${comun} ${dep})