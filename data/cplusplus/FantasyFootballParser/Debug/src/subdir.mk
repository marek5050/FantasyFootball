################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Drive.cpp \
../src/FantasyFootball1.cpp \
../src/Game.cpp \
../src/Play.cpp \
../src/PlayPoints.cpp \
../src/Players.cpp \
../src/PointCalculator.cpp \
../src/Team.cpp 

OBJS += \
./src/Drive.o \
./src/FantasyFootball1.o \
./src/Game.o \
./src/Play.o \
./src/PlayPoints.o \
./src/Players.o \
./src/PointCalculator.o \
./src/Team.o 

CPP_DEPS += \
./src/Drive.d \
./src/FantasyFootball1.d \
./src/Game.d \
./src/Play.d \
./src/PlayPoints.d \
./src/Players.d \
./src/PointCalculator.d \
./src/Team.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


