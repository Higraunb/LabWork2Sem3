set(target MatrixTest)

file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../gtest")

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} gtest ${tbandedmatrixlib})
target_link_libraries(${target} gtest ${tdensematrixlib})
target_link_libraries(${target} gtest ${tvectorlib})
target_link_libraries(${target} gtest ${tsparsematrixlib})
target_link_libraries(${target} gtest ${ttrianglematrixlib})