// #include <gtest/gtest.h>
//
// #include <array>
// #include <deque>
// #include <exception>
// #include <iostream>
// #include <list>
// #include <set>
// #include <string>
// #include <vector>
//
// #include "../../../DataStructures/Gender.hpp"
// #include "../../../DataStructures/Person.hpp"
// #include "../../../DataStructures/PersonLibrary.hpp"
//
// #include "../../../Queryable/QueryBuilder.hpp"
//
//
// using namespace QueryBuilder;
//
// class SkipWhileFunctionalTest : public ::testing::Test
// {
// protected:
//   size_t threshold = 10;
//   int expectedCountUnordered = 8;
//   int expectedCountOrdered = 6;
//   int expectedCountOrderedSet = 5;
//   InternalQueryable<size_t> queryable;
//
//   void SetUp() override
//   {
//     this->queryable = InternalQueryable<size_t>(std::vector<size_t>({ 4, 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 9, 867, 12 }));
//   }
//
//   void TearDown() override {}
// };
//
// TEST_F(SkipWhileFunctionalTest, SkipWhileVectorUninitialized)
// {
//   InternalQueryable<Person> emptyQueryable;
//   InternalQueryable<Person> * result = emptyQueryable.SkipWhile([](Person p) { return true; });
//
//   ASSERT_EQ(0, result->Count());
// }
//
// TEST_F(SkipWhileFunctionalTest, SkipWhileVectorAlwaysTrue)
// {
//   InternalQueryable<size_t>* result = this->queryable.SkipWhile([](size_t value) { return true; });
//
//   ASSERT_EQ(this->queryable.Count(), result->Count());
//
//   for (int i = 0; i < this->queryable.Count(); i++)
//   {
//     ASSERT_EQ(this->queryable.At(i), result->At(i));
//   }
// }
//
// TEST_F(SkipWhileFunctionalTest, SkipWhileVector)
// {
//   InternalQueryable<size_t>* result = this->queryable
//     .SkipWhile([&](size_t value) { return value < this->threshold; });
//
//   ASSERT_EQ(this->expectedCountUnordered, result->Count());
//
//   for (int i = 0; i < result->Count(); i++)
//   {
//     ASSERT_TRUE(result->At(i) > 7);
//   }
// }
//
// TEST_F(SkipWhileFunctionalTest, SkipWhileSet)
// {
//   InternalQueryable<size_t> queryableSet = BuildQueryable(this->queryable.ToSet());
//   InternalQueryable<size_t>* result = queryableSet
//     .SkipWhile([&](size_t value) { return value < this->threshold; });
//
//   ASSERT_EQ(this->expectedCountOrderedSet, result->Count());
//
//   for (int i = 0; i < result->Count(); i++)
//   {
//     ASSERT_TRUE((result->At(i) / 10) > 0);
//   }
// }
//
// TEST_F(SkipWhileFunctionalTest, SkipWhileMultiSet)
// {
//   InternalQueryable<size_t> queryableSet = BuildQueryable(this->queryable.ToMultiSet());
//   InternalQueryable<size_t>* result = queryableSet
//     .SkipWhile([&](size_t value) { return value < this->threshold; });
//
//   ASSERT_EQ(this->expectedCountOrdered, result->Count());
//
//   for (int i = 0; i < result->Count(); i++)
//   {
//     ASSERT_TRUE((result->At(i) / 10) > 0);
//   }
// }
//
// TEST_F(SkipWhileFunctionalTest, SkipWhileDeque)
// {
//   InternalQueryable<size_t> queryableSet = BuildQueryable(this->queryable.ToDeque());
//   InternalQueryable<size_t>* result = queryableSet
//     .SkipWhile([&](size_t value) { return value < this->threshold; });
//
//   ASSERT_EQ(this->expectedCountUnordered, result->Count());
//
//   for (int i = 0; i < result->Count(); i++)
//   {
//     ASSERT_TRUE(result->At(i) > 7);
//   }
// }
//
// TEST_F(SkipWhileFunctionalTest, SkipWhileList)
// {
//   InternalQueryable<size_t> queryableSet = BuildQueryable(this->queryable.ToList());
//   InternalQueryable<size_t>* result = queryableSet
//     .SkipWhile([&](size_t value) { return value < this->threshold; });
//
//   ASSERT_EQ(this->expectedCountUnordered, result->Count());
//
//   for (int i = 0; i < result->Count(); i++)
//   {
//     ASSERT_TRUE(result->At(i) > 7);
//   }
// }
//
// TEST_F(SkipWhileFunctionalTest, SkipWhileWhere)
// {
//   int skipCount = 4;
//   int expectedCount = 2;
//   InternalQueryable<size_t> queryableVector = BuildQueryable(std::vector<size_t>({ 7, 0, 7, 2, 3, 4, 6, 45, 8, 1, 3, 10 }));
//   InternalQueryable<size_t> * result = queryableVector
//     .Where([](size_t value) { return value % 2 == 0; })
//     .SkipWhile([](size_t value) { return value < 8; });
//
//   ASSERT_EQ(expectedCount, result->Count());
//   result->ForEach([&](size_t value) { ASSERT_EQ(skipCount++ * 2, value); });
// }
