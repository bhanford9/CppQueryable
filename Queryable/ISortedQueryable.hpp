#ifndef CPPQUERYABLE_QUERYABLE_ISORTEDQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_ISORTEDQUERYABLE_H

#include <deque>
#include <functional>
#include <list>
#include <memory>
#include <set>
#include <vector>

#include "IBaseQueryable.hpp"
#include "Queryable.hpp"
#include "QueryableType.hpp"
#include "Utilities/StaticBuilders/QueryableStaticBuilder.hpp"

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class Queryable;


template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class IBaseQueryable;

// TODO --> if we template the allocator and less instead of using TArgs, we may be able to do more with less
//   for example, GroupBy currently requires an allocator be passed in to account for TArgs...
template<
  typename T,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class ISortedQueryable : public IBaseQueryable<T, TIterable, TArgs...>
{
public:
  ISortedQueryable() : IBaseQueryable<T, TIterable, TArgs...>() { }
  ISortedQueryable(const std::shared_ptr<Queryable<T, TIterable, TArgs...>> & other) :
    IBaseQueryable<T, TIterable, TArgs...>(other)
  {
  }
  ISortedQueryable(std::shared_ptr<Queryable<T, TIterable, TArgs...>> && other) :
    IBaseQueryable<T, TIterable, TArgs...>(std::move(other))
  {
  }
  ISortedQueryable(Queryable<T, TIterable, TArgs...> * other) :
    IBaseQueryable<T, TIterable, TArgs...>(other)
  {
  }
  ISortedQueryable(const ISortedQueryable<T, TIterable, TArgs...> & other) :
    IBaseQueryable<T, TIterable, TArgs...>(other.queryable)
  {
  }
  ISortedQueryable(ISortedQueryable<T, TIterable, TArgs...> && other) :
    IBaseQueryable<T, TIterable, TArgs...>(std::move(other.queryable))
  {
  }

  void operator=(const ISortedQueryable<T, TIterable, TArgs...> & other)
  {
    this->queryable = other.queryable;
  }

  void operator=(ISortedQueryable<T, TIterable, TArgs...> && other)
  {
    this->queryable = std::move(other.queryable);
  }

  template<
    template<typename, typename ...> typename TExceptions,
    typename TLessThan = std::less<T>,
    typename TAllocator = std::allocator<T>,
    typename ...TExceptionArgs>
  ISortedQueryable<T, TIterable, TArgs...> Except(
    const TExceptions<T, TExceptionArgs...> & exceptions,
    TLessThan lessThan = {},
    TAllocator allocator = {})
  {
    this->queryable->template Except<TExceptions, TLessThan, TAllocator>(exceptions, lessThan, allocator);
    return *this;
  }

  template<typename TKey, typename TAllocator = std::allocator<T>>
  inline ISortedQueryable<
      Grouping<TKey, T, TAllocator>,
      std::set,
      std::less<Grouping<TKey, T, TAllocator>>,
      std::allocator<Grouping<TKey, T, TAllocator>>> GroupBy(
    const std::function<TKey(T)> & getKey,
    std::function<bool(TKey, TKey)> lessThan = [](TKey a, TKey b) { return a < b; },
    TAllocator allocator = {})
  {
    Queryable<
      Grouping<TKey, T, TAllocator>,
      std::set,
      std::less<Grouping<TKey, T, TAllocator>>,
      std::allocator<Grouping<TKey, T, TAllocator>>> result =
      this->queryable->template GroupBy(getKey, lessThan, allocator);
    
    ISortedQueryable<
        Grouping<TKey, T, TAllocator>,
        std::set,
        std::less<Grouping<TKey, T, TAllocator>>,
        std::allocator<Grouping<TKey, T, TAllocator>>> output(
      std::make_shared<Queryable<
        Grouping<TKey, T, TAllocator>,
        std::set,
        std::less<Grouping<TKey, T, TAllocator>>,
        std::allocator<Grouping<TKey, T, TAllocator>>>>
      (result));
    return output;
  }

  template<
    typename TOut,
    typename ...TNewArgs>
  ISortedQueryable<TOut, TIterable, TNewArgs...> Select(
    std::function<TOut(T)> retrieveValue,
    TNewArgs... iterableParameters)
  {
    Queryable<TOut, TIterable, TNewArgs...> result =
      this->queryable->template Select<TOut, TNewArgs...>(
        retrieveValue,
        iterableParameters...);

    ISortedQueryable<TOut, TIterable, TNewArgs...> output(std::make_shared<Queryable<TOut, TIterable, TNewArgs...>>(result));
    return output;
  }

  template<
    typename TLessThan = std::less<T>,
    typename TAllocator = std::allocator<T>>
  ISortedQueryable<T, TIterable, TLessThan, TAllocator> Sort(TLessThan lessThan = {})
  {
    switch (this->queryable->GetType())
    {
      case QueryableType::MultiSet:
      {
        ISortedQueryable<T, std::multiset, TLessThan, TAllocator> newMultiSet(
          std::make_shared<Queryable<T, std::multiset, TLessThan, TAllocator>>(
            Builders::FromMultiSet(
              this->queryable->ToMultiSet(
                lessThan,
                this->queryable->template GetAllocator<std::multiset, TAllocator>()))));
        return newMultiSet;
      }
      case QueryableType::Set:
      {
        ISortedQueryable<T, std::set, TLessThan, TAllocator> newSet(
          std::make_shared<Queryable<T, std::set, TLessThan, TAllocator>>(
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

  inline ISortedQueryable<T, TIterable, TArgs...> Where(std::function<bool(const T &)> condition)
  {
    this->queryable->Where(condition);
    return *this;
  }
};

#endif
