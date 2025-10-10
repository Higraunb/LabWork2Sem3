 file(GLOB hdrs "*.h*") #Добавляем в переменную hdrs все файлы с расширением .h
file(GLOB srcs "*.cpp")#Добавляем в переменную srcs все файлы с расширением .h

add_library(${TBandedMatrixlib} TBandedMatrix ${srcs} ${hdrs})

target_link_libraries(${TBandedMatrixlib} ${vectorlib})
target_include_directories(${TBandedMatrixlib} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})