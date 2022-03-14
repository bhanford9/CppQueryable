#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEWRAPPER_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEWRAPPER_H

#include <iostream>
#include <memory>

#include "Queryable.hpp"

#include "SelectBuilders/SelectBuilder.hpp"
#include "SelectBuilders/VectorSelectBuilder.hpp"
#include "Utilities/Casting.hpp"

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class QueryableWrapper
{
private:
  std::shared_ptr<Queryable<TObj, TIterable, TArgs...>> queryable;

public:
  QueryableWrapper() { }
  QueryableWrapper(const std::shared_ptr<Queryable<TObj, TIterable, TArgs...>> && other)
    : queryable(other)
  {
  }
  // QueryableWrapper(const Queryable<TObj, TIterable, TArgs...> & other)
  //   : queryable(std::make_shared<Queryable<TObj, TIterable, TArgs...>>(other))
  // {
  // }
  QueryableWrapper(const VectorQueryable<TObj, TArgs...> && other)
  {
    queryable = FutureStd::reinterpret_pointer_cast<Queryable<TObj, TIterable, TArgs...>>(std::make_shared<VectorQueryable<TObj, TArgs...>>(other));
  }

  template<typename T, typename ...TNewArgs>
  QueryableWrapper<T, TIterable, TNewArgs...> Select(
    std::function<T(TObj)> retrieveValue,
    TNewArgs... iterableParameters)
  {

    switch (this->queryable->GetType())
    {
      case QueryableType::Vector:
      {
        // std::shared_ptr<Queryable<T, TIterable, TNewArgs...>> newQueryable;
        VectorSelectBuilder<TObj, T, TNewArgs...> selectBuilder;
        this->queryable->Select(
          retrieveValue,
          reinterpret_cast<SelectBuilder<TObj, T, TIterable, TNewArgs...>*>(&selectBuilder),
          iterableParameters...);

        std::shared_ptr<Queryable<T, TIterable, TNewArgs...>> newQueryble(FutureStd::reinterpret_pointer_cast<Queryable<T, TIterable, TNewArgs...>>(selectBuilder.Get()));
        // move constructor so no new memory is created
        QueryableWrapper<T, TIterable, TNewArgs...> newQueryableWrapper(std::move(newQueryble));

        // TODO --> determine if reseting is undesireable
        this->queryable.reset();

        // return uses move constructor so no new memory is created
        return newQueryableWrapper;
        break;
      }
      default:
        break;
    }


    return {};
  }

  inline void ForEach(std::function<void(TObj)> action)
  {
    this->queryable->ForEach(action);
  }

};

#endif
