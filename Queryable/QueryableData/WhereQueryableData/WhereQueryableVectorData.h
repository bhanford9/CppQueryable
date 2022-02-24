#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEVECTORDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEVECTORDATA_H

#include <iostream>
#include <vector>

#include "../../Utilities/Condition.h"
#include "WhereQueryableData.h"

template<typename TObj>
class WhereQueryableVectorData : public WhereQueryableData<TObj, std::vector>
{
protected:

  inline virtual void Add(std::vector<TObj> items, TObj item) const
  {
    items.push_back(item);
  }

public:
  WhereQueryableVectorData(
    std::shared_ptr<IQueryableData<TObj, TObj>> data,
    std::function<bool(TObj)> condition)
    : WhereQueryableData<TObj, std::vector>(std::move(data), std::move(condition))
  {
    std::cout << "WhereQueryable Vector Data Constructor 1" << std::endl;
  }
  WhereQueryableVectorData(const WhereQueryableVectorData<TObj> & other)
    : WhereQueryableData<TObj, std::vector>(other)
  {
    std::cout << "WhereQueryable Vector Data Constructor 2" << std::endl;
  }

  virtual ~WhereQueryableVectorData() { }

  inline virtual IQueryableIteratorData<TObj> & Add(int addend) override
  {
    std::cout << "[VectorWhere+]" << std::endl;
    switch (this->type)
    {
      case IteratorType::BeginForward: this->beginIterator += addend; break;
      case IteratorType::EndForward: this->endIterator += addend; break;
      case IteratorType::BeginReverse: this->rbeginIterator += addend; break;
      case IteratorType::EndReverse: this->rendIterator += addend; break;
    }

    return *this;
  }

  inline virtual IQueryableIteratorData<TObj> & Subtract(int subtrahend) override
  {
    switch (this->type)
    {
      case IteratorType::BeginForward: this->beginIterator -= subtrahend; break;
      case IteratorType::EndForward: this->endIterator -= subtrahend; break;
      case IteratorType::BeginReverse: this->rbeginIterator -= subtrahend; break;
      case IteratorType::EndReverse: this->rendIterator -= subtrahend; break;
    }

    return *this;
  }

  void Add(TObj item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items.push_back(item);
    this->size++;
  }
};

#endif
