project(ejer7)

set( DCMAKE_BUILD_TYPE Debug)
set( dep ColaComponentes.cpp ColaPiezas.cpp Estacion.cpp EstacionVirtual.cpp CompEstacion.cpp ) 

aux_source_directory(../../comun comun)

add_executable(lanzador mainLanzador.cpp ${dep} ${comun})

add_executable(estacion	mainEstacion.cpp ${dep} ${comun})

add_executable(comp	mainComponente.cpp ${dep} ${comun})