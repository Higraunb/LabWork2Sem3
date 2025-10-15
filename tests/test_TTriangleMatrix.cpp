#include <gtest.h>
#include "TTriangleMatrix.h"
#include <sstream>


class TTriangleMatrixTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Инициализация тестовых данных
  }

  void TearDown() override {
    // Очистка
  }
};

// Тесты конструкторов
TEST_F(TTriangleMatrixTest, DefaultConstructor) {
  TTriangleMatrix<int> matrix;
  EXPECT_EQ(matrix.GetDim(), 0);
  EXPECT_TRUE(matrix.empty());
}

TEST_F(TTriangleMatrixTest, SizeConstructor) 
{
  TTriangleMatrix<int> matrix(4);
  EXPECT_EQ(matrix.GetDim(), 4);
  EXPECT_EQ(matrix.GetData().GetCapacity(), 10);
}

TEST_F(TTriangleMatrixTest, InitializerListConstructor) {
  TTriangleMatrix<int> matrix({ {1}, {2, 3}, {4, 5, 6} });
  EXPECT_EQ(matrix.GetDim(), 3);

  // Проверяем данные через GetData()
  auto data = matrix.GetData();
  EXPECT_EQ(data[0], 1);   // [0][0]
  EXPECT_EQ(data[1], 2);   // [1][0]
  EXPECT_EQ(data[2], 3);   // [1][1]
  EXPECT_EQ(data[3], 4);   // [2][0]
  EXPECT_EQ(data[4], 5);   // [2][1]
  EXPECT_EQ(data[5], 6);   // [2][2]
}

TEST_F(TTriangleMatrixTest, CopyConstructor) {
  TTriangleMatrix<int> original({ {1}, {2, 3} });
  TTriangleMatrix<int> copy(original);

  EXPECT_EQ(copy.GetDim(), original.GetDim());
}

TEST_F(TTriangleMatrixTest, MoveConstructor) {
  TTriangleMatrix<int> original({ {1}, {2, 3} });
  size_t originalDim = original.GetDim();
  size_t originalDataSize = original.GetData().GetSize();

  TTriangleMatrix<int> moved(std::move(original));

  EXPECT_EQ(moved.GetDim(), originalDim);
  EXPECT_EQ(moved.GetData().GetSize(), originalDataSize);
  EXPECT_EQ(original.GetDim(), 0); // После перемещения original должен быть пустым
  EXPECT_TRUE(original.empty());
}

TEST_F(TTriangleMatrixTest, ParameterizedConstructor) {
  TTriangleMatrix<int> matrix(3, 5); // 3x3 матрица, заполненная 5
  EXPECT_EQ(matrix.GetDim(), 3);

  auto data = matrix.GetData();
  for (size_t i = 0; i < data.GetSize(); ++i) {
    EXPECT_EQ(data[i], 5);
  }
}

// Тесты методов доступа
TEST_F(TTriangleMatrixTest, GetDim) {
  TTriangleMatrix<int> matrix2({ {1}, {2, 3}, {4, 5, 6} });
  TTriangleMatrix<int> matrix3({ {1}, {2, 3} });

  EXPECT_EQ(matrix2.GetDim(), 3);
  EXPECT_EQ(matrix3.GetDim(), 2);
}

TEST_F(TTriangleMatrixTest, GetData) {
  TTriangleMatrix<int> matrix({ {1}, {2, 3} });
  auto data = matrix.GetData();

  EXPECT_EQ(data.GetSize(), 3); // 2*(2+1)/2 = 3
  EXPECT_EQ(data[0], 1);
  EXPECT_EQ(data[1], 2);
  EXPECT_EQ(data[2], 3);
}

TEST_F(TTriangleMatrixTest, SetDim) {
  TTriangleMatrix<int> matrix({ {1}, {2, 3} });
  matrix.SetDim(4);
  EXPECT_EQ(matrix.GetDim(), 4);
}

