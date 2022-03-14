#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLE_H

#include <iostream>
#include <memory>

#include "InternalQueryable.hpp"

#include "SelectBuilders/SelectBuilder.hpp"
#include "SelectBuilders/DequeSelectBuilder.hpp"
#include "SelectBuilders/ListSelectBuilder.hpp"
#include "SelectBuilders/MultiSetSelectBuilder.hpp"
#include "SelectBuilders/SetSelectBuilder.hpp"
#include "SelectBuilders/VectorSelectBuilder.hpp"
#include "Utilities/Casting.hpp"

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class Queryable
{
protected:
  std::shared_ptr<InternalQueryable<TObj, TIterable, TArgs...>> queryable;
public:

  Queryable() { }
  Queryable(Queryable<TObj, TIterable, TArgs...> && other)
    : queryable(std::move(other.queryable))
  {
  }
  Queryable(const Queryable<TObj, TIterable, TArgs...> & other)
    : queryable(other.queryable)
  {
  }
  Queryable(std::shared_ptr<InternalQueryable<TObj, TIterable, TArgs...>> && other)
    : queryable(std::move(other))
  {
  }

  // I don't like having all of these constructors, but I want this class to be movable so that
  // methods like 'Select' can return a new insance without making a copy
  Queryable(const DequeInternalQueryable<TObj, TArgs...> && other)
  {
    queryable = FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, TIterable, TArgs...>>(
      std::make_shared<DequeInternalQueryable<TObj, TArgs...>>(other));
  }
  Queryable(const ListInternalQueryable<TObj, TArgs...> && other)
  {
    queryable = FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, TIterable, TArgs...>>(
      std::make_shared<ListInternalQueryable<TObj, TArgs...>>(other));
  }
  Queryable(const MultiSetInternalQueryable<TObj, TArgs...> && other)
  {
    queryable = FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, TIterable, TArgs...>>(
      std::make_shared<MultiSetInternalQueryable<TObj, TArgs...>>(other));
  }
  Queryable(const SetInternalQueryable<TObj, TArgs...> && other)
  {
    queryable = FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, TIterable, TArgs...>>(
      std::make_shared<SetInternalQueryable<TObj, TArgs...>>(other));
  }
  Queryable(const VectorInternalQueryable<TObj, TArgs...> && other)
  {
    queryable = FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, TIterable, TArgs...>>(
      std::make_shared<VectorInternalQueryable<TObj, TArgs...>>(other));
  }

  Queryable(const std::deque<TObj, TArgs...> & iterable)
  {
    queryable = FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, TIterable, TArgs...>>(
      std::make_shared<DequeInternalQueryable<TObj, TArgs...>>(iterable));
  }
  Queryable(const std::list<TObj, TArgs...> & iterable)
  {
    queryable = FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, TIterable, TArgs...>>(
      std::make_shared<ListInternalQueryable<TObj, TArgs...>>(iterable));
  }
  Queryable(const std::multiset<TObj, TArgs...> & iterable)
  {
    queryable = FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, TIterable, TArgs...>>(
      std::make_shared<MultiSetInternalQueryable<TObj, TArgs...>>(iterable));
  }
  Queryable(const std::set<TObj, TArgs...> & iterable)
  {
    queryable = FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, TIterable, TArgs...>>(
      std::make_shared<SetInternalQueryable<TObj, TArgs...>>(iterable));
  }
  Queryable(const std::vector<TObj, TArgs...> & iterable)
  {
    queryable = FutureStd::reinterpret_pointer_cast<InternalQueryable<TObj, TIterable, TArgs...>>(
      std::make_shared<VectorInternalQueryable<TObj, TArgs...>>(iterable));
  }

  template<typename T, typename ...TNewArgs>
  Queryable<T, TIterable, TNewArgs...> Select(
    std::function<T(TObj)> retrieveValue,
    TNewArgs... iterableParameters)
  {
    // TODO --> this is terribly ugly, find a better way to handle it
    switch (this->queryable->GetType())
    {
      case QueryableType::Deque:
      {
        DequeSelectBuilder<TObj, T, TNewArgs...> selectBuilder;
        this->queryable->Select(
          retrieveValue,
          reinterpret_cast<SelectBuilder<TObj, T, TIterable, TNewArgs...>*>(&selectBuilder),
          iterableParameters...);

        std::shared_ptr<InternalQueryable<T, TIterable, TNewArgs...>> newQueryble(
          FutureStd::reinterpret_pointer_cast<InternalQueryable<T, TIterable, TNewArgs...>>(selectBuilder.Get()));
        // move constructor so no new memory is created
        Queryable<T, TIterable, TNewArgs...> newQueryable(std::move(newQueryble));

        // TODO --> determine if reseting is undesireable
        this->queryable.reset();

        // return uses move constructor so no new memory is created
        return newQueryable;
        break;
      }
      case QueryableType::List:
      {
        ListSelectBuilder<TObj, T, TNewArgs...> selectBuilder;
        this->queryable->Select(
          retrieveValue,
          reinterpret_cast<SelectBuilder<TObj, T, TIterable, TNewArgs...>*>(&selectBuilder),
          iterableParameters...);

        std::shared_ptr<InternalQueryable<T, TIterable, TNewArgs...>> newQueryble(
          FutureStd::reinterpret_pointer_cast<InternalQueryable<T, TIterable, TNewArgs...>>(selectBuilder.Get()));
        // move constructor so no new memory is created
        Queryable<T, TIterable, TNewArgs...> newQueryable(std::move(newQueryble));

        // TODO --> determine if reseting is undesireable
        this->queryable.reset();

        // return uses move constructor so no new memory is created
        return newQueryable;
        break;
      }
      case QueryableType::MultiSet:
      {
        MultiSetSelectBuilder<TObj, T, TNewArgs...> selectBuilder;
        this->queryable->Select(
          retrieveValue,
          reinterpret_cast<SelectBuilder<TObj, T, TIterable, TNewArgs...>*>(&selectBuilder),
          iterableParameters...);

        std::shared_ptr<InternalQueryable<T, TIterable, TNewArgs...>> newQueryble(
          FutureStd::reinterpret_pointer_cast<InternalQueryable<T, TIterable, TNewArgs...>>(selectBuilder.Get()));
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
        SetSelectBuilder<TObj, T, TNewArgs...> selectBuilder;
        this->queryable->Select(
          retrieveValue,
          reinterpret_cast<SelectBuilder<TObj, T, TIterable, TNewArgs...>*>(&selectBuilder),
          iterableParameters...);

        std::shared_ptr<InternalQueryable<T, TIterable, TNewArgs...>> newQueryble(
          FutureStd::reinterpret_pointer_cast<InternalQueryable<T, TIterable, TNewArgs...>>(selectBuilder.Get()));
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
        VectorSelectBuilder<TObj, T, TNewArgs...> selectBuilder;
        this->queryable->Select(
          retrieveValue,
          reinterpret_cast<SelectBuilder<TObj, T, TIterable, TNewArgs...>*>(&selectBuilder),
          iterableParameters...);

        std::shared_ptr<InternalQueryable<T, TIterable, TNewArgs...>> newQueryble(
          FutureStd::reinterpret_pointer_cast<InternalQueryable<T, TIterable, TNewArgs...>>(selectBuilder.Get()));
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
