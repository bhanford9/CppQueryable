// #ifndef CPPQUERYABLE_QUERYABLE_QUERYABLERS_VECTORQUERYABLE_H
// #define CPPQUERYABLE_QUERYABLE_QUERYABLERS_VECTORQUERYABLE_H
//
// #include <iostream>
// #include <vector>
//
// #include "../Queryable.hpp"
// #include "../QueryableType.hpp"
// #include "../QueryableData/QueryableVectorData.hpp"
//
// template<
//   typename TObj,
//   typename TAllocator = std::allocator<TObj>>
// class VectorQueryable : public Queryable<TObj, std::vector, TAllocator>
// {
// public:
//   VectorQueryable()
//   {
//     this->queryable = std::make_shared<VectorInternalQueryable<TObj, TAllocator>>();
//   }
//   virtual ~VectorQueryable() { }
//
//   VectorQueryable(const QueryableVector<TObj, TAllocator> & other)
//     : Queryable<TObj, std::vector, TAllocator>(other)
//   {
//   }
//
//   VectorQueryable(Queryable<TObj, std::vector, TAllocator> && other)
//     : Queryable<TObj, std::vector, TAllocator>(std::move(other))
//   {
//   }
//
//   VectorQueryable(const Queryable<TObj, std::vector, TAllocator> & other)
//     : Queryable<TObj, std::vector, TAllocator>(other)
//   {
//   }
//
//   VectorQueryable(VectorInternalQueryable<TObj, TAllocator> && other)
//     : Queryable<TObj, std::vector, TAllocator>(std::move(other))
//   {
//   }
//
//   VectorQueryable(const std::vector<TObj, TAllocator> & iterable)
//   {
//     this->queryable = std::make_shared<VectorInternalQueryable<TObj, TAllocator>>(iterable);
//   }
//
//   VectorQueryable(const std::vector<TObj, TAllocator> && iterable)
//   {
//     this->queryable = std::make_shared<VectorInternalQueryable<TObj, TAllocator>>(std::move(iterable));
//   }
//
//   VectorQueryable & operator=(const QueryableVector<TObj, TAllocator> & other)
//   {
//     this->queryable = other.queryable;
//     return *this;
//   }
// };
//
// #endif
