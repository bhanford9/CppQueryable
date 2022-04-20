#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLETYPECONVERTERS_QUERYABLETYPECONVERTER_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLETYPECONVERTERS_QUERYABLETYPECONVERTER_H

#include <memory>
#include "../InternalQueryable.hpp"
#include "../Iterators/QueryableIterator.hpp"

template<
  typename TSourceObj,
  typename TDestObj,
  template<typename, typename...> typename TDestIterable,
  typename ...TDestArgs>
class QueryableTypeConverter
{
public:
  virtual std::shared_ptr<InternalQueryable<TDestObj, TDestIterable, TDestArgs...>> Convert(
    QueryableIterator<TSourceObj> first,
    QueryableIterator<TSourceObj> last,
    TDestArgs... args) const = 0;
};

#endif
