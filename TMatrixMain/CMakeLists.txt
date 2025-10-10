file(GLOB hdrs "*.h*") #Добавляем в переменную hdrs все файлы с расширением .h
file(GLOB srcs "*.cpp")#Добавляем в переменную srcs все файлы с расширением .h
add_executable(${application} ${srcs} ${hdrs})

target_link_libraries(${application} 
    ${TDenseRectangularMatrixlib}
    ${TSparseMatrixlib}
    ${TBandedMatrixlib}
    ${TTriangleMatrixlib}
    ${vectorlib}
)


#add_library(${MyLib1} TMatrixMain ${srcs}