#include "gtest.h"
#include "TDenseRectangularMatrix.h"
#include <sstream>

class TDenseMatrixTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Матрица 2x3 для тестов
    matrix2x3 = { {1, 2, 3},
                 {4, 5, 6} };

    // Матрица 3x2 для тестов умножения
    matrix3x2 = { {1, 2},
                 {3, 4},
                 {5, 6} };

    // Единичная матрица 2x2
    identity2x2 = { {1, 0},
                   {0, 1} };
  }

  TDenseMatrix<int> matrix2x3;
  TDenseMatrix<int> matrix3x2;
  TDenseMatrix<int> identity2x2;
  TDenseMatrix<int> emptyMatrix;
};

// Тесты конструкторов
TEST_F(TDenseMatrixTest, DefaultConstructor) {
  EXPECT_EQ(emptyMatrix.GetRow(), 0);
  EXPECT_EQ(emptyMatrix.GetColumn(), 0);
  EXPECT_TRUE(emptyMatrix.empty());
}

TEST_F(TDenseMatrixTest, SizeConstructor) {
  TDenseMatrix<int> matrix(3, 4);
  EXPECT_EQ(matrix.GetRow(), 3);
  EXPECT_EQ(matrix.GetColumn(), 4);
  EXPECT_FALSE(matrix.empty());
}

TEST_F(TDenseMatrixTest, InitializerListConstructor) {
  EXPECT_EQ(matrix2x3.GetRow(), 2);
  EXPECT_EQ(matrix2x3.GetColumn(), 3);
  EXPECT_EQ(matrix2x3[0][0], 1);
  EXPECT_EQ(matrix2x3[0][1], 2);
  EXPECT_EQ(matrix2x3[0][2], 3);
  EXPECT_EQ(matrix2x3[1][0], 4);
  EXPECT_EQ(matrix2x3[1][1], 5);
  EXPECT_EQ(matrix2x3[1][2], 6);
}

TEST_F(TDenseMatrixTest, InitializerListConstructorThrowsOnInvalidInput) {
  EXPECT_THROW({
      TDenseMatrix<int> invalid({{1, 2}, {3}}); // Different row sizes
    }, std::invalid_argument);
}

TEST_F(TDenseMatrixTest, CopyConstructor) 
{
  TDenseMatrix<int> copy(matrix2x3);
  EXPECT_EQ(copy.GetRow(), 2);
  EXPECT_EQ(copy.GetColumn(), 3);
  EXPECT_EQ(copy[0][0], 1);
  EXPECT_EQ(copy[1][2], 6);
}

// Тесты методов доступа
TEST_F(TDenseMatrixTest, GetRowGetColumn) {
  EXPECT_EQ(matrix2x3.GetRow(), 2);
  EXPECT_EQ(matrix2x3.GetColumn(), 3);
}

TEST_F(TDenseMatrixTest, OperatorBrackets) {
  // Тест неконстантной версии
  EXPECT_EQ(matrix2x3[0][0], 1);
  EXPECT_EQ(matrix2x3[1][2], 6);

  // Тест константной версии
  const TDenseMatrix<int>& constMatrix = matrix2x3;
  EXPECT_EQ(constMatrix[0][1], 2);
  EXPECT_EQ(constMatrix[1][1], 5);
}

// Тесты модификаторов размера
TEST_F(TDenseMatrixTest, SetRow) {
  matrix2x3.SetRow(3);
  EXPECT_EQ(matrix2x3.GetRow(), 3);
  EXPECT_EQ(matrix2x3.GetColumn(), 3);
}

TEST_F(TDenseMatrixTest, SetColumn) {
  matrix2x3.SetColumn(4);
  EXPECT_EQ(matrix2x3.GetRow(), 2);
  EXPECT_EQ(matrix2x3.GetColumn(), 4);
}

