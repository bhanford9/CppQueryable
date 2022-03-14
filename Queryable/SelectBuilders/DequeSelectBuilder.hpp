#ifndef CPPQUERYABLE_SELECTBUILDERS_DEQUESELECTBUILDER_H
#define CPPQUERYABLE_SELECTBUILDERS_DEQUESELECTBUILDER_H

#include <deque>

#include "SelectBuilder.hpp"
#include "../QueryableType.hpp"
#include "../Utilities/Casting.hpp"

template<
  typename TOriginal,
  typename TCurrent,
  typename TAllocator = std::allocator<TCurrent>>
class DequeSelectBuilder : public SelectBuilder<TOriginal, TCurrent, std::deque, TAllocator>
{
public:
  virtual void Build(
    std::shared_ptr<QueryableData<TOriginal, std::deque, TAllocator>> & data,
    std::function<TCurrent(TOriginal)> & selector,
    TAllocator allocator = {})
  {
    std::shared_ptr<SelectQueryableDequeData<TOriginal, TCurrent, TAllocator>> selectData =
      std::make_shared<SelectQueryableDequeData<TOriginal, TCurrent, TAllocator>>(std::move(data), selector);

    std::shared_ptr<DequeQueryable<TCurrent, TAllocator>> dequeQueryable =
      std::make_shared<DequeQueryable<TCurrent, TAllocator>>(std::move(selectData), QueryableType::Deque);

    this->selectedQuery = FutureStd::reinterpret_pointer_cast<Queryable<TCurrent, std::deque, TAllocator>>(dequeQueryable);
  }
};

#endif
