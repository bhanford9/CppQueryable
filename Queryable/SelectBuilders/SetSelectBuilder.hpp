#ifndef CPPQUERYABLE_SELECTBUILDERS_SETSELECTBUILDER_H
#define CPPQUERYABLE_SELECTBUILDERS_SETSELECTBUILDER_H

#include <set>

#include "SelectBuilder.hpp"
#include "../QueryableType.hpp"
#include "../Utilities/Casting.hpp"

template<
  typename TOriginal,
  typename TCurrent,
  typename TLessThan = std::less<TCurrent>,
  typename TAllocator = std::allocator<TCurrent>>
class SetSelectBuilder : public SelectBuilder<TOriginal, TCurrent, std::set, TLessThan, TAllocator>
{
public:
  virtual void Build(
    std::shared_ptr<QueryableData<TOriginal, std::set, TLessThan, TAllocator>> & data,
    std::function<TCurrent(TOriginal)> & selector,
    TLessThan lessThan = {},
    TAllocator allocator = {})
  {
    std::shared_ptr<SelectQueryableSetData<TOriginal, TCurrent, TLessThan, TAllocator>> selectData =
      std::make_shared<SelectQueryableSetData<TOriginal, TCurrent, TLessThan, TAllocator>>(std::move(data), selector);

    std::shared_ptr<SetQueryable<TCurrent, TLessThan, TAllocator>> setQueryable =
      std::make_shared<SetQueryable<TCurrent, TLessThan, TAllocator>>(std::move(selectData), QueryableType::Set);

    this->selectedQuery = FutureStd::reinterpret_pointer_cast<Queryable<TCurrent, std::set, TLessThan, TAllocator>>(setQueryable);
  }
};

#endif
