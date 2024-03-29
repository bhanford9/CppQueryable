#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLESFORWARDDECLARATIONS_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLESFORWARDDECLARATIONS_H

#include <memory>

template<
  typename TObj,
  template<typename, typename ...> class TIterable,
  typename TLessThan = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
class SortedInternalQueryable;

template<
  typename TObj,
  typename TAllocator = std::allocator<TObj>>
class DequeInternalQueryable;

template<
  typename TKey,
  typename TValue,
  typename TValueAllocator = std::allocator<TValue>>
class Grouping;

template<
  typename TObj,
  typename TAllocator = std::allocator<TObj>>
class ListInternalQueryable;

template<
  typename TKey,
  typename TObj,
  typename TLessThan = std::less<TKey>,
  typename TAllocator = std::allocator<std::pair<const TKey, TObj>>>
class MapInternalQueryable;

template<
  typename TObj,
  typename TLessThan = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
class MultiSetInternalQueryable;

template<
  typename TObj,
  typename TLessThan = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
class SetInternalQueryable;

template<
  typename TObj,
  typename TAllocator = std::allocator<TObj>>
class VectorInternalQueryable;

#endif
