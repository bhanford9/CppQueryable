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
    std::shared_ptr<Queryable<T, TIterable, TNewArgs...>> newQueryable;

    switch (this->queryable->GetType())
    {
      case QueryableType::Vector:
      {
        std::cout << "selecting vector" << std::endl;
        VectorSelectBuilder<TObj, T, TNewArgs...> selectBuilder;
        this->queryable->Select(
          retrieveValue,
          reinterpret_cast<SelectBuilder<TObj, T, TIterable, TNewArgs...>*>(&selectBuilder),
          iterableParameters...);
        break;
      }
      default:
        break;
    }

    newQueryable->ForEach([](T val) { std::cout << "value: " << val << std::endl; });

    // move constructor so no new memory is created
    QueryableWrapper<T, TIterable, TNewArgs...> newQueryableWrapper(std::move(newQueryable));

    // TODO --> determine if reseting is undesireable
    this->queryable.reset();

    // return uses move constructor so no new memory is created
    return newQueryable;
  }

};

#endif
