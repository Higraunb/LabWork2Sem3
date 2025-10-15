cmake_minimum_required(VERSION 3.5) #Проверка версии CMake.

set(PROJECT_NAME Matrix) #Создаем обычную локальную переменную с именем проекта
project(${PROJECT_NAME}) # Название проекта


set(application MatrixAPP) #Переменная с именем приложения

set(tbandedmatrixlib TBandedMatrixLibrary)
set(tdensematrixlib TDenseMatrixLibrary)
set(tvectorlib TVectorLibrary)
set(tsparsematrixlib TSparseMatrixLibrary)
set(ttrianglematrixlib TTriangleMatrixLibrary)    


set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(NOT CMAKE_BUILD_TYPE) # проверка имеющихся у компилятора вариантов сборки
  set(CMAKE_BUILD_TYPE Release) #Если нет то устанавливаем Release
endif()


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/TSparseMatrixLib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/TTriangleMatrixLib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/TVector)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/TDenseMatrixLib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/TBandedMatrixLib)


add_subdirectory(TBandedMatrixLib)
add_subdirectory(TDenseMatrixLib)
add_subdirectory(TTriangleMatrixLib)
add_subdirectory(TVector)
add_subdirectory(TSparseMatrixLib)
add_subdirectory(tests)
add_subdirectory(main)
add_subdirectory(gtest)