cmake_minimum_required(VERSION 3.5) #Проверка версии CMake.

set(PROJECT_NAME TMatrix) #Создаем обычную локальную переменную с именем проекта
project(${PROJECT_NAME}) # Название проекта
enable_testing()

set(application TMatrix) #Переменная с именем приложения

set(TTriangleMatrixlib TTriangleMatrixLibrary)
set(TDenseRectangularMatrixlib TDenseRectangularMatrixLibrary)
set(TSparseMatrixlib TSparseMatrixLibrary)
set(TBandedMatrixlib TBandedMatrixLibrary)
set(vectorlib TVectorLibrary)
  


set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(NOT CMAKE_BUILD_TYPE) # проверка имеющихся у компилятора вариантов сборки
  set(CMAKE_BUILD_TYPE Release) #Если нет то устанавливаем Release
endif()


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/TTriangleMatrix)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/TDenseRectangularMatrix)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/TSparseMatrix)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/TBandedMatrix)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/TVector)



add_subdirectory(TMatrixMain)
add_subdirectory(TTriangleMatrixLib)
add_subdirectory(TDenseRectangularMatrixLib)
add_subdirectory(TSparseMatrixLib)
add_subdirectory(TBandedMatrixLib)
add_subdirectory(TVector)
add_subdirectory(TMatrixTest)
add_subdirectory(gtest)
add_test(NAME TMatrix_Test 
         COMMAND TMatrix_Test
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/TMatrixTest)