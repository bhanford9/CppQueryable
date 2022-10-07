#ifndef CPPQUERYABLE_QUERYABLE_SELECTBUILDERS_MAPSELECTBUILDER_H
#define CPPQUERYABLE_QUERYABLE_SELECTBUILDERS_MAPSELECTBUILDER_H

#include <map>

#include "SelectBuilder.hpp"
#include "../QueryableType.hpp"
#include "../Utilities/Casting.hpp"

template<
  typename TKeyOriginal,
  typename TCurrent,
  typename TValueOriginal,
  typename TLessThan = std::less<TCurrent>,
  typename TAllocator = std::allocator<TCurrent>>
class MapSelectBuilder :
  public SelectBuilder<
    TKeyOriginal,
    TCurrent,
    std::map,
    TOriginal,
    TCurrent,
    TValueOriginal,
    TLessThan,
    TAllocator>
{
public:
  virtual void Build(
    std::shared_ptr<QueryableData<TOriginal, std::map, TLessThan, TAllocator>> & data,
    std::function<TCurrent(TOriginal)> & selector,
    TLessThan lessThan = {},
    TAllocator allocator = {})
  {
    std::shared_ptr<SelectQueryableMapData<TOriginal, TCurrent, TLessThan, TAllocator>> selectData =
      std::make_shared<SelectQueryableMapData<TOriginal, TCurrent, TLessThan, TAllocator>>(data, selector);

    std::shared_ptr<MapInternalQueryable<TCurrent, TLessThan, TAllocator>> mapQueryable =
      std::make_shared<MapInternalQueryable<TCurrent, TLessThan, TAllocator>>(std::move(selectData), QueryableType::Map);

    this->selectedQuery = FutureStd::reinterpret_pointer_cast<InternalQueryable<TCurrent, std::map, TLessThan, TAllocator>>(mapQueryable);
  }
};

#endif
