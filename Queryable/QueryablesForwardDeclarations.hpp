#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLESFORWARDDECLARATIONS_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLESFORWARDDECLARATIONS_H

#include <memory>

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename TLessThan = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>,
  typename TObjOut = TObj>
class SortedQueryable;

template<
  typename TObj,
  typename TAllocator = std::allocator<TObj>,
  typename TObjOut = TObj>
class DequeQueryable;

template<
  typename TObj,
  typename TAllocator = std::allocator<TObj>,
  typename TObjOut = TObj>
class ListQueryable;

template<
  typename TObj,
  typename TLessThan = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>,
  typename TObjOut = TObj>
class MultiSetQueryable;

template<
  typename TObj,
  typename TLessThan = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>,
  typename TObjOut = TObj>
class SetQueryable;

template<
  typename TObj,
  typename TAllocator = std::allocator<TObj>,
  typename TObjOut = TObj>
class VectorQueryable;

#endif
