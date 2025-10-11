//#include "gtest.h"
//#include "TTriangleMatrix.h"
//#include <sstream>
//
//// Тесты конструкторов
//TEST_F(TTriangleMatrix, DefaultConstructor) 
//{
//  TTriangleMatrix<int> 
//  EXPECT_EQ(emptyMatrix.GetRow(), 0);
//  EXPECT_EQ(emptyMatrix.GetColumn(), 0);
//  EXPECT_TRUE(emptyMatrix.empty());
//}
//
//TEST_F(TTriangleMatrix, SizeConstructor) {
//  TTriangleMatrix<int> matrix(3, 4);
//  EXPECT_EQ(matrix.GetRow(), 3);
//  EXPECT_EQ(matrix.GetColumn(), 4);
//  EXPECT_FALSE(matrix.empty());
//}
//
//TEST_F(TDenseMatrixTest, InitializerListConstructor) {
//  EXPECT_EQ(matrix2x3.GetRow(), 2);
//  EXPECT_EQ(matrix2x3.GetColumn(), 3);
//  EXPECT_EQ(matrix2x3[0][0], 1);
//  EXPECT_EQ(matrix2x3[0][1], 2);
//  EXPECT_EQ(matrix2x3[0][2], 3);
//  EXPECT_EQ(matrix2x3[1][0], 4);
//  EXPECT_EQ(matrix2x3[1][1], 5);
//  EXPECT_EQ(matrix2x3[1][2], 6);
//}
//
//TEST_F(TDenseMatrixTest, InitializerListConstructorThrowsOnInvalidInput) {
//  EXPECT_THROW({
//      TDenseMatrix<int> invalid({{1, 2}, {3}}); // Different row sizes
//    }, std::invalid_argument);
//}
//
//TEST_F(TDenseMatrixTest, CopyConstructor)
//{
//  TDenseMatrix<int> copy(matrix2x3);
//  EXPECT_EQ(copy.GetRow(), 2);
//  EXPECT_EQ(copy.GetColumn(), 3);
//  EXPECT_EQ(copy[0][0], 1);
//  EXPECT_EQ(copy[1][2], 6);
//}
//
//// Тесты методов доступа
//TEST_F(TDenseMatrixTest, GetRowGetColumn) {
//  EXPECT_EQ(matrix2x3.GetRow(), 2);
//  EXPECT_EQ(matrix2x3.GetColumn(), 3);
//}