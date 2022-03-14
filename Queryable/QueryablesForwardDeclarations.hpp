#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLESFORWARDDECLARATIONS_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLESFORWARDDECLARATIONS_H

#include <memory>

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename TLessThan = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
class SortedInternalQueryable;

template<
  typename TObj,
  typename TAllocator = std::allocator<TObj>>
class DequeInternalQueryable;

template<
  typename TObj,
  typename TAllocator = std::allocator<TObj>>
class ListInternalQueryable;

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
