project(Ejer3)
set (CMAKE_BUILD_TYPE Debug)
set (dependencias ColaComponentes.cpp GestorPedidos.cpp GestorActores.cpp ColaDirecciones.cpp)

include_directories(../../comun)

aux_source_directory(../../comun comun)

add_executable(lanzador mainLanzador.cpp ${dependencias} ${comun})
add_executable(prod mainProductor.cpp ${dependencias} ${comun})
add_executable(cons mainConsumidor.cpp ${dependencias} ${comun})

add_executable(serv  mainServidor.cpp  ${dependencias} ${comun})
add_executable(asist mainAsistidor.cpp ${dependencias} ${comun})

add_executable(prodEmi mainProdServidor.cpp ${dependencias} ${comun})
add_executable(emisor mainProdEmisor.cpp ${dependencias} ${comun})

add_executable(consRecep mainConsServidor.cpp ${dependencias} ${comun})
add_executable(recep 	mainConsReceptor.cpp ${dependencias} ${comun})
