PROJECT(Ejer1)
set( DCMAKE_BUILD_TYPE Debug)
set( dependencias PlataformaVirtual.cpp SemRobots.cpp ColaMensajes.cpp SalidaPorPantalla.cpp PlataformaReal.cpp ArchConfiguracion.cpp)

INCLUDE_directories(${CMAKE_CURRENT_SOURCE_DIR})

ADD_EXECUTABLE(lanzador mainLanzador.cpp ${dependencias})

ADD_EXECUTABLE(robotFrec mainRobotFrec.cpp ${dependencias})

ADD_EXECUTABLE(robotArmar mainRobotArmar.cpp ${dependencias})

ADD_EXECUTABLE(plataforma mainPlataforma.cpp ${dependencias})

