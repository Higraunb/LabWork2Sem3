cmake_minimum_required(VERSION 3.5) #Проверка версии CMake.

set(PROJECT_NAME TTriangleMatrix) #Создаем обычную локальную переменную с именем проекта
project(${PROJECT_NAME}) # Название проекта
enable_testing()

set(application TriangleMatirx) #Переменная с именем приложения

set(TTriangleMatrixlib TTriangleMatrixLibrary)
set(vectorlib TVectorLibrary)
  


set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(NOT CMAKE_BUILD_TYPE) # проверка имеющихся у компилятора вариантов сборки
  set(CMAKE_BUILD_TYPE Release) #Если нет то устанавливаем Release
endif()


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/TTriangleMatrix)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/TVector)



add_subdirectory(TTriangleMatrixMain)
add_subdirectory(TTriangleMatrixLib)
add_subdirectory(TVector)
add_subdirectory(TTriangleMatrixTest)
add_subdirectory(gtest)
add_test(NAME TTriangleMatrix_Test 
         COMMAND TTriangleMatrix_Test
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/TTriangleMatrixTest)