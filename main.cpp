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

    //   PersonLibrary personLibrary;
    //   IQueryable<Person> people(BuildQueryable2(personLibrary.GetPeople()));
    ISortedQueryable<size_t, std::set> numbers(BuildQueryable2(std::set<size_t>({7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12})));
    ISortedQueryable<double, std::set> newNumbers = numbers
        // .Where([](size_t value) { return value < 10; })
        .Select<double>([](size_t value) { return ((double)value) / 2.0; });
        // .Sort<std::set>();

    std::cout << "\n\n\n\nAFTER SORT\n\n\n" << std::endl;
    newNumbers.ForEach([](double value) { std::cout << value << ", "; });
    std::cout << std::endl;
    //   bool result = people.Any([](Person person) { return person.GetAge() > 40; });
    //   std::cout << "Anybody over 40: " << (result ? "YES" : "NO") << std::endl;

    // QueryableVectorData<size_t> vectorQueryable(std::vector<size_t>({7, 4, 7, 4, 3, 76, 8, 45, 76, 34, 1, 867, 12}));

    // std::shared_ptr<QueryableData<size_t, std::vector>> queryableData(
    //     FutureStd::reinterpret_pointer_cast<QueryableData<size_t, std::vector>>(
    //         std::make_shared<QueryableVectorData<size_t>>(vectorQueryable)));

    // SortQueryableData<size_t, std::vector> sortQueryable(queryableData);

    // auto first = vectorQueryable.begin();
    // auto last = vectorQueryable.end();
    // std::cout << "pre SWAP" << std::endl;
    // heap_sort(first, last);
    // std::cout << "post SWAP" << std::endl;
    // size_t firstValue = *first;
    // size_t lastValue = *last;
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
    //     size_t temp = *iter;
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
// size_t firstValue = *first;
// size_t lastValue = *last;
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
    // std::vector<size_t> startingInput;
    // std::vector<size_t> evens;
    // VectorInternalQueryable<size_t> queryable;
    // VectorInternalQueryable<size_t> queryableEvens;
    // startingInput = std::vector<size_t>({ 1, 4, 7, 4, 3, 76, 8, 45, 34, 76, 0, 867 });
    // evens = std::vector<size_t>({ 4, 76, 8, 34, 76, 0 });
    //
    // queryable = BuildQueryable(startingInput);
    // queryableEvens = BuildQueryable(evens);
    //
    // // InternalQueryable<size_t, std::vector> * meh = reinterpret_cast<InternalQueryable<size_t, std::vector>*>(&queryable);
    //
    // // std::shared_ptr<InternalQueryable<size_t, std::vector>> ptr = std::make_shared<InternalQueryable<size_t, std::vector>>(*meh);
    // std::multiset<size_t> setItems = queryable.ToMultiSet();
    // MultiSetInternalQueryable<size_t> qSetItems(std::move(setItems));
    // Queryable<size_t, std::multiset> blah(reinterpret_cast<InternalQueryable<size_t, std::multiset>*>(&qSetItems));
    //
    // std::cout << "starting test. set size: " << setItems.size() << std::endl;
    // blah
    //   .Where([](size_t num) { return (num % 2) == 0; })
    //   .Select<std::string>([](size_t num) { return "Number: " + std::to_string(num); })
    //   .ForEach([](std::string str) { std::cout << "STRING REPRESENTATION: " << str << std::endl; });
    // std::cout << "done with select\n\n" << std::endl;

    // std::cout << "attempting foreach" << std::endl;
    // queryable.ForEach([](size_t value) { std::cout << value << ", "; });
    // std::cout << std::endl;

    // ListInternalQueryable<size_t> local = BuildQueryable<size_t>(queryable.ToList());
    // std::cout << "local made\n\n" << std::endl;
    // ListInternalQueryable<size_t> mevens = BuildQueryable<size_t>(queryableEvens.ToList());
    // std::cout << "mevens made\n\n" << std::endl;
    // auto result = local.Where([](size_t value) { return value > 10; });
    // std::vector<size_t> vectorResult = result.ToVector();

    // std::vector<size_t> numbers({ 1, 65, 8, 45, 7, 63, 22, 14, 7, 9 });
    // std::function<bool(size_t)> conditioner = [](size_t value) { return value % 2 == 0; };
    // std::function<double(size_t)> selector = [](size_t value) { return static_cast<double>(value) / 2.0; };
    //
    // InternalQueryable<size_t> local(numbers);
    // local.Where(conditioner).ForEach([](size_t value) { std::cout << "where value: " << value << std::endl; });
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

    // QueryableVectorData<size_t> queryableData(numbers);
    // std::shared_ptr<IQueryableData<size_t>> sharedData = std::make_shared<QueryableVectorData<size_t, double>>(queryableData);
    // IQueryableData<size_t> * dummy = new SelectQueryableVectorData<size_t, double>(sharedData, selector);
    // for (double value : queryableData)
    // {
    //   std::cout << "value as size_t: " << value << std::endl;
    // }
    //
    // WhereQueryableVectorData<size_t> whereQueryableData(&queryableData, conditioner);
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
    // SelectQueryableVectorData<size_t, double> selectQueryableData(&queryableData, selector);
    //
    // for (double value : selectQueryableData)
    // {
    //   std::cout << "halved value as double: " << value << std::endl;
    // }
    //
    // SelectQueryableVectorData<size_t, double> selectWhereQueryableData(&whereQueryableData, selector);
    //
    // for (double value : selectWhereQueryableData)
    // {
    //   std::cout << "halved even value as double: " << value << std::endl;
    // }

    return 0;
}