// Тесты итераторов
TEST_F(TTriangleMatrixTest, Iterators) {
  TTriangleMatrix<int> matrix({ {1}, {2, 3}, {4, 5, 6} });

  // Тест begin/end
  int sum = 0;
  auto data = matrix.GetData();
  for (size_t i = 0; i < data.GetSize(); ++i) {
    sum += data[i];
  }
  EXPECT_EQ(sum, 21); // 1+2+3+4+5+6 = 21
}

TEST_F(TTriangleMatrixTest, EmptyAndFull) {
  TTriangleMatrix<int> empty_matrix;
  EXPECT_TRUE(empty_matrix.empty());

  TTriangleMatrix<int> non_empty({ {1}, {2, 3} });
  EXPECT_FALSE(non_empty.empty());
}

TEST_F(TTriangleMatrixTest, Clear) {
  TTriangleMatrix<int> matrix({ {1}, {2, 3} });
  matrix.Clear();

  // После Clear все элементы должны быть 0
  auto data = matrix.GetData();
  for (size_t i = 0; i < data.GetSize(); ++i) {
    EXPECT_EQ(data[i], 0);
  }
}

// Тесты операторов
TEST_F(TTriangleMatrixTest, AssignmentOperator) {
  TTriangleMatrix<int> original({ {1}, {2, 3} });
  TTriangleMatrix<int> copy;
  copy = original;

  EXPECT_EQ(copy.GetDim(), original.GetDim());
  EXPECT_EQ(1,copy == original);
}

TEST_F(TTriangleMatrixTest, MoveAssignmentOperator) {
  TTriangleMatrix<int> original({ {1}, {2, 3} });
  size_t originalDim = original.GetDim();
  TTriangleMatrix<int> moved;

  moved = std::move(original);

  EXPECT_EQ(moved.GetDim(), originalDim);
  EXPECT_EQ(original.GetDim(), 0);
}

TEST_F(TTriangleMatrixTest, AdditionOperator) {
  TTriangleMatrix<int> m1({ {1}, {2, 3} });
  TTriangleMatrix<int> m2({ {2}, {1, 4} });
  TTriangleMatrix<int> result = m1 + m2;

  auto data = result.GetData();
  EXPECT_EQ(data[0], 3); // 1+2
  EXPECT_EQ(data[1], 3); // 2+1
  EXPECT_EQ(data[2], 7); // 3+4
}

TEST_F(TTriangleMatrixTest, SubtractionOperator) {
  TTriangleMatrix<int> m1({ {5}, {4, 3} });
  TTriangleMatrix<int> m2({ {2}, {1, 1} });
  TTriangleMatrix<int> result = m1 - m2;

  auto data = result.GetData();
  EXPECT_EQ(data[0], 3); // 5-2
  EXPECT_EQ(data[1], 3); // 4-1
  EXPECT_EQ(data[2], 2); // 3-1
}

TEST_F(TTriangleMatrixTest, MultiplicationOperator) {
  TTriangleMatrix<int> m1({ {2}, {1, 3} });
  TTriangleMatrix<int> m2({ {3}, {2, 1} });
  TTriangleMatrix<int> result = m1 * m2;

  // Проверяем результат умножения треугольных матриц
  auto data = result.GetData();
  // Для матриц:
  // m1 = [2, 0]   m2 = [3, 0]
  //      [1, 3]        [2, 1]
  // Результат умножения:
  // [2*3,   0  ] = [6, 0]
  // [1*3+3*2, 1*0+3*1] = [9, 3]
  // Но в линейном представлении: [6, 9, 3]
  EXPECT_EQ(data[0], 6);  // [0][0]
  EXPECT_EQ(data[1], 9);  // [1][0] = 1*3 + 3*2 = 3 + 6 = 9
  EXPECT_EQ(data[2], 3);  // [1][1] = 1*0 + 3*1 = 0 + 3 = 3
}

