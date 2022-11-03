#ifndef CPPQUERYABLE_QUERYABLE_ISORTEDQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_ISORTEDQUERYABLE_H

#include <functional>
#include <memory>
#include <set>

#include "IBaseQueryable.hpp"
#include "QueryableType.hpp"
#include "Utilities/StaticBuilders/QueryableStaticBuilder.hpp"

template<
  typename TStoring,
  template<typename, typename ...> class TIterable,
  typename TIterating,
  typename ...TArgs>
class Queryable;

template<
  typename TStoring,
  template<typename, typename ...> class TIterable,
  typename TIterating,
  typename ...TArgs>
class IBaseQueryable;

// TODO --> if we template the allocator and less instead of using TArgs, we may be able to do more with less
//   for example, GroupBy currently requires an allocator be passed in to account for TArgs...
//
// TODO --> investigate compile time recursive handling of variadic template parameters to make the interface level
//   methods nicer and possibly get rid of the need to return Queryables as ISortedQueryables.
//  - https://stackoverflow.com/questions/18985898/performance-impact-of-variadic-templates
//  - https://stackoverflow.com/questions/15204649/passing-position-of-variadic-template-argument/15204752#15204752

template<
  typename TStoring,
  template<typename, typename ...> class TIterable,
  typename TIterating,
  typename ...TArgs>
class ISortedQueryable : public IBaseQueryable<TStoring, TIterable, TIterating, TArgs...>
{
public:
  ISortedQueryable() : IBaseQueryable<TStoring, TIterable, TIterating, TArgs...>() { }
  ISortedQueryable(const std::shared_ptr<Queryable<TStoring, TIterable, TIterating, TArgs...>> & other) :
    IBaseQueryable<TStoring, TIterable, TIterating, TArgs...>(other)
  {
  }
  ISortedQueryable(std::shared_ptr<Queryable<TStoring, TIterable, TIterating, TArgs...>> && other) :
    IBaseQueryable<TStoring, TIterable, TIterating, TArgs...>(std::move(other))
  {
  }
  ISortedQueryable(Queryable<TStoring, TIterable, TIterating, TArgs...> * other) :
    IBaseQueryable<TStoring, TIterable, TIterating, TArgs...>(other)
  {
  }
  ISortedQueryable(const ISortedQueryable<TStoring, TIterable, TIterating, TArgs...> & other) :
    IBaseQueryable<TStoring, TIterable, TIterating, TArgs...>(other.queryable)
  {
  }
  ISortedQueryable(ISortedQueryable<TStoring, TIterable, TIterating, TArgs...> && other) :
    IBaseQueryable<TStoring, TIterable, TIterating, TArgs...>(std::move(other.queryable))
  {
  }

  void operator=(const ISortedQueryable<TStoring, TIterable, TIterating, TArgs...> & other)
  {
    this->queryable = other.queryable;
  }

  void operator=(ISortedQueryable<TStoring, TIterable, TIterating, TArgs...> && other)
  {
    this->queryable = std::move(other.queryable);
  }

  template<
    template<typename, typename ...> class TExceptions,
    typename TLessThan = std::less<TStoring>,
    typename TAllocator = std::allocator<TStoring>,
    typename ...TExceptionArgs>
  ISortedQueryable<TStoring, TIterable, TIterating, TArgs...> Except(
    const TExceptions<TStoring, TExceptionArgs...> & exceptions,
    TLessThan lessThan = {},
    TAllocator allocator = {})
  {
    this->queryable->template Except<TExceptions, TLessThan, TAllocator>(exceptions, lessThan, allocator);
    return *this;
  }

  template<typename TKey, typename TAllocator = std::allocator<TStoring>>
  ISortedQueryable<
      Grouping<TKey, TStoring, TAllocator>,
      std::set,
      TIterating,
      std::less<Grouping<TKey, TStoring, TAllocator>>,
      std::allocator<Grouping<TKey, TStoring, TAllocator>>> GroupBy(
    const std::function<TKey(TIterating)> & getKey,
    std::function<bool(TKey, TKey)> lessThan = [](TKey a, TKey b) { return a < b; },
    TAllocator allocator = {})
  {
    Queryable<
      Grouping<TKey, TStoring, TAllocator>,
      std::set,
      TIterating,
      std::less<Grouping<TKey, TStoring, TAllocator>>,
      std::allocator<Grouping<TKey, TStoring, TAllocator>>> result =
      this->queryable->template GroupBy(getKey, lessThan, allocator);
    
    ISortedQueryable<
        Grouping<TKey, TStoring, TAllocator>,
        std::set,
        TIterating,
        std::less<Grouping<TKey, TStoring, TAllocator>>,
        std::allocator<Grouping<TKey, TStoring, TAllocator>>> output(
      std::make_shared<Queryable<
        Grouping<TKey, TStoring, TAllocator>,
        std::set,
        TIterating,
        std::less<Grouping<TKey, TStoring, TAllocator>>,
        std::allocator<Grouping<TKey, TStoring, TAllocator>>>>
      (result));
    return output;
  }

  template<
    typename TOut,
    typename ...TNewArgs>
  ISortedQueryable<TOut, TIterable, TNewArgs...> Select(
    std::function<TOut(TIterating)> retrieveValue,
    TNewArgs... iterableParameters)
  {
    Queryable<TOut, TIterable, TIterating, TNewArgs...> result =
      this->queryable->template Select<TOut, TNewArgs...>(
        retrieveValue,
        iterableParameters...);

    ISortedQueryable<TOut, TIterable, TIterating, TNewArgs...> output(
      std::make_shared<Queryable<TOut, TIterable, TIterating, TNewArgs...>>(result));
    return output;
  }

  template<
    typename TLessThan = std::less<TStoring>,
    typename TAllocator = std::allocator<TStoring>>
  ISortedQueryable<TStoring, TIterable, TIterating, TLessThan, TAllocator> Sort(TLessThan lessThan = {})
  {
    switch (this->queryable->GetType())
    {
      case QueryableType::MultiSet:
      {
        ISortedQueryable<TStoring, std::multiset, TIterating, TLessThan, TAllocator> newMultiSet(
          std::make_shared<Queryable<TStoring, std::multiset, TIterating, TLessThan, TAllocator>>(
            Builders::FromMultiSet(
              this->queryable->ToMultiSet(
                lessThan,
                this->queryable->template GetAllocator<std::multiset, TAllocator>()))));
        return newMultiSet;
      }
      case QueryableType::Set:
      {
        ISortedQueryable<TStoring, std::set, TIterating, TLessThan, TAllocator> newSet(
          std::make_shared<Queryable<TStoring, std::set, TIterating, TLessThan, TAllocator>>(
            Builders::FromSet(
              this->queryable->ToSet(
                lessThan,
                this->queryable->template GetAllocator<std::set, TAllocator>()))));
        return newSet;
      }
      default:
        throw; // TODO
    }
  }

  ISortedQueryable<TStoring, TIterable, TIterating, TArgs...> Where(std::function<bool(const TIterating &)> condition)
  {
    this->queryable->Where(condition);
    return *this;
  }
};

#endif
