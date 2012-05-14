################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Cli.cpp \
../ElTest.cpp \
../IntersectionTest.cpp \
../Line.cpp \
../Point2d.cpp \
../main.cpp 

OBJS += \
./Cli.o \
./ElTest.o \
./IntersectionTest.o \
./Line.o \
./Point2d.o \
./main.o 

CPP_DEPS += \
./Cli.d \
./ElTest.d \
./IntersectionTest.d \
./Line.d \
./Point2d.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


