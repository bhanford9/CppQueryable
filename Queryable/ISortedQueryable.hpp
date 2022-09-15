#ifndef CPPQUERYABLE_QUERYABLE_ISORTEDQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_ISORTEDQUERYABLE_H

#include <deque>
#include <functional>
#include <list>
#include <memory>
#include <set>
#include <vector>

#include "IBaseQueryable.hpp"
#include "InternalIQueryable.hpp"
#include "Queryable.hpp"
#include "QueryableType.hpp"

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class Queryable;

template<typename T, typename ...TArgs>
class IBaseQueryable;

template<typename T, typename ...TArgs>
class InternalIQueryable;

// TODO --> if we template the allocator and less instead of using TArgs, we may be able to do more with less
//   for example, GroupBy currently requires an allocator be passed in to account for TArgs...
template<typename T, typename ...TArgs>
class ISortedQueryable : public IBaseQueryable<T, TArgs...>
{
public:
  ISortedQueryable() : IBaseQueryable<T, TArgs...>() { }
  ISortedQueryable(const std::shared_ptr<InternalIQueryable<T, TArgs...>> & other) :
    IBaseQueryable<T, TArgs...>(other)
  {
  }
  ISortedQueryable(std::shared_ptr<InternalIQueryable<T, TArgs...>> && other) :
    IBaseQueryable<T, TArgs...>(std::move(other))
  {
  }
  ISortedQueryable(InternalIQueryable<T, TArgs...> * other) :
    IBaseQueryable<T, TArgs...>(other)
  {
  }
  ISortedQueryable(const ISortedQueryable<T, TArgs...> & other) :
    IBaseQueryable<T, TArgs...>(other.queryable)
  {
  }
  ISortedQueryable(ISortedQueryable<T, TArgs...> && other) :
    IBaseQueryable<T, TArgs...>(std::move(other.queryable))
  {
  }

  void operator=(const ISortedQueryable<T, TArgs...> & other)
  {
    this->queryable = other.queryable;
  }

  void operator=(ISortedQueryable<T, TArgs...> && other)
  {
    this->queryable = std::move(other.queryable);
  }

  template<
    template<typename, typename ...> typename TIterable,
    template<typename, typename ...> typename TExceptions,
    typename TLessThan = std::less<T>,
    typename TAllocator = std::allocator<T>,
    typename ...TExceptionArgs>
  ISortedQueryable<T, TArgs...> Except(
    const TExceptions<T, TExceptionArgs...> & exceptions,
    TLessThan lessThan = {},
    TAllocator allocator = {})
  {
    this->queryable->template Except<TIterable, TExceptions, TLessThan, TAllocator>(exceptions, lessThan, allocator);
    return *this;
  }

  template<
    template<typename, typename ...> typename TIterable, 
    typename TKey,
    typename TAllocator = std::allocator<T>>
  inline ISortedQueryable<
      Grouping<TKey, T, TAllocator>,
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
      this->queryable->template GroupBy<TIterable>(getKey, lessThan, allocator);
    
    ISortedQueryable<
        Grouping<TKey, T, TAllocator>,
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
    template<typename, typename ...> typename TIterable,
    typename TOut,
    typename ...TNewArgs>
  ISortedQueryable<TOut, TNewArgs...> Select(
    std::function<TOut(T)> retrieveValue,
    TNewArgs... iterableParameters)
  {
    Queryable<TOut, TIterable, TNewArgs...> result =
      this->queryable->template Select<TIterable, TOut, TNewArgs...>(
        retrieveValue,
        iterableParameters...);

    ISortedQueryable<TOut, TNewArgs...> output(std::make_shared<Queryable<TOut, TIterable, TNewArgs...>>(result));
    return output;
  }

  template<
    template<typename, typename ...> typename TIterable,
    typename TLessThan = std::less<T>,
    typename TAllocator = std::allocator<T>>
  ISortedQueryable<T, TLessThan, TAllocator> Sort(TLessThan lessThan = {})
  {
    switch (this->queryable->GetType())
    {
      case QueryableType::MultiSet:
      {
        ISortedQueryable<T, TLessThan, TAllocator> newMultiSet(
          std::make_shared<Queryable<T, std::multiset, TLessThan, TAllocator>>(
            Queryable<T, std::multiset, TLessThan, TAllocator>::FromMultiSet2(
              this->queryable->ToMultiSet(
                lessThan,
                this->queryable->template GetAllocator<std::multiset, TAllocator>()))));
        return newMultiSet;
      }
      case QueryableType::Set:
      {
        ISortedQueryable<T, TLessThan, TAllocator> newSet(
          std::make_shared<Queryable<T, std::set, TLessThan, TAllocator>>(
            Queryable<T, std::set, TLessThan, TAllocator>::FromSet2(
              this->queryable->ToSet(
                lessThan,
                this->queryable->template GetAllocator<std::set, TAllocator>()))));
        return newSet;
      }
      default:
        throw; // TODO
    }
  }

  inline ISortedQueryable<T, TArgs...> Where(std::function<bool(const T &)> condition)
  {
    this->queryable->Where(condition);
    return *this;
  }
};

#endif
