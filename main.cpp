#include <cstdint>
#include <functional>
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "Queryable/InternalQueryables/VectorInternalQueryable.hpp"
#include "Queryable/QueryableData/IQueryableData.hpp"
// #include "Queryable/QueryableData/SelectQueryableData/SelectQueryableData.hpp"
// #include "Queryable/QueryableData/SelectQueryableData/SelectQueryableVectorData.hpp"
// #include "Queryable/QueryableData/WhereQueryableData/WhereQueryableData.hpp"
// #include "Queryable/QueryableData/WhereQueryableData/WhereQueryableVectorData.hpp"
#include "Queryable/QueryableData/QueryableData.hpp"
// #include "Queryable/IQueryable.hpp"
#include "Queryable/ISortedQueryable.hpp"
#include "Queryable/QueryBuilder.hpp"
#include "Queryable/QueryableType.hpp"
#include "Queryable/InternalQueryable.hpp"
#include "Queryable/Queryable.hpp"
#include "DataStructures/People.hpp"
#include "DataStructures/PersonLibrary.hpp"

#include "DataStructures/Base.hpp"
#include "DataStructures/Derived.hpp"
#include "Queryable/QueryableData/QueryableVectorData.hpp"

using namespace QueryBuilder;

int main()
{
    auto data = std::vector<size_t>({7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12});

    auto queryable = BuildQueryable2(data);

    auto myMap = queryable.ToMap<size_t, std::string>(
        [](size_t value) { return value; },
        [](size_t value) { return "Half Value: " + std::to_string(value / 2.0); });

    for (auto kvp : myMap)
    {
        std::cout << "key: " << kvp.first << ", value: " << kvp.second << std::endl;
    }

    std::cout << "\n\n" << std::endl;

    auto mapQueryable = BuildQueryable2(myMap);

    mapQueryable.ForEach([&](std::pair<const size_t, std::string> kvp) { std::cout << kvp.first << ", value: " << kvp.second << std::endl; });

    // auto result = mapQueryable.Average();

    // std::cout << "\naverage of keys: " << result << std::endl;

    // auto valueResult = mapQueryable.Aggregate<std::string>([&](std::string total, size_t key) { return total += myMap[key] + ",\n"; });

    // std::cout << "\n" << valueResult << std::endl;

    return 0;
}
