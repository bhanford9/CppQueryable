// #ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEDATA_SORTEDGROUPQUERYABLEDATA_H
// #define CPPQUERYABLE_QUERYABLE_QUERYABLEDATA_SORTEDGROUPQUERYABLEDATA_H
//
// #include <algorithm>
// #include <functional>
// #include <iostream>
// #include <memory>
//
// #include "../../QueryableType.hpp"
// #include "../QueryableData.hpp"
// #include "GroupQueryableData.hpp"
//
// template<
//   typename TKey,
//   typename TData,
//   template<typename, typename ...> typename TIterable,
//   typename ...TArgs>
// class SortedGroupQueryableData : public GroupQueryableData<TKey, TData, TIterable, std::function<bool(TData, TData)>, TArgs...>
// {
// protected:
//   typedef typename std::vector<TData>::iterator TVectorIterator;
//
//   std::function<bool(TData, TData)> comparator = [](TData a, TData b) { return a < b; };
//
// public:
//
//   SortedGroupQueryableData(
//     TKey key,
//     QueryableType type,
//     std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; },
//     std::function<bool(TData, TData)> compare = [](TData a, TData b) { return a < b; })
//     : GroupQueryableData<TKey, TData, TIterable, std::function<bool(TData, TData)>, TArgs...>(key, type, keyCompare)
//   {
//     this->comparator = compare;
//     this->comparator(TData(), TData());
//
//     this->items = TIterable<TData, std::function<bool(TData, TData)>, TArgs...>(compare);
//   }
//
//   SortedGroupQueryableData(
//     TKey key,
//     std::shared_ptr<IQueryableData<TData>> data,
//     QueryableType type,
//     std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; },
//     std::function<bool(TData, TData)> compare = [](TData a, TData b) { return a < b; })
//     : GroupQueryableData<TKey, TData, TIterable, std::function<bool(TData, TData)>, TArgs...>(key, std::move(data), type, keyCompare)
//   {
//     this->comparator = compare;
//   }
//
//   SortedGroupQueryableData(const SortedGroupQueryableData<TData, TKey, TIterable, TArgs...> & data)
//     : GroupQueryableData<TKey, TData, TIterable, std::function<bool(TData, TData)>, TArgs...>(data)
//   {
//     this->comparator = data.comparator;
//   }
//
//   SortedGroupQueryableData(
//     TKey key,
//     TVectorIterator first,
//     TVectorIterator last,
//     QueryableType type,
//     std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; },
//     std::function<bool(TData, TData)> compare = [](TData a, TData b) { return a < b; })
//   {
//     // TODO SFINAE require this constructor
//     this->key = key;
//     this->type = type;
//     this->keyCompare = keyCompare;
//     this->comparator = compare;
//     this->items = TIterable<TData, std::function<bool(TData, TData)>>(first, last, this->comparator);
//     this->size = this->items.size();
//   }
//
//   virtual ~SortedGroupQueryableData() { }
//
//   // virtual void Update(QueryableIterator<TData> first, QueryableIterator<TData> last, std::function<bool(TData, TData)> compare) override
//   // {
//   //   // TODO SFINAE require this constructor
//   //   this->comparator = compare;
//   //   this->items = TIterable<TData, std::function<bool(TData, TData)>>(first, last, compare);
//   //   this->size = this->items.size();
//   // }
//   //
//   // virtual void Update(TVectorIterator first, TVectorIterator last) override
//   // {
//   //   // TODO SFINAE require this constructor
//   //   this->items = TIterable<TData, std::function<bool(TData, TData)>>(first, last, this->comparator);
//   //   this->size = this->items.size();
//   // }
//
//   virtual void Add(TData item) override
//   {
//     this->items.insert(item);
//     this->size++;
//   }
//
//   virtual TData & Get(IteratorType type) override
//   {
//     switch (type)
//     {
//         case IteratorType::BeginForward: { this->value = *this->beginIterator; return this->value; }
//         case IteratorType::EndForward: { this->value = *this->endIterator; return this->value; }
//         case IteratorType::BeginReverse: { this->value = *this->rbeginIterator; return this->value; }
//         case IteratorType::EndReverse: default: { this->value = *this->rendIterator; return this->value; }
//     }
//   }
// };
//
// #endif
