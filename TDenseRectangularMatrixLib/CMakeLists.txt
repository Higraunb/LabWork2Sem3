 file(GLOB hdrs "*.h*") #Добавляем в переменную hdrs все файлы с расширением .h
file(GLOB srcs "*.cpp")#Добавляем в переменную srcs все файлы с расширением .h

add_library(${TDenseRectangularMatrixlib} TDenseRectangularMatrix ${srcs} ${hdrs})

target_link_libraries(${TDenseRectangularMatrixlib} ${vectorlib})
target_include_directories(${TDenseRectangularMatrixlib} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})