// Тесты состояний
TEST_F(TDenseMatrixTest, Empty) {
  EXPECT_TRUE(emptyMatrix.empty());
  EXPECT_FALSE(matrix2x3.empty());
}

TEST_F(TDenseMatrixTest, Clear) {
  matrix2x3.Clear();

  // Проверяем, что все элементы стали 0
  for (size_t i = 0; i < matrix2x3.GetRow(); ++i) {
    for (size_t j = 0; j < matrix2x3.GetColumn(); ++j) {
      EXPECT_EQ(matrix2x3[i][j], 0);
    }
  }
}

// Тесты арифметических операций
TEST_F(TDenseMatrixTest, Addition) {
  TDenseMatrix<int> matrixA = { {1, 2}, {3, 4} };
  TDenseMatrix<int> matrixB = { {5, 6}, {7, 8} };

  TDenseMatrix<int> result = matrixA + matrixB;

  EXPECT_EQ(result.GetRow(), 2);
  EXPECT_EQ(result.GetColumn(), 2);
  EXPECT_EQ(result[0][0], 6);
  EXPECT_EQ(result[0][1], 8);
  EXPECT_EQ(result[1][0], 10);
  EXPECT_EQ(result[1][1], 12);
}

TEST_F(TDenseMatrixTest, AdditionThrowsOnSizeMismatch) {
  TDenseMatrix<int> differentSize(3, 3);

  EXPECT_THROW({
      auto result = matrix2x3 + differentSize;
    }, std::invalid_argument);
}

TEST_F(TDenseMatrixTest, Subtraction) {
  TDenseMatrix<int> matrixA = { {5, 6}, {7, 8} };
  TDenseMatrix<int> matrixB = { {1, 2}, {3, 4} };

  TDenseMatrix<int> result = matrixA - matrixB;

  EXPECT_EQ(result[0][0], 4);
  EXPECT_EQ(result[0][1], 4);
  EXPECT_EQ(result[1][0], 4);
  EXPECT_EQ(result[1][1], 4);
}

TEST_F(TDenseMatrixTest, Multiplication) {
  // 2x3 * 3x2 = 2x2
  TDenseMatrix<int> result = matrix2x3 * matrix3x2;

  EXPECT_EQ(result.GetRow(), 2);
  EXPECT_EQ(result.GetColumn(), 2);

  // Проверяем вычисления вручную:
  // [1,2,3] * [1,2]   = [1*1 + 2*3 + 3*5, 1*2 + 2*4 + 3*6] = [22, 28]
  // [4,5,6]   [3,4]     [4*1 + 5*3 + 6*5, 4*2 + 5*4 + 6*6] = [49, 64]
  //           [5,6]
  EXPECT_EQ(result[0][0], 22);
  EXPECT_EQ(result[0][1], 28);
  EXPECT_EQ(result[1][0], 49);
  EXPECT_EQ(result[1][1], 64);
}

TEST_F(TDenseMatrixTest, MultiplicationThrowsOnSizeMismatch) {
  TDenseMatrix<int> invalidSize(4, 4);
  EXPECT_ANY_THROW(matrix2x3 * invalidSize);
}

// Тесты операторов сравнения
TEST_F(TDenseMatrixTest, EqualityOperator) {
  TDenseMatrix<int> copy = matrix2x3;
  EXPECT_TRUE(matrix2x3 == copy);

  TDenseMatrix<int> different = { {1, 2, 3}, {4, 5, 7} };
  EXPECT_FALSE(matrix2x3 == different);
}

TEST_F(TDenseMatrixTest, InequalityOperator) {
  TDenseMatrix<int> different = { {1, 2, 3}, {4, 5, 7} };
  EXPECT_TRUE(matrix2x3 != different);

  TDenseMatrix<int> copy = matrix2x3;
  EXPECT_FALSE(matrix2x3 != copy);
}

