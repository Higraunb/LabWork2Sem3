#include <gtest.h>
#include "TVector.h"
#include "TDenseMatrix.h"
#include "TBandedMatrix.h"

// Фикстура для тестов
class TBandedMatrixTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Создаем тестовую ленточную матрицу 3x3
    // Матрица:
    // 1 2 0
    // 3 4 5
    // 0 6 7
    matrix = TBandedMatrix<int>({
        {1, 2, 0},
        {3, 4, 5},
        {0, 6, 7}
      });
  }

  TBandedMatrix<int> matrix;
};

// Тест конструктора по умолчанию
TEST_F(TBandedMatrixTest, DefaultConstructor) {
  TBandedMatrix<int> mat;
  EXPECT_EQ(mat.GetDim(), 0);
  EXPECT_TRUE(mat.empty());
}

// Тест конструктора из initializer_list
TEST_F(TBandedMatrixTest, InitializerListConstructor) {
  TBandedMatrix<int> mat = {
      {1, 0, 0},
      {0, 2, 3},
      {0, 4, 5}
  };

  EXPECT_EQ(mat.GetDim(), 3);
  EXPECT_FALSE(mat.empty());
  EXPECT_EQ(mat[0][0], 1);
  EXPECT_EQ(mat[1][1], 2);
  EXPECT_EQ(mat[1][2], 3);
  EXPECT_EQ(mat[2][1], 4);
  EXPECT_EQ(mat[2][2], 5);
}

// Тест конструктора копирования
TEST_F(TBandedMatrixTest, CopyConstructor) {
  TBandedMatrix<int> copy(matrix);

  EXPECT_EQ(copy.GetDim(), matrix.GetDim());
  EXPECT_EQ(copy[0][0], 1);
  EXPECT_EQ(copy[1][1], 4);
  EXPECT_EQ(copy[2][2], 7);
}

// Тест конструктора перемещения
TEST_F(TBandedMatrixTest, MoveConstructor) {
  TBandedMatrix<int> original = {
      {1, 2},
      {3, 4}
  };

  TBandedMatrix<int> moved(std::move(original));

  EXPECT_EQ(moved.GetDim(), 2);
  EXPECT_EQ(moved[0][0], 1);
  EXPECT_EQ(moved[1][1], 4);
  EXPECT_EQ(original.GetDim(), 0); // После перемещения original должен быть в валидном состоянии
}

// Тест оператора присваивания
TEST_F(TBandedMatrixTest, AssignmentOperator) {
  TBandedMatrix<int> assigned;
  assigned = matrix;

  EXPECT_EQ(assigned.GetDim(), matrix.GetDim());
  EXPECT_EQ(assigned[0][0], 1);
  EXPECT_EQ(assigned[1][1], 4);
  EXPECT_EQ(assigned[2][2], 7);
}

// Тест оператора перемещающего присваивания
TEST_F(TBandedMatrixTest, MoveAssignmentOperator) {
  TBandedMatrix<int> original = {
      {5, 0},
      {1, 6}
  };

  TBandedMatrix<int> target;
  target = std::move(original);

  EXPECT_EQ(target.GetDim(), 2);
  EXPECT_EQ(target[0][0], 5);
  EXPECT_EQ(target[1][1], 6);
  EXPECT_EQ(original.GetDim(), 0);
}

// Тест оператора сложения
TEST_F(TBandedMatrixTest, AdditionOperator) {
  TBandedMatrix<int> mat1 = {
      {1, 2},
      {3, 4}
  };

  TBandedMatrix<int> mat2 = {
      {5, 0},
      {1, 6}
  };

  TBandedMatrix<int> result = mat1 + mat2;

  EXPECT_EQ(result.GetDim(), 2);
  EXPECT_EQ(result[0][0], 6); // 1 + 5
  EXPECT_EQ(result[0][1], 2); // 2 + 0
  EXPECT_EQ(result[1][0], 4); // 3 + 1
  EXPECT_EQ(result[1][1], 10); // 4 + 6
}

// Тест оператора вычитания
TEST_F(TBandedMatrixTest, SubtractionOperator) {
  TBandedMatrix<int> mat1 = {
      {5, 3},
      {2, 8}
  };

  TBandedMatrix<int> mat2 = {
      {2, 1},
      {1, 4}
  };

  TBandedMatrix<int> result = mat1 - mat2;

  EXPECT_EQ(result.GetDim(), 2);
  EXPECT_EQ(result[0][0], 3); // 5 - 2
  EXPECT_EQ(result[0][1], 2); // 3 - 1
  EXPECT_EQ(result[1][0], 1); // 2 - 1
  EXPECT_EQ(result[1][1], 4); // 8 - 4
}

// Тест оператора умножения
TEST_F(TBandedMatrixTest, MultiplicationOperator) {
  TBandedMatrix<int> mat1 = {
      {1, 2},
      {3, 4}
  };

  TBandedMatrix<int> mat2 = {
      {2, 0},
      {1, 3}
  };

  TBandedMatrix<int> result = mat1 * mat2;

  EXPECT_EQ(result.GetDim(), 2);
  EXPECT_EQ(result[0][0], 4); // 1*2 + 2*1
  EXPECT_EQ(result[0][1], 6); // 1*0 + 2*3
  EXPECT_EQ(result[1][0], 10); // 3*2 + 4*1
  EXPECT_EQ(result[1][1], 12); // 3*0 + 4*3
}

