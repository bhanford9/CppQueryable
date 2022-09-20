#ifndef CPPQUERYABLE_QUERYABLE_IQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_IQUERYABLE_H

#include <deque>
#include <functional>
#include <list>
#include <memory>
#include <set>
#include <vector>

#include "IBaseQueryable.hpp"
#include "Queryable.hpp"
#include "QueryableType.hpp"

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class Queryable;

template<
  typename T,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class IBaseQueryable;

template<
  typename T, 
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class IQueryable : public IBaseQueryable<T, TIterable, TArgs...>
{
public:
  IQueryable() : IBaseQueryable<T, TIterable, TArgs...>() { }
  IQueryable(const std::shared_ptr<Queryable<T, TIterable, TArgs...>> & other) :
    IBaseQueryable<T, TIterable, TArgs...>(other)
  {
  }
  IQueryable(std::shared_ptr<Queryable<T, TIterable, TArgs...>> && other) :
    IBaseQueryable<T, TIterable, TArgs...>(std::move(other))
  {
  }
  IQueryable(Queryable<T, TIterable, TArgs...> * other) :
    IBaseQueryable<T, TIterable, TArgs...>(other)
  {
  }
  IQueryable(const IQueryable<T, TIterable, TArgs...> & other) :
    IBaseQueryable<T, TIterable, TArgs...>(other.queryable)
  {
  }
  IQueryable(IQueryable<T, TIterable, TArgs...> && other) :
    IBaseQueryable<T, TIterable, TArgs...>(std::move(other.queryable))
  {
  }

  void operator=(const IQueryable<T, TIterable, TArgs...> & other)
  {
    this->queryable = other.queryable;
  }

  void operator=(IQueryable<T, TIterable, TArgs...> && other)
  {
    this->queryable = std::move(other.queryable);
  }

  template<
    template<typename, typename ...> typename TExceptions,
    typename TLessThan = std::less<T>,
    typename TAllocator = std::allocator<T>,
    typename ...TExceptionArgs>
  IQueryable<T, TIterable, TArgs...> Except(
    const TExceptions<T, TExceptionArgs...> & exceptions,
    TLessThan lessThan = {},
    TAllocator allocator = {})
  {
    this->queryable->template Except<TExceptions, TLessThan, TAllocator>(exceptions, lessThan, allocator);
    return *this;
  }

  template<
    typename TKey,
    typename TAllocator = std::allocator<T>>
  inline IQueryable<
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
      this->queryable->GroupBy(getKey, lessThan, allocator);
    
    IQueryable<
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
  IQueryable<TOut, TIterable, TNewArgs...> Select(
    std::function<TOut(T)> retrieveValue,
    TNewArgs... iterableParameters)
  {
    Queryable<TOut, TIterable, TNewArgs...> result =
      this->queryable->template Select<TIterable, TOut, TNewArgs...>(
        retrieveValue,
        iterableParameters...);

    IQueryable<TOut, TIterable, TNewArgs...> output(std::make_shared<Queryable<TOut, TIterable, TNewArgs...>>(result));
    return output;
  }

  template<typename TLessThan = std::less<T>>
  IQueryable<T, TIterable, TArgs...> Sort(TLessThan lessThan = {})
  {
    this->queryable->template Sort<TIterable, TLessThan>(lessThan);
    return *this;
  }

  inline IQueryable<T, TIterable, TArgs...> Where(std::function<bool(const T &)> condition)
  {
    this->queryable->Where(condition);
    return *this;
  }
};

#endif
