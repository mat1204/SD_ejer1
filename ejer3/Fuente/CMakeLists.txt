project(Ejer3)
set (DCMAKE_BUILD_TYPE Debug)
set (dependencias ColaComponentes.cpp GestorPedidos.cpp)

include_directories(../../comun)

aux_source_directory(../../comun comunes)

add_executable(lanzador mainLanzador.cpp ${dependencias} ${comunes})
add_executable(prod mainEmisor.cpp ${dependencias} ${comunes})
add_executable(cons mainReceptor.cpp ${dependencias} ${comunes})