TEST_F(TTriangleMatrixTest, EqualityOperator) {
  TTriangleMatrix<int> m1({ {1}, {2, 3} });
  TTriangleMatrix<int> m2({ {1}, {2, 3} });
  TTriangleMatrix<int> m3({ {1}, {2, 4} });

  EXPECT_TRUE(m1 == m2);
  EXPECT_FALSE(m1 == m3);
}

TEST_F(TTriangleMatrixTest, InequalityOperator) {
  TTriangleMatrix<int> m1({ {1}, {2, 3} });
  TTriangleMatrix<int> m2({ {1}, {2, 4} });

  EXPECT_TRUE(m1 != m2);
  EXPECT_FALSE(m1 != m1);
}

// Тесты ввода/вывода
TEST_F(TTriangleMatrixTest, OutputOperator) {
  TTriangleMatrix<int> matrix({ {1}, {2, 3} });
  std::stringstream ss;
  ss << matrix;

  std::string output = ss.str();
  // Проверяем, что вывод содержит ожидаемые значения
  EXPECT_TRUE(output.find("1") != std::string::npos);
  EXPECT_TRUE(output.find("2") != std::string::npos);
  EXPECT_TRUE(output.find("3") != std::string::npos);
}

// Тесты исключений
TEST_F(TTriangleMatrixTest, InvalidInitializerList) {
  // Некорректные размеры - должно бросить исключение
  EXPECT_THROW({
      TTriangleMatrix<int> matrix({{1, 2}, {3}}); // Первая строка имеет 2 элемента, но должна иметь 1
    }, std::invalid_argument);
}

TEST_F(TTriangleMatrixTest, InvalidOperationSizes) {
  TTriangleMatrix<int> m1(2);
  TTriangleMatrix<int> m2(3);

  // Операции с матрицами разных размеров должны бросать исключения
  EXPECT_ANY_THROW(m1 + m2);
  EXPECT_ANY_THROW(m1 - m2);
  EXPECT_ANY_THROW(m1 * m2);
}

// Тесты с разными типами данных
TEST(TTriangleMatrixDoubleTest, DoubleOperations) {
  TTriangleMatrix<double> m1({ {1.5}, {2.5, 3.5} });
  TTriangleMatrix<double> m2({ {0.5}, {1.5, 2.5} });

  auto result = m1 + m2;
  auto data = result.GetData();

  EXPECT_DOUBLE_EQ(data[0], 2.0);  // 1.5 + 0.5
  EXPECT_DOUBLE_EQ(data[1], 4.0);  // 2.5 + 1.5
  EXPECT_DOUBLE_EQ(data[2], 6.0);  // 3.5 + 2.5
}

// Тест производительности для больших матриц
TEST(TTriangleMatrixPerformanceTest, LargeMatrixOperations) {
  const size_t large_size = 100;
  TTriangleMatrix<int> large_matrix(large_size);

  // Заполняем матрицу тестовыми данными
  auto data = large_matrix.GetData();
  for (size_t i = 0; i < data.GetSize(); ++i) {
    data[i] = static_cast<int>(i);
  }

  // Тестируем операции с большими матрицами
  auto result = large_matrix + large_matrix;

  EXPECT_EQ(result.GetDim(), large_size);
}

// Тест на правильность индексации
TEST_F(TTriangleMatrixTest, Indexing) {
  TTriangleMatrix<int> matrix({ {10}, {20, 30}, {40, 50, 60} });

  // Проверяем правильность хранения данных
  auto data = matrix.GetData();
  EXPECT_EQ(data[0], 10); // [0][0]
  EXPECT_EQ(data[1], 20); // [1][0]
  EXPECT_EQ(data[2], 30); // [1][1]
  EXPECT_EQ(data[3], 40); // [2][0]
  EXPECT_EQ(data[4], 50); // [2][1]
  EXPECT_EQ(data[5], 60); // [2][2]
}