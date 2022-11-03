#ifndef CPPQUERYABLE_QUERYABLE_IQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_IQUERYABLE_H

#include <functional>
#include <memory>
#include <set>

#include "IBaseQueryable.hpp"
#include "Queryable.hpp"

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

template<
  typename TStoring, 
  template<typename, typename ...> class TIterable,
  typename TIterating,
  typename ...TArgs>
class IQueryable : public IBaseQueryable<TStoring, TIterable, TIterating, TArgs...>
{
public:
  IQueryable() : IBaseQueryable<TStoring, TIterable, TIterating, TArgs...>() { }
  IQueryable(const std::shared_ptr<Queryable<TStoring, TIterable, TIterating, TArgs...>> & other) :
    IBaseQueryable<TStoring, TIterable, TIterating, TArgs...>(other)
  {
  }
  IQueryable(std::shared_ptr<Queryable<TStoring, TIterable, TIterating, TArgs...>> && other) :
    IBaseQueryable<TStoring, TIterable, TIterating, TArgs...>(std::move(other))
  {
  }
  IQueryable(Queryable<TStoring, TIterable, TIterating, TArgs...> * other) :
    IBaseQueryable<TStoring, TIterable, TIterating, TArgs...>(other)
  {
  }
  IQueryable(const IQueryable<TStoring, TIterable, TIterating, TArgs...> & other) :
    IBaseQueryable<TStoring, TIterable, TIterating, TArgs...>(other.queryable)
  {
  }
  IQueryable(IQueryable<TStoring, TIterable, TIterating, TArgs...> && other) :
    IBaseQueryable<TStoring, TIterable, TIterating, TArgs...>(std::move(other.queryable))
  {
  }

  void operator=(const IQueryable<TStoring, TIterable, TIterating, TArgs...> & other)
  {
    this->queryable = other.queryable;
  }

  void operator=(IQueryable<TStoring, TIterable, TIterating, TArgs...> && other)
  {
    this->queryable = std::move(other.queryable);
  }

  template<
    template<typename, typename ...> class TExceptions,
    typename TLessThan = std::less<TStoring>,
    typename TAllocator = std::allocator<TStoring>,
    typename ...TExceptionArgs>
  IQueryable<TStoring, TIterable, TIterating, TArgs...> Except(
    const TExceptions<TStoring, TExceptionArgs...> & exceptions,
    TLessThan lessThan = {},
    TAllocator allocator = {})
  {
    this->queryable->template Except<TExceptions, TLessThan, TAllocator>(exceptions, lessThan, allocator);
    return *this;
  }

  template<
    typename TKey,
    typename TAllocator = std::allocator<TStoring>>
  IQueryable<
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
      this->queryable->GroupBy(getKey, lessThan, allocator);
    
    IQueryable<
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

  // template<
  //   typename TOut,
  //   typename ...TNewArgs>
  // IQueryable<TOut, TIterable, TIterating, TNewArgs...> Select(
  //   std::function<TOut(TIterating)> retrieveValue,
  //   TNewArgs... iterableParameters)
  // {
  //   Queryable<TOut, TIterable, TIterating, TNewArgs...> result =
  //     this->queryable->template Select<TIterable, TOut, TNewArgs...>(
  //       retrieveValue,
  //       iterableParameters...);

  //   IQueryable<TOut, TIterable, TIterating, TNewArgs...> output(
  //     std::make_shared<Queryable<TOut, TIterable, TIterating, TNewArgs...>>(result));
  //   return output;
  // }

  template<typename TLessThan = std::less<TStoring>>
  IQueryable<TStoring, TIterable, TIterating, TArgs...> Sort(TLessThan lessThan = {})
  {
    this->queryable->template Sort<TIterable, TLessThan>(lessThan);
    return *this;
  }

  IQueryable<TStoring, TIterable, TIterating, TArgs...> Where(std::function<bool(const TIterating &)> condition)
  {
    this->queryable->Where(condition);
    return *this;
  }
};

#endif
