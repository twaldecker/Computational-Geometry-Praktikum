################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Cli.cpp \
../Point2d.cpp \
../Polygon.cpp \
../PolygonTest.cpp \
../main.cpp 

OBJS += \
./Cli.o \
./Point2d.o \
./Polygon.o \
./PolygonTest.o \
./main.o 

CPP_DEPS += \
./Cli.d \
./Point2d.d \
./Polygon.d \
./PolygonTest.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


