# Создаем интерфейсную библиотеку для разреженных матриц
add_library(TSparseMatrixLib INTERFACE)

# Включаем директории с заголовками
target_include_directories(TSparseMatrixLib INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Зависимости
target_link_libraries(TSparseMatrixLib INTERFACE TVector)

# Компиляционные флаги
target_compile_features(TSparseMatrixLib INTERFACE cxx_std_17)

# Установка
install(FILES include/TSparseMatrix.h DESTINATION include)