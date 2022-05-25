#ifndef CPPQUERYABLE_QUERYABLE_SELECTBUILDERS_MULTISETSELECTBUILDER_H
#define CPPQUERYABLE_QUERYABLE_SELECTBUILDERS_MULTISETSELECTBUILDER_H

#include <set>

#include "SelectBuilder.hpp"
#include "../QueryableType.hpp"
#include "../Utilities/Casting.hpp"

template<
  typename TOriginal,
  typename TCurrent,
  typename TLessThan = std::less<TCurrent>,
  typename TAllocator = std::allocator<TCurrent>>
class MultiSetSelectBuilder : public SelectBuilder<TOriginal, TCurrent, std::multiset, TLessThan, TAllocator>
{
public:
  virtual void Build(
    std::shared_ptr<QueryableData<TOriginal, std::multiset, TLessThan, TAllocator>> & data,
    std::function<TCurrent(TOriginal)> & selector,
    TLessThan lessThan = {},
    TAllocator allocator = {})
  {
    std::shared_ptr<SelectQueryableMultiSetData<TOriginal, TCurrent, TLessThan, TAllocator>> selectData =
      std::make_shared<SelectQueryableMultiSetData<TOriginal, TCurrent, TLessThan, TAllocator>>(data, selector);

    std::shared_ptr<MultiSetInternalQueryable<TCurrent, TLessThan, TAllocator>> multisetQueryable =
      std::make_shared<MultiSetInternalQueryable<TCurrent, TLessThan, TAllocator>>(std::move(selectData), QueryableType::MultiSet);

    this->selectedQuery = FutureStd::reinterpret_pointer_cast<InternalQueryable<TCurrent, std::multiset, TLessThan, TAllocator>>(multisetQueryable);
  }
};

#endif
