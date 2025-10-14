#include <gtest.h>
#include "TVector.h"
#include "TSparseMatrix.h"

class TSparseMatrixTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Создаем тестовые матрицы
    m1 = TSparseMatrix<int>(3, 2);
    m2 = TSparseMatrix<int>(2, 1);
  }

  TSparseMatrix<int> m1;
  TSparseMatrix<int> m2;
};

// Тест конструктора по умолчанию
TEST_F(TSparseMatrixTest, DefaultConstructor) {
  TSparseMatrix<int> mat;
  EXPECT_EQ(mat.GetDim(), 0);
  EXPECT_EQ(mat.GetWidth(), 0);
  EXPECT_TRUE(mat.empty());
}

// Тест конструктора с параметрами
TEST_F(TSparseMatrixTest, ParameterizedConstructor) {
  TSparseMatrix<int> mat(4, 3);
  EXPECT_EQ(mat.GetDim(), 4);
  EXPECT_EQ(mat.GetWidth(), 3);
}

// Тест конструктора копирования
TEST_F(TSparseMatrixTest, CopyConstructor) {
  // Заполняем m1 данными
  m1[0][0] = 1;
  m1[1][1] = 2;

  TSparseMatrix<int> copy(m1);
  EXPECT_EQ(copy.GetDim(), m1.GetDim());
  EXPECT_EQ(copy.GetWidth(), m1.GetWidth());
  EXPECT_EQ(copy[0][0], 1);
  EXPECT_EQ(copy[1][1], 2);
}

// Тест конструктора перемещения
TEST_F(TSparseMatrixTest, MoveConstructor) {
  TSparseMatrix<int> original(3, 2);
  original[0][0] = 5;

  TSparseMatrix<int> moved(std::move(original));
  EXPECT_EQ(moved.GetDim(), 3);
  EXPECT_EQ(moved.GetWidth(), 2);
  EXPECT_EQ(moved[0][0], 5);

  // Проверяем, что original в валидном состоянии
  EXPECT_EQ(original.GetDim(), 0);
  EXPECT_EQ(original.GetWidth(), 0);
}

// Тест конструктора из initializer_list
TEST_F(TSparseMatrixTest, InitializerListConstructor) {
  TSparseMatrix<int> mat = {
      {1, 2, 0},
      {2, 3, 4},
      {0, 4, 5}
  };

  EXPECT_EQ(mat.GetDim(), 3);
  EXPECT_EQ(mat[0][0], 1);
  EXPECT_EQ(mat[0][1], 2);
  EXPECT_EQ(mat[1][1], 3);
  EXPECT_EQ(mat[2][2], 5);
}

// Тест оператора присваивания
TEST_F(TSparseMatrixTest, AssignmentOperator) {
  m1[0][0] = 10;
  m1[1][1] = 20;

  TSparseMatrix<int> assigned;
  assigned = m1;

  EXPECT_EQ(assigned.GetDim(), m1.GetDim());
  EXPECT_EQ(assigned.GetWidth(), m1.GetWidth());
  EXPECT_EQ(assigned[0][0], 10);
  EXPECT_EQ(assigned[1][1], 20);
}

// Тест оператора перемещающего присваивания
TEST_F(TSparseMatrixTest, MoveAssignmentOperator) {
  TSparseMatrix<int> original(2, 1);
  original[0][0] = 15;

  TSparseMatrix<int> target;
  target = std::move(original);

  EXPECT_EQ(target.GetDim(), 2);
  EXPECT_EQ(target.GetWidth(), 1);
  EXPECT_EQ(target[0][0], 15);
}

// Тест оператора сложения
TEST_F(TSparseMatrixTest, AdditionOperator) {
  TSparseMatrix<int> mat1(2, 1);
  TSparseMatrix<int> mat2(2, 1);

  mat1[0][0] = 1;
  mat1[1][1] = 2;
  mat2[0][0] = 3;
  mat2[1][1] = 4;

  TSparseMatrix<int> result = mat1 + mat2;

  EXPECT_EQ(result[0][0], 4);
  EXPECT_EQ(result[1][1], 6);
}

