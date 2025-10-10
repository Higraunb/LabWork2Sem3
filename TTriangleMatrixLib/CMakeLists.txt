# Создаем интерфейсную библиотеку
add_library(TTriangleMatrixLib INTERFACE)

# Включаем директории с заголовками
target_include_directories(TTriangleMatrixLib INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Зависимости
target_link_libraries(TTriangleMatrixLib INTERFACE TVector)

# Компиляционные флаги
target_compile_features(TTriangleMatrixLib INTERFACE cxx_std_17)

# Установка
install(FILES include/TTriangleMatrix.h DESTINATION include)