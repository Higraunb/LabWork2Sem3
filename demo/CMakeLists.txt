# Создаем демонстрационное приложение
add_executable(LinearAlgebraDemo main.cpp)

# Линкуем с ВСЕМИ библиотеками
target_link_libraries(LinearAlgebraDemo 
    TVector
    TTriangleMatrixLib
    TDenseMatrixLib
    TSparseMatrixLib      # Новая
    TBandedMatrixLib      # Новая
)

# Установка демо-приложения
install(TARGETS LinearAlgebraDemo
    RUNTIME DESTINATION bin
)