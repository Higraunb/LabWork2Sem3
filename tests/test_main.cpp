#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char** argv) {
  std::cout << "=========================================" << std::endl;
  std::cout << "    Linear Algebra Library Tests" << std::endl;
  std::cout << "=========================================" << std::endl;

  // Инициализация Google Test
  testing::InitGoogleTest(&argc, argv);

  // Можно добавить кастомную конфигурацию
  // testing::GTEST_FLAG(output) = "xml:test_results.xml";
  // testing::GTEST_FLAG(filter) = "TVectorTest.*";

  std::cout << "Running all tests..." << std::endl;

  // Запуск всех тестов
  int result = RUN_ALL_TESTS();

  std::cout << "=========================================" << std::endl;
  std::cout << "Tests finished with result: " << (result == 0 ? "PASS" : "FAIL") << std::endl;
  std::cout << "=========================================" << std::endl;

  return result;
}