PROJECT(Ejer1)
set(comun ../../comun)
set( DCMAKE_BUILD_TYPE Debug)
set( dependencias PlataformaVirtual.cpp SemRobots.cpp ColaMensajes.cpp PlataformaReal.cpp Plataforma.cpp ComponenteRobot.cpp ${comun}/ArchConfiguracion.cpp ${comun}/MemoriaCompartida.cpp)

INCLUDE_DIRECTORIES(${comun})
#add_subdirectory(${comun})

aux_source_directory(../../comun comunes)
#aux_source_directory(. dependencias)

ADD_EXECUTABLE(lanzador mainLanzador.cpp ${dependencias} ${comunes})

ADD_EXECUTABLE(robotFrec mainRobotFrec.cpp ${dependencias} ${comunes})

ADD_EXECUTABLE(robotArmar mainRobotArmar.cpp ${dependencias} ${comunes})

ADD_EXECUTABLE(plataforma mainPlataforma.cpp ${dependencias} ${comunes})

