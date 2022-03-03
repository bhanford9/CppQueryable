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
// class SkipFunctionalTest : public ::testing::Test
// {
// protected:
//   int SkipCount = 5;
//   Queryable<uint> queryable;
//
//   void SetUp() override
//   {
//     this->queryable = Queryable<uint>(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12 }));
//   }
//
//   template<typename TObj>
//   void TestSkip(Queryable<TObj> * localQueryable, int toSkip)
//   {
//     std::vector<uint> expected;
//     for (int i = toSkip; i < localQueryable->Count(); i++)
//     {
//       expected.push_back(localQueryable->At(i));
//     }
//
//     Queryable<uint> * result = localQueryable->Skip(toSkip);
//
//     ASSERT_EQ(expected.size(), result->Count());
//
//     for (int i = 0; i < result->Count(); i++)
//     {
//       ASSERT_EQ(expected[i], result->At(i));
//     }
//   }
//
//   template<typename TObj>
//   void TestSkipNegative(Queryable<TObj> * localQueryable, int toSkip)
//   {
//     std::vector<uint> expected;
//     int endIndex = localQueryable->Count() + toSkip;
//     for (int i = 0; i < endIndex; i++)
//     {
//       expected.push_back(localQueryable->At(i));
//     }
//
//     Queryable<uint>* result = localQueryable->Skip(toSkip);
//
//     ASSERT_EQ(expected.size(), result->Count());
//
//     for (int i = 0; i < result->Count(); i++)
//     {
//       ASSERT_EQ(expected[i], result->At(i));
//     }
//   }
//
//   void TearDown() override {}
// };
//
// TEST_F(SkipFunctionalTest, SkipVectorUninitialized)
// {
//   Queryable<Person> emptyQueryable;
//   Queryable<Person> * result = emptyQueryable.Skip(this->SkipCount);
//
//   ASSERT_EQ(0, result->Count());
// }
//
// TEST_F(SkipFunctionalTest, SkipVectorSkipMoreThanSize)
// {
//   this->TestSkip(&this->queryable, this->queryable.Count() + 1);
// }
//
// TEST_F(SkipFunctionalTest, SkipVector)
// {
//   this->TestSkip(&this->queryable, this->SkipCount);
// }
//
// TEST_F(SkipFunctionalTest, SkipSet)
// {
//   Queryable<uint> localQueryable(this->queryable.ToSet());
//   this->TestSkip(&localQueryable, this->SkipCount);
// }
//
// TEST_F(SkipFunctionalTest, SkipMultiSet)
// {
//   Queryable<uint> localQueryable(this->queryable.ToMultiSet());
//   this->TestSkip(&localQueryable, this->SkipCount);
// }
//
// TEST_F(SkipFunctionalTest, SkipDeque)
// {
//   Queryable<uint> localQueryable(this->queryable.ToDeque());
//   this->TestSkip(&localQueryable, this->SkipCount);
// }
//
// TEST_F(SkipFunctionalTest, SkipList)
// {
//   Queryable<uint> localQueryable(this->queryable.ToList());
//   this->TestSkip(&localQueryable, this->SkipCount);
// }
//
// TEST_F(SkipFunctionalTest, SkipVectorNegative)
// {
//   this->TestSkipNegative(&this->queryable, -this->SkipCount);
// }
//
// TEST_F(SkipFunctionalTest, SkipSetNegative)
// {
//   Queryable<uint> localQueryable(this->queryable.ToSet());
//   this->TestSkipNegative(&localQueryable, -this->SkipCount);
// }
//
// TEST_F(SkipFunctionalTest, SkipMultiSetNegative)
// {
//   Queryable<uint> localQueryable(this->queryable.ToMultiSet());
//   this->TestSkipNegative(&localQueryable, -this->SkipCount);
// }
//
// TEST_F(SkipFunctionalTest, SkipDequeNegative)
// {
//   Queryable<uint> localQueryable(this->queryable.ToDeque());
//   this->TestSkipNegative(&localQueryable, -this->SkipCount);
// }
//
// TEST_F(SkipFunctionalTest, SkipListNegative)
// {
//   Queryable<uint> localQueryable(this->queryable.ToList());
//   this->TestSkipNegative(&localQueryable, -this->SkipCount);
// }
//
// TEST_F(SkipFunctionalTest, SkipWhere)
// {
//   int skipCount = 3;
//   int expectedCount = 3;
//   Queryable<uint> queryableVector = BuildQueryable(std::vector<uint>({ 7, 0, 7, 2, 3, 4, 6, 45, 8, 1, 3, 10 }));
//   Queryable<uint> * result = queryableVector
//     .Where([](uint value) { return value % 2 == 0; })
//     .Skip(skipCount);
//
//   ASSERT_EQ(expectedCount, result->Count());
//   result->ForEach([&](uint value) { ASSERT_EQ(skipCount++ * 2, value); });
// }
