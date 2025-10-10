# Создаем интерфейсную библиотеку для ленточных матриц
add_library(TBandedMatrixLib INTERFACE)

# Включаем директории с заголовками
target_include_directories(TBandedMatrixLib INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Зависимости
target_link_libraries(TBandedMatrixLib INTERFACE TVector)

# Компиляционные флаги
target_compile_features(TBandedMatrixLib INTERFACE cxx_std_17)

# Установка
install(FILES include/TBandedMatrix.h DESTINATION include)