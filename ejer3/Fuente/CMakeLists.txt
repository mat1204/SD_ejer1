project(Ejer3)
set (DCMAKE_BUILD_TYPE Debug)
set (dependencias ColaMensajes.cpp GestorPedidos.cpp SalidaPorPantalla.cpp ArchConfiguracion.cpp)
set (var_inutil Sin_USAR)

add_executable(lanzador mainLanzador.cpp ${dependencias})
add_executable(prod mainEmisor.cpp ${dependencias})
add_executable(cons mainReceptor.cpp ${dependencias})