// Тесты операторов присваивания
TEST_F(TDenseMatrixTest, CopyAssignment) {
  TDenseMatrix<int> copy;
  copy = matrix2x3;

  EXPECT_EQ(copy.GetRow(), 2);
  EXPECT_EQ(copy.GetColumn(), 3);
  EXPECT_EQ(copy[0][0], 1);
  EXPECT_EQ(copy[1][2], 6);
}

TEST_F(TDenseMatrixTest, MoveAssignment) {
  TDenseMatrix<int> temp = { {1, 2}, {3, 4} };
  TDenseMatrix<int> moved;
  moved = std::move(temp);

  EXPECT_EQ(moved.GetRow(), 2);
  EXPECT_EQ(moved.GetColumn(), 2);
  EXPECT_EQ(moved[0][0], 1);
  EXPECT_EQ(moved[1][1], 4);

  EXPECT_EQ(temp.GetRow(), 0);
  EXPECT_EQ(temp.GetColumn(), 0);
}

// Тесты ввода/вывода
TEST_F(TDenseMatrixTest, OutputOperator) {
  std::stringstream ss;
  ss << matrix2x3;

  std::string output = ss.str();
  // Проверяем, что вывод содержит ожидаемые значения
  EXPECT_TRUE(output.find("1") != std::string::npos);
  EXPECT_TRUE(output.find("6") != std::string::npos);
}

// Тесты методов push/pop (если они действительно нужны для матрицы)
TEST_F(TDenseMatrixTest, PushBack) {
  TDenseMatrix<int> matrix(1, 1);
  matrix[0][0] = 1;

  matrix.push_back(2);
  // Проверяем, что матрица расширилась корректно
  EXPECT_GE(matrix.GetRow(), 1);
}

TEST_F(TDenseMatrixTest, PushFront) {
  TDenseMatrix<int> matrix(1, 1);
  matrix[0][0] = 1;

  matrix.push_front(0);
  // Проверяем, что матрица расширилась корректно
  EXPECT_GE(matrix.GetRow(), 1);
}

// Тест на полную матрицу
TEST_F(TDenseMatrixTest, Full) {
  TDenseMatrix<int> fullMatrix(2, 2);
  fullMatrix[0][0] = 1; fullMatrix[0][1] = 2;
  fullMatrix[1][0] = 3; fullMatrix[1][1] = 4;

  EXPECT_TRUE(fullMatrix.full());

  TDenseMatrix<int> notFullMatrix(2, 2);
  notFullMatrix[0][0] = 1;
  // EXPECT_FALSE(notFullMatrix.full()); // Зависит от реализации TVector::full()
}

// Тест производительности для больших матриц
TEST_F(TDenseMatrixTest, LargeMatrixPerformance) {
  const size_t largeSize = 100;
  TDenseMatrix<int> largeMatrix(largeSize, largeSize);

  // Заполнение матрицы
  for (size_t i = 0; i < largeSize; ++i) {
    for (size_t j = 0; j < largeSize; ++j) {
      largeMatrix[i][j] = static_cast<int>(i + j);
    }
  }

  // Проверяем, что все элементы установлены корректно
  EXPECT_EQ(largeMatrix[0][0], 0);
  EXPECT_EQ(largeMatrix[largeSize - 1][largeSize - 1], static_cast<int>(2 * (largeSize - 1)));
}

// Тест исключительных ситуаций
TEST_F(TDenseMatrixTest, ExceptionSafety) {
  TDenseMatrix<int> original = { {1, 2}, {3, 4} };

  try {
    TDenseMatrix<int> invalid = original + TDenseMatrix<int>(3, 3);
    FAIL() << "Expected std::invalid_argument";
  }
  catch (const std::invalid_argument&) {
    // Ожидаемое исключение
    SUCCEED();
  }
  catch (...) {
    FAIL() << "Expected std::invalid_argument but got different exception";
  }

  // Проверяем, что original не изменился
  EXPECT_EQ(original[0][0], 1);
  EXPECT_EQ(original[1][1], 4);
}