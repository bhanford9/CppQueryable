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
#include "Queryable/IQueryable.hpp"
#include "Queryable/QueryBuilder.hpp"
#include "Queryable/QueryableType.hpp"
#include "Queryable/InternalQueryable.hpp"
#include "Queryable/Queryable.hpp"
#include "DataStructures/People.hpp"
#include "DataStructures/PersonLibrary.hpp"

#include "DataStructures/Base.hpp"
#include "DataStructures/Derived.hpp"
#include "Queryable/QueryableData/QueryableVectorData.hpp"
#include "Queryable/QueryableData/SortQueryableData/SortQueryableData.hpp"

using namespace QueryBuilder;

int main()
{

    //   PersonLibrary personLibrary;
    //   IQueryable<Person> people(BuildQueryable2(personLibrary.GetPeople()));
    IQueryable<uint> numbers(BuildQueryable2(std::vector<uint>({7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12})));
    IQueryable<double> newNumbers = numbers
        // .Where([](uint value) { return value < 10; })
        .Select<std::vector, double>([](uint value) { return ((double)value) / 2.0; })
        .Sort<std::vector>();

    std::cout << "\n\n\n\nAFTER SORT\n\n\n" << std::endl;
    newNumbers.ForEach([](double value) { std::cout << value << ", "; });
    std::cout << std::endl;
    //   bool result = people.Any([](Person person) { return person.GetAge() > 40; });
    //   std::cout << "Anybody over 40: " << (result ? "YES" : "NO") << std::endl;

    // QueryableVectorData<uint> vectorQueryable(std::vector<uint>({7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12}));

    // std::shared_ptr<QueryableData<uint, std::vector>> queryableData(
    //     FutureStd::reinterpret_pointer_cast<QueryableData<uint, std::vector>>(
    //         std::make_shared<QueryableVectorData<uint>>(vectorQueryable)));

    // SortQueryableData<uint, std::vector> sortQueryable(queryableData);

    // auto first = vectorQueryable.begin();
    // auto last = vectorQueryable.end();
    // std::cout << "pre SWAP" << std::endl;
    // heap_sort(first, last);
    // std::cout << "post SWAP" << std::endl;
    // uint firstValue = *first;
    // uint lastValue = *last;
    // std::cout << "\n\n\n\nfirst: " << firstValue << ", last: " << lastValue << std::endl;
    // // std::sort(vectorQueryable.begin(), vectorQueryable.end());
    // for (auto value : vectorQueryable)
    // {
    //     std::cout << value << std::endl;
    // }

    // sortQueryable.Sort();
    // auto firstIter = sortQueryable.begin();
    // auto iter = ++firstIter;
    // auto lastIter = sortQueryable.end();
    // for (; iter != lastIter; ++iter)
    // {
    //     uint temp = *iter;
    //     auto innerIter = std::prev(iter);
    //     while (innerIter >= firstIter && temp <= *innerIter)
    //     {
    //         *std::next(innerIter) = *innerIter;
    //         --innerIter;
    //     }
    //     *std::next(innerIter) = temp;
    // }

    // heap_sort(sortQueryable.begin(), sortQueryable.end());
    //   std::sort(sortQueryable.begin(), sortQueryable.end());

// std::cout << "\n\n\n\n\n\nDone Sorting\n\n\n\n\n"
//             << std::endl;

// auto first = sortQueryable.begin();
// auto last = --sortQueryable.end();
// uint firstValue = *first;
// uint lastValue = *last;
// std::cout << "\n\n\n\nfirst: " << firstValue << ", last: " << lastValue << std::endl;
// //   auto temp = std::move(*first);
// //   *first = std::move(*last);
// //   *last = std::move(temp);

// //   std::iter_swap(first, last);
// //   firstValue = *first;
// //   lastValue = *last;
// //    std::cout << "first: " << firstValue << ", last: " << lastValue << std::endl;

//     for (auto value : sortQueryable)
//     {
//         std::cout << value << std::endl;
//     }

    //
    // std::vector<uint> startingInput;
    // std::vector<uint> evens;
    // VectorInternalQueryable<uint> queryable;
    // VectorInternalQueryable<uint> queryableEvens;
    // startingInput = std::vector<uint>({ 1, 4, 7, 4, 3, 76, 8, 45, 34, 76, 0, 867 });
    // evens = std::vector<uint>({ 4, 76, 8, 34, 76, 0 });
    //
    // queryable = BuildQueryable(startingInput);
    // queryableEvens = BuildQueryable(evens);
    //
    // // InternalQueryable<uint, std::vector> * meh = reinterpret_cast<InternalQueryable<uint, std::vector>*>(&queryable);
    //
    // // std::shared_ptr<InternalQueryable<uint, std::vector>> ptr = std::make_shared<InternalQueryable<uint, std::vector>>(*meh);
    // std::multiset<uint> setItems = queryable.ToMultiSet();
    // MultiSetInternalQueryable<uint> qSetItems(std::move(setItems));
    // Queryable<uint, std::multiset> blah(reinterpret_cast<InternalQueryable<uint, std::multiset>*>(&qSetItems));
    //
    // std::cout << "starting test. set size: " << setItems.size() << std::endl;
    // blah
    //   .Where([](uint num) { return (num % 2) == 0; })
    //   .Select<std::string>([](uint num) { return "Number: " + std::to_string(num); })
    //   .ForEach([](std::string str) { std::cout << "STRING REPRESENTATION: " << str << std::endl; });
    // std::cout << "done with select\n\n" << std::endl;

    // std::cout << "attempting foreach" << std::endl;
    // queryable.ForEach([](uint value) { std::cout << value << ", "; });
    // std::cout << std::endl;

    // ListInternalQueryable<uint> local = BuildQueryable<uint>(queryable.ToList());
    // std::cout << "local made\n\n" << std::endl;
    // ListInternalQueryable<uint> mevens = BuildQueryable<uint>(queryableEvens.ToList());
    // std::cout << "mevens made\n\n" << std::endl;
    // auto result = local.Where([](uint value) { return value > 10; });
    // std::vector<uint> vectorResult = result.ToVector();

    // std::vector<uint> numbers({ 1, 65, 8, 45, 7, 63, 22, 14, 7, 9 });
    // std::function<bool(uint)> conditioner = [](uint value) { return value % 2 == 0; };
    // std::function<double(uint)> selector = [](uint value) { return static_cast<double>(value) / 2.0; };
    //
    // InternalQueryable<uint> local(numbers);
    // local.Where(conditioner).ForEach([](uint value) { std::cout << "where value: " << value << std::endl; });
    // local.Select<double>(selector).ForEach([](double value) { std::cout << "select value: " << value << std::endl; });
    //
    // std::vector<Person> people(PersonLibrary().GetPeople());
    //
    // InternalQueryable<Person> queryablePeople(people);
    // InternalQueryable<std::string> queryableNames = queryablePeople
    //   .Select<std::string>([](Person p) { return p.GetName(); });
    //
    // queryableNames.ForEach([](std::string name) { std::cout << "name: " << name << std::endl; });
    //
    // std::cout << "count: " << queryableNames.Count() << std::endl;
    //
    // queryablePeople.Count();

    // QueryableVectorData<uint> queryableData(numbers);
    // std::shared_ptr<IQueryableData<uint>> sharedData = std::make_shared<QueryableVectorData<uint, double>>(queryableData);
    // IQueryableData<uint> * dummy = new SelectQueryableVectorData<uint, double>(sharedData, selector);
    // for (double value : queryableData)
    // {
    //   std::cout << "value as uint: " << value << std::endl;
    // }
    //
    // WhereQueryableVectorData<uint> whereQueryableData(&queryableData, conditioner);
    //
    // int count = 0;
    //
    // for (double value : whereQueryableData)
    // {
    //   if (++count > 12)
    //   break;
    //   std::cout << "even value: " << value << std::endl;
    // }
    //
    // SelectQueryableVectorData<uint, double> selectQueryableData(&queryableData, selector);
    //
    // for (double value : selectQueryableData)
    // {
    //   std::cout << "halved value as double: " << value << std::endl;
    // }
    //
    // SelectQueryableVectorData<uint, double> selectWhereQueryableData(&whereQueryableData, selector);
    //
    // for (double value : selectWhereQueryableData)
    // {
    //   std::cout << "halved even value as double: " << value << std::endl;
    // }

    return 0;
}
