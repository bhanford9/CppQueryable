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
#include "Queryable/QueryableData/WhereQueryableData/WhereQueryableMapData.hpp"
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

    auto queryable = BuildQueryable(data);

    auto myMap = queryable.ToMap<size_t, std::string>(
        [](size_t value) { return value; },
        [](size_t value) { return "Half Value: " + std::to_string(value / 2.0); });

    for (auto kvp : myMap)
    {
        std::cout << "key: " << kvp.first << ", value: " << kvp.second << std::endl;
    }

    std::cout << "\n\n" << std::endl;

    QueryableMap<size_t, std::string> mapQueryable = BuildQueryable(myMap);

    mapQueryable
        .Select<bool>([&](std::pair<const size_t, std::string> kvp)
        {
            std::cout << "--- kvp first: " << kvp.first << ", result: " << (kvp.first % 2) << std::endl;
            return (kvp.first % 2) == 0;
        })
        .ForEach([&](bool isEven) { std::cout << (isEven ? "EVEN" : "ODD") << std::endl; });

    // I think this may be a problem... To Vector should return std::vector<TIterating>
    BuildQueryable(BuildQueryable(data).ToList())
        .Select<bool>([&](size_t value)
        {
            std::cout << "--- value: " << value << ", result: " << (value % 2) << std::endl;
            return (value % 2) == 0;
        })
        .ForEach([&](bool isEven) { std::cout << (isEven ? "EVEN" : "ODD") << std::endl; });

    // auto result = mapQueryable.Average();

    // std::cout << "\naverage of keys: " << result << std::endl;

    // auto valueResult = mapQueryable.Aggregate<std::string>([&](std::string total, size_t key) { return total += myMap[key] + ",\n"; });

    // std::cout << "\n" << valueResult << std::endl;

    return 0;
}