// Тест оператора вычитания
TEST_F(TSparseMatrixTest, SubtractionOperator) {
  TSparseMatrix<int> mat1(2, 1);
  TSparseMatrix<int> mat2(2, 1);

  mat1[0][0] = 5;
  mat1[1][1] = 8;
  mat2[0][0] = 2;
  mat2[1][1] = 3;

  TSparseMatrix<int> result = mat1 - mat2;

  EXPECT_EQ(result[0][0], 3);
  EXPECT_EQ(result[1][1], 5);
}

// Тест оператора умножения
TEST_F(TSparseMatrixTest, MultiplicationOperator) {
  TSparseMatrix<int> mat1(2, 1);
  TSparseMatrix<int> mat2(2, 1);

  mat1[0][0] = 8;
  mat1[1][1] = 4;

  mat2[0][0] = 2;
  mat2[1][1] = 3;

  TSparseMatrix<int> result = mat1 * mat2;

  EXPECT_EQ(result[0][0], 16);  
  EXPECT_EQ(result[1][1], 12); 
}

// Тест операторов сравнения
TEST_F(TSparseMatrixTest, ComparisonOperators) {
  TSparseMatrix<int> mat1(2, 1);
  TSparseMatrix<int> mat2(2, 1);
  TSparseMatrix<int> mat3(3, 1);

  mat1[0][0] = 1;
  mat2[0][0] = 1;
  mat3[0][0] = 1;

  EXPECT_TRUE(mat1 == mat2);
  EXPECT_FALSE(mat1 == mat3);
  EXPECT_TRUE(mat1 != mat3);
}

// Тест методов GetDim и GetWidth
TEST_F(TSparseMatrixTest, GetDimAndWidth) {
  TSparseMatrix<int> mat(5, 3);
  EXPECT_EQ(mat.GetDim(), 5);
  EXPECT_EQ(mat.GetWidth(), 3);
}

// Тест методов SetDim и SetWidth
TEST_F(TSparseMatrixTest, SetDimAndWidth) {
  TSparseMatrix<int> mat(3, 2);
  mat[0][0] = 1;
  mat[1][1] = 2;

  mat.SetDim(4);
  mat.SetWidth(3);

  EXPECT_EQ(mat.GetDim(), 4);
  EXPECT_EQ(mat.GetWidth(), 3);
  // Проверяем, что данные сохранились
  EXPECT_EQ(mat[0][0], 1);
  EXPECT_EQ(mat[1][1], 2);
}

// Тест метода Clear
TEST_F(TSparseMatrixTest, Clear) {
  TSparseMatrix<int> mat(2, 1);
  mat[0][0] = 5;
  mat[1][1] = 10;

  mat.Clear();

  // После очистки все элементы должны быть нулевыми
  EXPECT_EQ(mat[0][0], 0);
  EXPECT_EQ(mat[1][1], 0);
}

// Тест оператора индексации
TEST_F(TSparseMatrixTest, IndexOperator) {
  TSparseMatrix<int> mat(3, 2);

  // Записываем значения
  mat[0][0] = 10;
  mat[1][1] = 20;
  mat[0][1] = 30;

  // Проверяем значения
  EXPECT_EQ(mat[0][0], 10);
  EXPECT_EQ(mat[1][1], 20);
  EXPECT_EQ(mat[0][1], 30);

  // Проверяем симметрию (для ленточной матрицы)
  EXPECT_EQ(mat[1][0], 30);
}

// Тест на выход за границы
TEST_F(TSparseMatrixTest, OutOfBounds) {
  TSparseMatrix<int> mat(2, 1);

  EXPECT_THROW(mat[5][0], std::out_of_range);
}

// Тест метода empty
TEST_F(TSparseMatrixTest, Empty) {
  TSparseMatrix<int> emptyMat;
  TSparseMatrix<int> nonEmptyMat(2, 1);

  EXPECT_TRUE(emptyMat.empty());
  EXPECT_FALSE(nonEmptyMat.empty());
}

// Тест метода full
TEST_F(TSparseMatrixTest, Full) {
  TSparseMatrix<int> mat(2, 2); // Полная матрица 2x2

  // Заполняем матрицу
  mat[0][0] = 1;
  mat[0][1] = 2;
  mat[1][0] = 3;
  mat[1][1] = 4;

  EXPECT_TRUE(mat.full());
}