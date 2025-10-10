# Создаем интерфейсную библиотеку (header-only)
add_library(TVector INTERFACE)

# Включаем директории с заголовками
target_include_directories(TVector INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Компиляционные флаги
target_compile_features(TVector INTERFACE cxx_std_17)

# Если есть .cpp файлы с явными инстанциациями, можно добавить их так:
# if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/TVector.cpp)
#     target_sources(TVector INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/TVector.cpp)
# endif()

# Установка
install(FILES include/TVector.h DESTINATION include)