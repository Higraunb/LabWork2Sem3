# Создаем интерфейсную библиотеку
add_library(TDenseMatrixLib INTERFACE)

# Включаем директории с заголовками
target_include_directories(TDenseMatrixLib INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Зависимости
target_link_libraries(TDenseMatrixLib INTERFACE TVector)

# Компиляционные флаги
target_compile_features(TDenseMatrixLib INTERFACE cxx_std_17)

# Установка
install(FILES include/TDenserMatrix.h DESTINATION include)