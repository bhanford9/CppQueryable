#ifndef CPPQUERYABLE_SELECTBUILDERS_VECTORSELECTBUILDER_H
#define CPPQUERYABLE_SELECTBUILDERS_VECTORSELECTBUILDER_H

#include <vector>

#include "SelectBuilder.hpp"
#include "../QueryableType.hpp"
#include "../Utilities/Casting.hpp"

template<
  typename TOriginal,
  typename TCurrent,
  typename TAllocator = std::allocator<TCurrent>>
class VectorSelectBuilder : public SelectBuilder<TOriginal, TCurrent, std::vector, TAllocator>
{
public:
  virtual void Build(
    std::shared_ptr<QueryableData<TOriginal, std::vector, TAllocator>> & data,
    std::function<TCurrent(TOriginal)> & selector,
    TAllocator allocator = {})
  {
    std::cout << "\n\nin builder" << std::endl;
    for (TOriginal orig : *data) std::cout << "orig: " << orig << std::endl;

    std::shared_ptr<SelectQueryableVectorData<TOriginal, TCurrent, TAllocator>> selectData =
      std::make_shared<SelectQueryableVectorData<TOriginal, TCurrent, TAllocator>>(std::move(data), selector);

    std::cout << "\n\ncreated select data" << std::endl;

    std::shared_ptr<VectorQueryable<TCurrent, TAllocator>> vectorQueryable =
      std::make_shared<VectorQueryable<TCurrent, TAllocator>>(std::move(selectData), QueryableType::Vector);

    this->selectedQuery = FutureStd::reinterpret_pointer_cast<Queryable<TCurrent, std::vector, TAllocator>>(vectorQueryable);
  }
};

#endif
