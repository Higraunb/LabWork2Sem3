set(target TMatrix_Test)

file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/../gtest"
    "${CMAKE_CURRENT_SOURCE_DIR}/../TVector"
    "${CMAKE_CURRENT_SOURCE_DIR}/../TTriangleMatrixLib"
    "${CMAKE_CURRENT_SOURCE_DIR}/../TDenseRectangularMatrixLib"
    "${CMAKE_CURRENT_SOURCE_DIR}/../TSparseMatrixLib"
    "${CMAKE_CURRENT_SOURCE_DIR}/../TBandedMatrixLib"	
)

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} gtest ${vectorlib})
target_link_libraries(${target} gtest ${TTriangleMatrixlib})
target_link_libraries(${target} gtest ${TDenseRectangularMatrixlib})
target_link_libraries(${target} gtest ${TSparseMatrixlib})
target_link_libraries(${target} gtest ${TBandedMatrixlib})