file(GLOB hdrs "*.h*") #Добавляем в переменную hdrs все файлы с расширением .h
file(GLOB srcs "*.cpp")#Добавляем в переменную srcs все файлы с расширением .h
add_executable(${application} ${srcs} ${hdrs})

target_link_libraries(${application} ${tbandedmatrixlib})
target_link_libraries(${application} ${tdensematrixlib})
target_link_libraries(${application} ${tvectorlib})
target_link_libraries(${application} ${tsparsematrixlib})
target_link_libraries(${application} ${ttrianglematrixlib})