#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEDATA_GROUPQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEDATA_GROUPQUERYABLEDATA_H

#include <functional>
#include <iostream>
#include <memory>

#include "../../QueryableType.h"
#include "../../Utilities/IGroup.h"
#include "../IQueryableData.h"
#include "../QueryableData.h"

template<
  typename TKey,
  typename TData,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class GroupQueryableData : public QueryableData<TData, TIterable, TArgs...>//, public IGroup<TKey, TData>
{
protected:
  TKey key;
  QueryableType type = QueryableType::Default;
  std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; };

public:
  // virtual IQueryableData<TData> * GetData() override
  // {
  //   std::cout << "within group queryable data get data method but shouldn't be" << std::endl;
  //   return this;
  // }

  GroupQueryableData(
    TKey key,
    QueryableType type,
    std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; })
    : QueryableData<TData, TIterable, TArgs...>()
  {
    std::cout << "group queryable data constructor" << std::endl;
    this->key = key;
    this->type = type;
    this->keyCompare = keyCompare;
  }

  GroupQueryableData(
    TKey key,
    std::shared_ptr<IQueryableData<TData>> data,
    QueryableType type,
    std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; })
    : QueryableData<TData, TIterable, TArgs...>(std::move(data))
  {
    this->key = key;
    this->type = type;
    this->keyCompare = keyCompare;
  }

  GroupQueryableData(const GroupQueryableData<TData, TKey, TIterable, TArgs...> & data)
    : QueryableData<TData, TIterable, TArgs...>(data)
  {
    this->key = data.key;
    this->type = data.type;
    this->keyCompare = data.keyCompare;
  }

  virtual ~GroupQueryableData() { }

  // QueryableType GetType() const override
  // {
  //   return this->type;
  // }
  //
  // TKey GetKey() const override
  // {
  //   return this->key;
  // }
  //
  // bool HasKey(TKey key) const override
  // {
  //   return !(this->keyCompare(this->key, key) || this->keyCompare(key, this->key));
  // }
  //
  // bool operator<(const IGroup<TKey, TData> & other) const override
  // {
  //   return this->keyCompare(this->key, other.GetKey());
  // }
};

#endif
