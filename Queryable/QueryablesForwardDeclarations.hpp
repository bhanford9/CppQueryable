#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLESFORWARDDECLARATIONS_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLESFORWARDDECLARATIONS_H

#include <memory>

template<
  typename TObj,
  typename TAllocator = std::allocator<TObj>>
class DequeQueryable;

template<
  typename TObj,
  typename TAllocator = std::allocator<TObj>>
class ListQueryable;

template<
  typename TObj,
  typename TLessThan = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
class MultiSetQueryable;

template<
  typename TObj,
  typename TLessThan = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
class SetQueryable;

template<
  typename TObj,
  typename TAllocator = std::allocator<TObj>>
class VectorQueryable;

#endif
