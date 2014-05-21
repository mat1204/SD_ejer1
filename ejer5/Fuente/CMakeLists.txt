project(ejer5)

set( CMAKE_BUILD_TYPE Debug)

aux_source_directory(../../comun comun)

set( dep Mutex.cpp SalaVirtual.cpp ColaComponentes.cpp Sala.cpp CompCableCarril.cpp CompPersona.cpp AreaPersonas.cpp ColaBloqueos.cpp Componente.cpp)


add_executable(compCC mainCompCC.cpp ${comun} ${dep})

add_executable(cc mainCC.cpp ${comun} ${dep})




add_executable(prod mainProductor.cpp ${comun} ${dep})

add_executable(compPer mainCompPersona.cpp ${comun} ${dep})

add_executable(pers mainPersona.cpp ${comun} ${dep})


add_executable(lanzador mainLanzador.cpp ${comun} ${dep})