// Тест операторов сравнения
TEST_F(TBandedMatrixTest, ComparisonOperators) {
  TBandedMatrix<int> mat1 = {
      {1, 2},
      {3, 4}
  };

  TBandedMatrix<int> mat2 = {
      {1, 2},
      {3, 4}
  };

  TBandedMatrix<int> mat3 = {
      {5, 6},
      {7, 8}
  };

  EXPECT_TRUE(mat1 == mat2);
  EXPECT_FALSE(mat1 == mat3);
  EXPECT_TRUE(mat1 != mat3);
}

// Тест методов доступа
TEST_F(TBandedMatrixTest, AccessMethods) {
  EXPECT_EQ(matrix.GetDim(), 3);

  TVector<size_t> row_counts = matrix.GetRowElemCount();
  TVector<size_t> col_indices = matrix.GetColumnIndex();
  TVector<int> data = matrix.GetData();

  EXPECT_FALSE(row_counts.empty());
  EXPECT_FALSE(col_indices.empty());
  EXPECT_FALSE(data.empty());
}

// Тест оператора индексации
TEST_F(TBandedMatrixTest, IndexOperator) {
  EXPECT_EQ(matrix[0][0], 1);
  EXPECT_EQ(matrix[0][1], 2);
  EXPECT_EQ(matrix[1][0], 3);
  EXPECT_EQ(matrix[1][1], 4);
  EXPECT_EQ(matrix[1][2], 5);
  EXPECT_EQ(matrix[2][1], 6);
  EXPECT_EQ(matrix[2][2], 7);

  // Проверка нулевых элементов
  EXPECT_EQ(matrix[0][2], 0);
  EXPECT_EQ(matrix[2][0], 0);
}

// Тест на выход за границы при индексации
TEST_F(TBandedMatrixTest, IndexOutOfBounds) {
  EXPECT_THROW(matrix[5][0], std::invalid_argument);
  EXPECT_THROW(matrix[0][5], std::invalid_argument);
}

// Тест метода SetDim
TEST_F(TBandedMatrixTest, SetDim) {
  matrix.SetDim(5);
  EXPECT_EQ(matrix.GetDim(), 5);
}

// Тест методов empty и full
TEST_F(TBandedMatrixTest, EmptyAndFull) {
  TBandedMatrix<int> emptyMat;
  EXPECT_TRUE(emptyMat.empty());
  EXPECT_FALSE(matrix.empty());

  // Для ленточной матрицы full обычно не имеет смысла, но тестируем как есть
  EXPECT_FALSE(matrix.full());
}

// Тест метода Clear
TEST_F(TBandedMatrixTest, Clear) {
  matrix.Clear();
  EXPECT_TRUE(matrix.empty());
  EXPECT_EQ(matrix.GetDim(), 0);
}

// Тест итераторов
TEST_F(TBandedMatrixTest, Iterators) {
  auto begin = matrix.begin();
  auto end = matrix.end();

  EXPECT_TRUE(begin.GetSize() > 0); // Предполагая, что TVector имеет метод GetSize()

  auto cbegin = matrix.cbegin();
  auto cend = matrix.cend();

  // Проверяем, что итераторы возвращают непустые векторы
  EXPECT_TRUE(cbegin.GetSize() > 0);
}

// Тест конструктора из плотной матрицы
TEST_F(TBandedMatrixTest, FromDenseMatrix) {
  // Создаем плотную матрицу 2x2
  TDenseMatrix<int> dense(2, 2);
  dense[0][0] = 1;
  dense[0][1] = 0;
  dense[1][0] = 2;
  dense[1][1] = 3;

  TBandedMatrix<int> banded(dense);

  EXPECT_EQ(banded.GetDim(), 2);
  EXPECT_EQ(banded[0][0], 1);
  EXPECT_EQ(banded[1][0], 2);
  EXPECT_EQ(banded[1][1], 3);
  EXPECT_EQ(banded[0][1], 0);
}

// Тест с различными типами данных
TEST_F(TBandedMatrixTest, DifferentDataTypes) {
  TBandedMatrix<double> doubleMatrix = {
      {1.5, 2.5},
      {3.5, 4.5}
  };

  EXPECT_EQ(doubleMatrix.GetDim(), 2);
  EXPECT_DOUBLE_EQ(doubleMatrix[0][0], 1.5);
  EXPECT_DOUBLE_EQ(doubleMatrix[1][1], 4.5);

  TBandedMatrix<float> floatMatrix = {
      {1.1f, 0.0f},
      {2.2f, 3.3f}
  };

  EXPECT_EQ(floatMatrix.GetDim(), 2);
  EXPECT_FLOAT_EQ(floatMatrix[0][0], 1.1f);
  EXPECT_FLOAT_EQ(floatMatrix[1][1], 3.3f);
}

// Тест исключений при несовпадающих размерах
TEST_F(TBandedMatrixTest, SizeMismatchExceptions) {
  TBandedMatrix<int> mat1 = { {1, 2}, {3, 4} };
  TBandedMatrix<int> mat2 = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

  EXPECT_THROW(mat1 + mat2, std::invalid_argument);
  EXPECT_THROW(mat1 - mat2, std::invalid_argument);
  EXPECT_THROW(mat1 * mat2, std::invalid_argument);
}


// Тест на симметричные операции
TEST_F(TBandedMatrixTest, SymmetricOperations) {
  TBandedMatrix<int> symmetric = {
      {1, 2, 0},
      {2, 3, 4},
      {0, 4, 5}
  };

  EXPECT_EQ(symmetric[0][1], 2);
  EXPECT_EQ(symmetric[1][0], 2);
  EXPECT_EQ(symmetric[1][2], 4);
  EXPECT_EQ(symmetric[2][1], 4);
}