// #include <gtest/gtest.h>

// #include <array>
// #include <deque>
// #include <exception>
// #include <iostream>
// #include <list>
// #include <set>
// #include <string>
// #include <vector>

// #include "../../../DataStructures/Gender.hpp"
// #include "../../../DataStructures/Person.hpp"
// #include "../../../DataStructures/PersonLibrary.hpp"
// #include "../../../DataStructures/Point.hpp"

// #include "../../../Queryable/QueryBuilder.hpp"


// using namespace QueryBuilder;

// class SumFunctionalTest : public ::testing::Test
// {
// protected:
//   uint expectedSum = 1144;
//   uint expectedNoDupsSum = 1057;
//   QueryableVector<uint> queryable;

//   SumFunctionalTest() :
//     queryable(BuildQueryable2(std::vector<uint>({ 7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 867, 1, 12 })))
//   {
//   }

//   void SetUp() override
//   {
//   }

//   void TearDown() override {}
// };

// TEST_F(SumFunctionalTest, SumUninitialized)
// {
//   QueryableVector<Person> emptyQueryable(BuildQueryable2(std::vector<Person>()));
//   double sum = emptyQueryable.Sum<double>([](Person p) { return p.GetAge(); });
//   ASSERT_EQ(0, sum);
// }

// TEST_F(SumFunctionalTest, SumUninitializedDefault)
// {
//   Point expected(0, 0);
//   QueryableVector<Point> emptyQueryable(BuildQueryable2(std::vector<Point>()));
//   Point sum = emptyQueryable.Sum();
//   ASSERT_EQ(expected.X, sum.X);
//   ASSERT_EQ(expected.Y, sum.Y);
// }

// TEST_F(SumFunctionalTest, SumOperatorOverload)
// {
//   Point expected(20, 10);
//   QueryableVector<Point> points = BuildQueryable2(std::vector<Point>({
//     Point(2, 4),
//     Point(3, 5),
//     Point(7, 1),
//     Point(8, 0)
//   }));

//   Point sum = points.Sum<Point>([](Point point) { return point; });

//   ASSERT_EQ(expected.X, sum.X);
//   ASSERT_EQ(expected.Y, sum.Y);
// }

// TEST_F(SumFunctionalTest, SumVector)
// {
//   uint sum = this->queryable.Sum<uint>([](uint value) { return value; });
//   ASSERT_EQ(this->expectedSum, sum);
// }

// TEST_F(SumFunctionalTest, SumVectorDefault)
// {
//   uint sum = this->queryable.Sum();
//   ASSERT_EQ(this->expectedSum, sum);
// }

// TEST_F(SumFunctionalTest, SumDeque)
// {
//   QueryableDeque<uint> local = BuildQueryable2(this->queryable.ToDeque());
//   uint sum = local.Sum<uint>([](uint value) { return value; });
//   ASSERT_EQ(this->expectedSum, sum);
// }

// TEST_F(SumFunctionalTest, SumDequeDefault)
// {
//   QueryableDeque<uint> local = BuildQueryable2(this->queryable.ToDeque());
//   uint sum = local.Sum();
//   ASSERT_EQ(this->expectedSum, sum);
// }

// TEST_F(SumFunctionalTest, SumList)
// {
//   QueryableList<uint> local = BuildQueryable2(this->queryable.ToList());
//   uint sum = local.Sum<uint>([](uint value) { return value; });
//   ASSERT_EQ(this->expectedSum, sum);
// }

// TEST_F(SumFunctionalTest, SumListDefault)
// {
//   QueryableList<uint> local = BuildQueryable2(this->queryable.ToList());
//   uint sum = local.Sum();
//   ASSERT_EQ(this->expectedSum, sum);
// }

// TEST_F(SumFunctionalTest, SumMultiSet)
// {
//   QueryableMultiSet<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
//   uint sum = local.Sum<uint>([](uint value) { return value; });
//   ASSERT_EQ(this->expectedSum, sum);
// }

// TEST_F(SumFunctionalTest, SumMultiSetDefault)
// {
//   QueryableMultiSet<uint> local = BuildQueryable2(this->queryable.ToMultiSet());
//   uint sum = local.Sum();
//   ASSERT_EQ(this->expectedSum, sum);
// }

// TEST_F(SumFunctionalTest, SumSet)
// {
//   QueryableSet<uint> local = BuildQueryable2(this->queryable.ToSet());
//   uint sum = local.Sum<uint>([](uint value) { return value; });
//   ASSERT_EQ(this->expectedNoDupsSum, sum);
// }

// TEST_F(SumFunctionalTest, SumSetDefault)
// {
//   QueryableSet<uint> local = BuildQueryable2(this->queryable.ToSet());
//   uint sum = local.Sum();
//   ASSERT_EQ(this->expectedNoDupsSum, sum);
// }

// TEST_F(SumFunctionalTest, SumWhere)
// {
//   uint expected = 1110;
//   uint sum = this->queryable
//     .Where([](uint value) { return value > 10; })
//     .Sum<uint>([](uint value) { return value; });
//   ASSERT_EQ(expected, sum);
// }

// TEST_F(SumFunctionalTest, SumWhereDefault)
// {
//   uint expected = 1110;
//   uint sum = this->queryable
//     .Where([](uint value) { return value > 10; })
//     .Sum();
//   ASSERT_EQ(expected, sum);
// }
