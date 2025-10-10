# ТОЛЬКО один исполняемый файл для всех тестов
add_executable(test_all
    test_main.cpp
    test_TVector.cpp
    test_TTriangleMatrix.cpp
    test_TDenseMatrix.cpp
    test_TSparseMatrix.cpp
    test_TBandedMatrix.cpp
)

target_link_libraries(test_all
    gtest
    gmock
    TVector
    TTriangleMatrixLib
    TDenseMatrixLib
    TSparseMatrixLib
    TBandedMatrixLib
)

include(GoogleTest)
gtest_discover_tests(test_all)