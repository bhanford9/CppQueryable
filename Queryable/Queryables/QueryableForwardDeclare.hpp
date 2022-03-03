#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEFORWARDDECLARE_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEFORWARDDECLARE_H

#include <memory>

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename TAllocator = std::allocator<TObj>,
  typename ...TArgs>
class Queryable;

#endif
