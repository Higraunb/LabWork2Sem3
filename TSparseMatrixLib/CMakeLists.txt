 file(GLOB hdrs "*.h*") #Добавляем в переменную hdrs все файлы с расширением .h
file(GLOB srcs "*.cpp")#Добавляем в переменную srcs все файлы с расширением .h

add_library(${TSparseMatrixlib} TSparseMatrix ${srcs} ${hdrs})

target_link_libraries(${TSparseMatrixlib} ${vectorlib})
target_include_directories(${TSparseMatrixlib} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})