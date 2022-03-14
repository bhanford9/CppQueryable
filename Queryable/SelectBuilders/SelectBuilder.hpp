#ifndef CPPQUERYABLE_SELECTBUILDERS_SELECTBUILDER_H
#define CPPQUERYABLE_SELECTBUILDERS_SELECTBUILDER_H

#include <functional>
#include <memory>

#include "../Queryable.hpp"

template<
  typename TOriginal,
  typename TCurrent,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class SelectBuilder
{
protected:
  std::shared_ptr<InternalQueryable<TCurrent, TIterable, TArgs...>> selectedQuery;

public:
  virtual void Build(
    std::shared_ptr<QueryableData<TOriginal, TIterable, TArgs...>> & data,
    std::function<TCurrent(TOriginal)> & selector,
    TArgs... iterableArgs) = 0;

  std::shared_ptr<InternalQueryable<TCurrent, TIterable, TArgs...>> Get()
  {
    return this->selectedQuery;
  }
};

#endif
