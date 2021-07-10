#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <exception>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>

#include "../../../DataStructures/Gender.h"
#include "../../../DataStructures/Person.h"
#include "../../../DataStructures/PersonLibrary.h"

#include "../../../Queryable/Queryable.h"
//
// class TakeWhileFunctionalTest : public ::testing::Test
// {
// protected:
//   uint threshold = 10;
//   int expectedCountUnordered = 6;
//   int expectedCountOrdered = 8;
//   int expectedCountOrderedSet = 5;
//   Queryable<uint, std::vector> queryable;
//
//   void SetUp() override
//   {
//     this->queryable = Queryable<uint, std::vector>({ 4, 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 });
//   }
//
//   void TearDown() override {}
// };
//
// TEST_F(TakeWhileFunctionalTest, TakeWhileVectorUninitialized)
// {
//   Queryable<Person, std::vector> emptyQueryable;
//   Queryable<Person, std::vector> result = emptyQueryable.TakeWhile([](Person p) { return true; });
//
//   ASSERT_EQ(0, result.Count());
// }
//
// TEST_F(TakeWhileFunctionalTest, TakeWhileVectorAlwaysTrue)
// {
//   Queryable<uint, std::vector> result = this->queryable.TakeWhile([](uint value) { return true; });
//
//   ASSERT_EQ(this->queryable.Count(), result.Count());
//
//   for (int i = 0; i < this->queryable.Count(); i++)
//   {
//     ASSERT_EQ(this->queryable.At(i), result.At(i));
//   }
// }
//
// TEST_F(TakeWhileFunctionalTest, TakeWhileVector)
// {
//   Queryable<uint, std::vector> result = this->queryable
//     .TakeWhile([&](uint value) { return value < this->threshold; });
//
//   ASSERT_EQ(this->expectedCountUnordered, result.Count());
//
//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_EQ(0, result.At(i) / 10);
//   }
// }
//
// TEST_F(TakeWhileFunctionalTest, TakeWhileSet)
// {
//   Queryable<uint, std::set> result = Queryable<uint, std::set>(this->queryable.ToSet())
//     .TakeWhile([&](uint value) { return value < this->threshold; });
//
//   ASSERT_EQ(this->expectedCountOrderedSet, result.Count());
//
//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_EQ(0, result.At(i) / 10);
//   }
// }
//
// TEST_F(TakeWhileFunctionalTest, TakeWhileMultiSet)
// {
//   Queryable<uint, std::multiset> result = Queryable<uint, std::multiset>(this->queryable.ToMultiSet())
//     .TakeWhile([&](uint value) { return value < this->threshold; });
//
//   ASSERT_EQ(this->expectedCountOrdered, result.Count());
//
//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_EQ(0, result.At(i) / 10);
//   }
// }
//
// TEST_F(TakeWhileFunctionalTest, TakeWhileDeque)
// {
//   Queryable<uint, std::deque> result = Queryable<uint, std::deque>(this->queryable.ToDeque())
//     .TakeWhile([&](uint value) { return value < this->threshold; });
//
//   ASSERT_EQ(this->expectedCountUnordered, result.Count());
//
//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_EQ(0, result.At(i) / 10);
//   }
// }
//
// TEST_F(TakeWhileFunctionalTest, TakeWhileList)
// {
//   Queryable<uint, std::list> result = Queryable<uint, std::list>(this->queryable.ToList())
//     .TakeWhile([&](uint value) { return value < this->threshold; });
//
//   ASSERT_EQ(this->expectedCountUnordered, result.Count());
//
//   for (int i = 0; i < result.Count(); i++)
//   {
//     ASSERT_EQ(0, result.At(i) / 10);
//   }
// }
