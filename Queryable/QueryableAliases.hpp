#ifndef CPPQUERYABLE_QUERYABLE_QUERYBLEALIASES_H
#define CPPQUERYABLE_QUERYABLE_QUERYBLEALIASES_H

#include <deque>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <vector>

#include "Queryable.hpp"

template<
  typename TObj,
  typename ...TArgs>
using QueryableDeque = Queryable<TObj, std::deque, TArgs...>;

template<
  typename TObj,
  typename ...TArgs>
using QueryableList = Queryable<TObj, std::list, TArgs...>;

template<
  typename TKey,
  typename TValue,
  typename ...TArgs>
using QueryableMap = Queryable<TKey, std::map, TValue, TArgs...>;

template<
  typename TObj,
  typename ...TArgs>
using QueryableMultiSet = Queryable<TObj, std::multiset, TArgs...>;

template<
  typename TObj,
  typename ...TArgs>
using QueryableSet = Queryable<TObj, std::set, TArgs...>;

template<
  typename TObj,
  typename ...TArgs>
using QueryableVector = Queryable<TObj, std::vector, TArgs...>;

#endif
