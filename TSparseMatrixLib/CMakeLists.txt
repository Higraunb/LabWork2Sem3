 file(GLOB hdrs "*.h*") #Добавляем в переменную hdrs все файлы с расширением .h
file(GLOB srcs "*.cpp")#Добавляем в переменную srcs все файлы с расширением .h

add_library(${tsparsematrixlib} STATIC ${srcs} ${hdrs})

target_link_libraries(${tsparsematrixlib} ${tvectorlib})