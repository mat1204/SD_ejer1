PROJECT(Ejer1)
set(comun ../../comun)
set( DCMAKE_BUILD_TYPE Debug)
set( dependencias SemRobots.cpp ColaComponentes.cpp Plataforma.cpp ComponenteRobot.cpp PlataformaVirtual.cpp)

INCLUDE_DIRECTORIES(${comun})
#add_subdirectory(${comun})

aux_source_directory(../../comun comunes)
#aux_source_directory(. dependencias)

MESSAGE(EMPIEZAAAAAAAAAAAAAAAAAA)
MESSAGE(${comunes})
MESSAGE(TERMINAAAAAAAAAAAAAAAAA)

ADD_EXECUTABLE(lanzador mainLanzador.cpp ${dependencias} ${comunes})

ADD_EXECUTABLE(robotFrec mainRobotFrec.cpp ${dependencias} ${comunes})

ADD_EXECUTABLE(robotArmar mainRobotArmar.cpp ${dependencias} ${comunes})

ADD_EXECUTABLE(comp mainComponente.cpp ${dependencias} ${comunes})

ADD_EXECUTABLE(activ mainActivador.cpp ${dependencias} ${comunes})