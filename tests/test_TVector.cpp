#include <gtest.h>
#include "TVector.h"

TEST(TVectorTest, DefaultConstructor) {
  TVector<int> vec;
  EXPECT_EQ(vec.GetSize(), 0);
  EXPECT_EQ(vec.GetCapacity(), 0);
  EXPECT_TRUE(vec.empty());
}

TEST(TVectorTest, SizeConstructor) {
  TVector<int> vec(5);
  EXPECT_EQ(vec.GetSize(), 0);
  EXPECT_EQ(vec.GetCapacity(), 5);
  EXPECT_TRUE(vec.empty());

  TVector<int> vec0(0);
  EXPECT_EQ(vec0.GetSize(), 0);
  EXPECT_EQ(vec0.GetCapacity(), 0);
}


TEST(TVectorTest, SizeValueConstructor) {
  TVector<int> vec(3, 10);
  EXPECT_EQ(vec.GetSize(), 3);
  EXPECT_EQ(vec.GetCapacity(), 3);
  EXPECT_EQ(vec[0], 10);
  EXPECT_EQ(vec[1], 10);
  EXPECT_EQ(vec[2], 10);

  TVector<int> vec0(0, 10);
  EXPECT_EQ(vec0.GetSize(), 0);
  EXPECT_EQ(vec0.GetCapacity(), 0);
}

TEST(TVectorTest, CopyConstructor) {
  TVector<int> original(2, 5);
  TVector<int> copy(original);

  EXPECT_EQ(copy.GetSize(), 2);
  EXPECT_EQ(copy.GetCapacity(), 2);
  EXPECT_EQ(copy[0], 5);
  EXPECT_EQ(copy[1], 5);
}


TEST(TVectorTest, MoveConstructor) {
  TVector<int> original(2, 5);
  TVector<int> moved(std::move(original));

  EXPECT_EQ(moved.GetSize(), 2);
  EXPECT_EQ(moved.GetCapacity(), 2);
  EXPECT_EQ(moved[0], 5);
  EXPECT_EQ(moved[1], 5);

  EXPECT_EQ(original.GetSize(), 0);
  EXPECT_EQ(original.GetCapacity(), 0);
  EXPECT_EQ(original.GetData(), nullptr);
}


TEST(TVectorTest, InitializerListConstructor) {
  TVector<int> vec{ 1, 2, 3 };
  EXPECT_EQ(vec.GetSize(), 3);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
}


TEST(TVectorTest, PushBack) {
  TVector<int> vec;
  vec.push_back(1);
  EXPECT_EQ(vec.GetSize(), 1);
  EXPECT_EQ(vec[0], 1);

  vec.push_back(2);
  EXPECT_EQ(vec.GetSize(), 2);
  EXPECT_EQ(vec[1], 2);
}


TEST(TVectorTest, PushFront) {
  TVector<int> vec;
  vec.push_front(1);
  EXPECT_EQ(vec.GetSize(), 1);
  EXPECT_EQ(vec[0], 1);

  vec.push_front(2);
  EXPECT_EQ(vec.GetSize(), 2);
  EXPECT_EQ(vec[0], 2);
  EXPECT_EQ(vec[1], 1);
}


TEST(TVectorTest, PopOperations) {
  TVector<int> vec{ 1, 2, 3 };

  vec.pop_back();
  EXPECT_EQ(vec.GetSize(), 2); 
  EXPECT_EQ(vec[2], 0);        

  vec.pop_front();
  EXPECT_EQ(vec.GetSize(), 1);
  EXPECT_EQ(vec[0], 2);
  EXPECT_EQ(vec[2], 0);
}


TEST(TVectorTest, AssignmentOperator) {
  TVector<int> vec1(2, 5);
  TVector<int> vec2;
  vec2 = vec1;

  EXPECT_EQ(vec2.GetSize(), 2);
  EXPECT_EQ(vec2[0], 5);
  EXPECT_EQ(vec2[1], 5);
}


TEST(TVectorTest, ComparisonOperators) {
  TVector<int> vec1{ 1, 2, 3 };
  TVector<int> vec2{ 1, 2, 3 };
  TVector<int> vec3{ 1, 2 };

  EXPECT_TRUE(vec1 == vec2);
  EXPECT_FALSE(vec1 == vec3);
  EXPECT_TRUE(vec1 != vec3);
}

TEST(TVectorTest, IndexOperator) {
  TVector<int> vec{ 1, 2, 3 };
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);

  vec[1] = 5;
  EXPECT_EQ(vec[1], 5);
}


TEST(TVectorTest, AdditionOperator) {
  TVector<int> vec1{ 1, 2 };
  TVector<int> vec2{ 3, 4 };
  TVector<int> result = vec1 + vec2;

  EXPECT_EQ(result.GetSize(), 4);
  EXPECT_EQ(result[0], 1);
  EXPECT_EQ(result[1], 2);
  EXPECT_EQ(result[2], 3);
  EXPECT_EQ(result[3], 4);
}

TEST(TVectorTest, Iterators) {
  TVector<int> vec{ 1, 2, 3 };
  int sum = 0;
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    sum += *it;
  }
  EXPECT_EQ(sum, 6);

  sum = 0;
  for (const auto& item : vec) {
    sum += item;
  }
  EXPECT_EQ(sum, 6);
}

TEST(TVectorTest, SetSizeCapacity) {
  TVector<int> vec;
  vec.SetSize(3);
  EXPECT_EQ(vec.GetSize(), 3);

  vec.SetCapacity(5);
  EXPECT_EQ(vec.GetCapacity(), 5);
}