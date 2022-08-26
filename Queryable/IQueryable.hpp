#ifndef CPPQUERYABLE_QUERYABLE_IQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_IQUERYABLE_H

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

template<typename T, typename ...TArgs>
class IQueryable : public IBaseQueryable<T, TArgs...>
{
public:
  IQueryable() : IBaseQueryable<T, TArgs...>() { }
  IQueryable(const std::shared_ptr<InternalIQueryable<T, TArgs...>> & other) :
    IBaseQueryable<T, TArgs...>(other)
  {
  }
  IQueryable(std::shared_ptr<InternalIQueryable<T, TArgs...>> && other) :
    IBaseQueryable<T, TArgs...>(std::move(other))
  {
  }
  IQueryable(InternalIQueryable<T, TArgs...> * other) :
    IBaseQueryable<T, TArgs...>(other)
  {
  }
  IQueryable(const IQueryable<T, TArgs...> & other) :
    IBaseQueryable<T, TArgs...>(other.queryable)
  {
  }
  IQueryable(IQueryable<T, TArgs...> && other) :
    IBaseQueryable<T, TArgs...>(std::move(other.queryable))
  {
  }

  void operator=(const IQueryable<T, TArgs...> & other)
  {
    this->queryable = other.queryable;
  }

  void operator=(IQueryable<T, TArgs...> && other)
  {
    this->queryable = std::move(other.queryable);
  }

  template<
    template<typename, typename ...> typename TIterable,
    template<typename, typename ...> typename TExceptions,
    typename TLessThan = std::less<T>,
    typename TAllocator = std::allocator<T>,
    typename ...TExceptionArgs>
  IQueryable<T, TArgs...> Except(
    const TExceptions<T, TExceptionArgs...> & exceptions,
    TLessThan lessThan = {},
    TAllocator allocator = {})
  {
    this->queryable->template Except<TIterable, TExceptions, TLessThan, TAllocator>(exceptions, lessThan, allocator);
    return *this;
  }

  template<
    template<typename, typename ...> typename TIterable,
    typename TOut,
    typename ...TNewArgs>
  IQueryable<TOut, TNewArgs...> Select(
    std::function<TOut(T)> retrieveValue,
    TNewArgs... iterableParameters)
  {
    Queryable<TOut, TIterable, TNewArgs...> result =
      this->queryable->template Select<TIterable, TOut, TNewArgs...>(
        retrieveValue,
        iterableParameters...);

    IQueryable<TOut, TNewArgs...> output(std::make_shared<Queryable<TOut, TIterable, TNewArgs...>>(result));
    return output;
  }

  template<
    template<typename, typename ...> typename TIterable,
    typename TLessThan = std::less<T>>
  IQueryable<T, TArgs...> Sort(TLessThan lessThan = {})
  {
    this->queryable->template Sort<TIterable, TLessThan>(lessThan);
    return *this;
  }

  inline IQueryable<T, TArgs...> Take(int count)
  {
    this->queryable->Take(count);
    return *this;
  }

  inline IQueryable<T, TArgs...> Where(std::function<bool(const T &)> condition)
  {
    this->queryable->Where(condition);
    return *this;
  }
};

#endif
