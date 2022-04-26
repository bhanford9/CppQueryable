// #ifndef CPPQUERYABLE_QUERYABLE_QUERYABLERS_DEQUEQUERYABLE_H
// #define CPPQUERYABLE_QUERYABLE_QUERYABLERS_DEQUEQUERYABLE_H
//
// #include <iostream>
// #include <deque>
//
// #include "../Queryable.hpp"
// #include "../QueryableType.hpp"
// #include "../QueryableData/QueryableDequeData.hpp"
//
// template<
//   typename TObj,
//   typename TAllocator = std::allocator<TObj>>
// class DequeQueryable : public Queryable<TObj, std::deque, TAllocator>
// {
// public:
//   DequeQueryable()
//   {
//     this->queryable = std::make_shared<DequeInternalQueryable<TObj, TAllocator>>();
//   }
//   virtual ~DequeQueryable() { }
//
//   DequeQueryable(const DequeInternalQueryable<TObj, TAllocator> && other)
//     : Queryable<TObj, std::deque, TAllocator>(std::move(other))
//   {
//   }
//
//   DequeQueryable(const std::deque<TObj, TAllocator> & iterable)
//   {
//     this->queryable = std::make_shared<DequeInternalQueryable<TObj, TAllocator>>(iterable);
//   }
//
//   DequeQueryable(const std::deque<TObj, TAllocator> && iterable)
//   {
//     this->queryable = std::make_shared<DequeInternalQueryable<TObj, TAllocator>>(std::move(iterable));
//   }
// };
//
// #endif
