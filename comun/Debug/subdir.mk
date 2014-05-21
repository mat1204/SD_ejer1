################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ArchConfiguracion.cpp \
../ColaMensajes.cpp \
../GestorArch.cpp \
../MemoriaCompartida.cpp \
../SalidaPorPantalla.cpp \
../Semaforo.cpp \
../Socket.cpp \
../enviar.cpp \
../recibir.cpp \
../tcpopact.cpp \
../tcpoppas.cpp 

OBJS += \
./ArchConfiguracion.o \
./ColaMensajes.o \
./GestorArch.o \
./MemoriaCompartida.o \
./SalidaPorPantalla.o \
./Semaforo.o \
./Socket.o \
./enviar.o \
./recibir.o \
./tcpopact.o \
./tcpoppas.o 

CPP_DEPS += \
./ArchConfiguracion.d \
./ColaMensajes.d \
./GestorArch.d \
./MemoriaCompartida.d \
./SalidaPorPantalla.d \
./Semaforo.d \
./Socket.d \
./enviar.d \
./recibir.d \
./tcpopact.d \
./tcpoppas.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


