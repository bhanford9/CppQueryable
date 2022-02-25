#ifndef CPPQUERYABLE_QUERYABLE_IQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_IQUERYABLEDATA_H

#include <functional>
#include <vector>

#include "../Iterators/QueryableIterator.h"
#include "../Iterators/IIterable.h"
#include "IQueryableIteratorData.h"

template<typename TObj, typename TIterator>
class IQueryableData : public IQueryableIteratorData<TIterator>
{
protected:
  typedef typename std::vector<TObj>::iterator TVectorIterator;


public:
  virtual ~IQueryableData() { }

  virtual void * GetData() = 0;
  virtual void Clear() = 0;
  virtual void Add(TObj obj) = 0;
  virtual int Count() = 0;
  virtual int StorageSize() = 0;
  virtual void Sort(std::function<bool(TObj, TObj)> compare = [](TObj a, TObj b) { return a < b; }) = 0;
  // virtual void Update(QueryableIterator<TIterator, TIterable, TArgs...> first, QueryableIterator<TIterator, TIterable, TArgs...> last, std::function<bool(TObj, TObj)> compare = [](TObj a, TObj b) { return a < b; }) = 0;
};

#endif
