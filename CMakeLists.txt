cmake_minimum_required(VERSION 3.14)
project(LinearAlgebraLib VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 🔧 ИСПРАВЛЕНИЕ ДЛЯ WINDOWS - единые настройки runtime
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    
    # Для Google Test тоже устанавливаем динамический runtime
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    
    # Отключаем некоторые предупреждения
    add_compile_options(/W4)
endif()

# Опции проекта
option(BUILD_TESTS "Build tests" ON)
option(BUILD_DEMO "Build demonstration executable" ON)

# ... остальная часть вашего CMakeLists.txt ...

# Добавляем ВСЕ библиотеки (header-only)
add_subdirectory(TVector)
add_subdirectory(TTriangleMatrixLib)
add_subdirectory(TDenseMatrixLib)
add_subdirectory(TSparseMatrixLib)
add_subdirectory(TBandedMatrixLib)

# Демонстрационное приложение
if(BUILD_DEMO)
    add_subdirectory(demo)
endif()

# Настройка тестов
if(BUILD_TESTS)
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/googletest/CMakeLists.txt)
        message(STATUS "Using Google Test from local directory")
        add_subdirectory(googletest)
    else()
        message(FATAL_ERROR "BUILD_TESTS is ON but googletest folder not found!")
    endif()
    
    enable_testing()
    add_subdirectory(tests)
endif()

# Установка ВСЕХ библиотек (header-only) - ТОЛЬКО ЗДЕСЬ!
install(TARGETS 
    TVector
    TTriangleMatrixLib 
    TDenseMatrixLib
    TSparseMatrixLib
    TBandedMatrixLib
    EXPORT LinearAlgebraLibTargets
)

# Установка заголовочных файлов ВСЕХ библиотек
install(DIRECTORY 
    TVector/include/
    TTriangleMatrixLib/include/ 
    TDenseMatrixLib/include/
    TSparseMatrixLib/include/
    TBandedMatrixLib/include/
    DESTINATION include
)

# Config файл для find_package
install(EXPORT LinearAlgebraLibTargets
    FILE LinearAlgebraLibTargets.cmake
    DESTINATION lib/cmake/LinearAlgebraLib
)

# Package information
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    LinearAlgebraLibConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/LinearAlgebraLibConfigVersion.cmake
    DESTINATION lib/cmake/LinearAlgebraLib
)