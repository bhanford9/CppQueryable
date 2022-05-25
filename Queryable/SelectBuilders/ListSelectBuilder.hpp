#ifndef CPPQUERYABLE_QUERYABLE_SELECTBUILDERS_LISTSELECTBUILDER_H
#define CPPQUERYABLE_QUERYABLE_SELECTBUILDERS_LISTSELECTBUILDER_H

#include <list>

#include "SelectBuilder.hpp"
#include "../QueryableType.hpp"
#include "../Utilities/Casting.hpp"

template<
  typename TOriginal,
  typename TCurrent,
  typename TAllocator = std::allocator<TCurrent>>
class ListSelectBuilder : public SelectBuilder<TOriginal, TCurrent, std::list, TAllocator>
{
public:
  virtual void Build(
    std::shared_ptr<QueryableData<TOriginal, std::list, TAllocator>> & data,
    std::function<TCurrent(TOriginal)> & selector,
    TAllocator allocator = {})
  {
    std::shared_ptr<SelectQueryableListData<TOriginal, TCurrent, TAllocator>> selectData =
      std::make_shared<SelectQueryableListData<TOriginal, TCurrent, TAllocator>>(data, selector);

    std::shared_ptr<ListInternalQueryable<TCurrent, TAllocator>> listQueryable =
      std::make_shared<ListInternalQueryable<TCurrent, TAllocator>>(std::move(selectData), QueryableType::List);

    this->selectedQuery = FutureStd::reinterpret_pointer_cast<InternalQueryable<TCurrent, std::list, TAllocator>>(listQueryable);
  }
};

#endif
