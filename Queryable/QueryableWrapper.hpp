#ifndef CPPQUERYABLE_QUERYABLE_Queryable_H
#define CPPQUERYABLE_QUERYABLE_Queryable_H

#include <iostream>
#include <memory>

#include "Queryable.hpp"

#include "SelectBuilders/SelectBuilder.hpp"
#include "SelectBuilders/DequeSelectBuilder.hpp"
#include "SelectBuilders/SetSelectBuilder.hpp"
#include "SelectBuilders/VectorSelectBuilder.hpp"
#include "Utilities/Casting.hpp"

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class Queryable
{
private:
  std::shared_ptr<InternalQueryable<TObj, TIterable, TArgs...>> queryable;

public:
  Queryable() { }
  Queryable(const std::shared_ptr<InternalQueryable<TObj, TIterable, TArgs...>> && other)
    : queryable(other)
  {
  }
  // Queryable(const InternalQueryable<TObj, TIterable, TArgs...> & other)
  //   : queryable(std::make_shared<InternalQueryable<TObj, TIterable, TArgs...>>(other))
  // {
  // }
  Queryable(const VectorInternalQueryable<TObj, TArgs...> && other)
  {
    std::cout << "vector constructor" << std::endl;
    queryable = FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, TIterable, TArgs...>>(std::make_shared<VectorInternalQueryable<TObj, TArgs...>>(other));
  }
  Queryable(const SetInternalQueryable<TObj, TArgs...> && other)
  {
    std::cout << "set constructor" << std::endl;
    queryable = FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, TIterable, TArgs...>>(std::make_shared<SetInternalQueryable<TObj, TArgs...>>(other));
  }

  template<typename T, typename ...TNewArgs>
  Queryable<T, TIterable, TNewArgs...> Select(
    std::function<T(TObj)> retrieveValue,
    TNewArgs... iterableParameters)
  {

    switch (this->queryable->GetType())
    {
      case QueryableType::Deque:
      {
        std::cout << "type is deque" << std::endl;

        DequeSelectBuilder<TObj, T, TNewArgs...> selectBuilder;
        this->queryable->Select(
          retrieveValue,
          reinterpret_cast<SelectBuilder<TObj, T, TIterable, TNewArgs...>*>(&selectBuilder),
          iterableParameters...);

        std::shared_ptr<InternalQueryable<T, TIterable, TNewArgs...>> newQueryble(FutureStd::reinterpret_pointer_cast<InternalQueryable<T, TIterable, TNewArgs...>>(selectBuilder.Get()));
        // move constructor so no new memory is created
        Queryable<T, TIterable, TNewArgs...> newQueryable(std::move(newQueryble));

        // TODO --> determine if reseting is undesireable
        this->queryable.reset();

        // return uses move constructor so no new memory is created
        return newQueryable;
        break;
      }
      case QueryableType::Set:
      {
        std::cout << "type is set" << std::endl;

        SetSelectBuilder<TObj, T, TNewArgs...> setSelectBuilder;
        this->queryable->Select(
          retrieveValue,
          reinterpret_cast<SelectBuilder<TObj, T, TIterable, TNewArgs...>*>(&setSelectBuilder),
          iterableParameters...);

        std::shared_ptr<InternalQueryable<T, TIterable, TNewArgs...>> newQueryble(FutureStd::reinterpret_pointer_cast<InternalQueryable<T, TIterable, TNewArgs...>>(setSelectBuilder.Get()));
        // move constructor so no new memory is created
        Queryable<T, TIterable, TNewArgs...> newQueryable(std::move(newQueryble));

        // TODO --> determine if reseting is undesireable
        this->queryable.reset();

        // return uses move constructor so no new memory is created
        return newQueryable;
        break;
      }
      case QueryableType::Vector:
      {
        std::cout << "type is vector" << std::endl;

        VectorSelectBuilder<TObj, T, TNewArgs...> selectBuilder;
        this->queryable->Select(
          retrieveValue,
          reinterpret_cast<SelectBuilder<TObj, T, TIterable, TNewArgs...>*>(&selectBuilder),
          iterableParameters...);

        std::shared_ptr<InternalQueryable<T, TIterable, TNewArgs...>> newQueryble(FutureStd::reinterpret_pointer_cast<InternalQueryable<T, TIterable, TNewArgs...>>(selectBuilder.Get()));
        // move constructor so no new memory is created
        Queryable<T, TIterable, TNewArgs...> newQueryable(std::move(newQueryble));

        // TODO --> determine if reseting is undesireable
        this->queryable.reset();

        // return uses move constructor so no new memory is created
        return newQueryable;
        break;
      }
      default:
        break;
    }

    return {};
  }

  inline Queryable<TObj, TIterable, TArgs...> Where(std::function<bool(const TObj &)> condition)
  {
    this->queryable->Where(condition);
    return *this;
  }

  inline void ForEach(std::function<void(TObj)> action)
  {
    this->queryable->ForEach(action);
  }

};

#endif
