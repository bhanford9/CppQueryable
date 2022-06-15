#ifndef CPPQUERYABLE_QUERYABLE_SORTQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_SORTQUERYABLEDATA_H

#include <algorithm>
#include <deque>
#include <exception>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <vector>

#include "../IQueryableData.hpp"
#include "../QueryableData.hpp"

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
//   typename TLessThan = std::less<TObj>,
  typename ...TArgs>
class SortQueryableData : public QueryableData<TObj, TIterable, TArgs...>
{
protected:
  std::shared_ptr<IQueryableData<TObj>> original;
//   TLessThan compare;
  bool hasSorted = false;

public:
//   SortQueryableData(
//     std::shared_ptr<QueryableData<TObj, TIterable, TArgs...>> && data,
//     const TLessThan & compare) :
//       original(std::move(data)),
//       compare(compare)
//   {
//     // std::cout << "sort queryable parent data moving" << std::endl;
//     this->size = original->Count();
//   }
//   SortQueryableData(
//     const std::shared_ptr<QueryableData<TObj, TIterable, TArgs...>> & data,
//     const TLessThan & compare) :
//       original(data),
//       compare(compare)
//   {
//     // std::cout << "sort queryable parent data copying" << std::endl;
//     this->size = original->Count();
//   }
//   SortQueryableData(const SortQueryableData<TObj, TIterable, TArgs...> & data) :
//     original(data.original->Clone()),
//     compare(data.compare)
//   {
//     this->size = original->Count();
//   }
  SortQueryableData(std::shared_ptr<QueryableData<TObj, TIterable, TArgs...>> && data) :
      original(std::move(data))
  {
    // std::cout << "sort queryable parent data moving" << std::endl;
    this->size = original->Count();
    // const TObj * beginTemp = &(*this->original->begin());
    // this->beginValue = const_cast<TObj*>(beginTemp);
    // const TObj * endTemp = &(*this->original->end());
    // this->endValue = const_cast<TObj*>(endTemp);
  }
  SortQueryableData(const std::shared_ptr<QueryableData<TObj, TIterable, TArgs...>> & data) :
      original(data)
  {
    // std::cout << "sort queryable parent data copying" << std::endl;
    this->size = original->Count();
    // const TObj * beginTemp = &(*this->original->begin());
    // this->beginValue = const_cast<TObj*>(beginTemp);
    // const TObj * endTemp = &(*this->original->end());
    // this->endValue = const_cast<TObj*>(endTemp);
  }
  SortQueryableData(const SortQueryableData<TObj, TIterable, TArgs...> & data) :
    original(data.original->Clone())
  {
    this->size = original->Count();
    this->original->begin();
    this->original->end();
    // const TObj * beginTemp = &(*this->original->begin());
    // this->beginValue = const_cast<TObj*>(beginTemp);
    // const TObj * endTemp = &(*this->original->end());
    // this->endValue = const_cast<TObj*>(endTemp);
  }

  void Sort()
  {
      std::sort(this->original->begin(), this->original->end());
  }

  virtual ~SortQueryableData() { }

  virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
  {
    // std::cout << "sort clone" << std::endl;
    return std::make_shared<SortQueryableData<TObj, TIterable, TArgs...>>(*this);
  }

  void Add(TObj item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items->push_back(item);
    this->size++;
  }

  // virtual TIterable<TObj, TArgs...> & GetContainer() override
  // {
  //   return {};
  //   // return this->original->GetContainer();
  // }

  virtual bool CanIncrement(IteratorType type) override
  {
    return this->original->CanIncrement(type);
  }

  virtual bool CanDecrement(IteratorType type) override
  {
    return this->original->CanDecrement(type);
  }

  virtual TObj & Get(IteratorType type) override
  {
    std::cout << "Sort Data Get" << std::endl;
    return this->original->Get(type);
    // *this->value = this->original->Get(type);
    // std::cout << "Sort Data Got: " << *this->value << std::endl;
    // return *this->value;
  }

  virtual const TObj & ConstGet(IteratorType type) override
  {
    // std::cout << "Sort Data ConstGet" << std::endl;
    return this->original->ConstGet(type);
    // *this->value = this->original->ConstGet(type);
    // return *this->value;
  }

  virtual IQueryableData<TObj> & Next(IteratorType type, uint64_t & iterated) override
  {
    // std::cout << "Sort Can Increment: " << this->original->CanIncrement(type) << std::endl;
    // std::cout << "Sort Data Next before value: " << this->original->Get(type) << std::endl;
    this->original->Next(type, iterated);
    return *this;
  }

  virtual IQueryableData<TObj> & Prev(IteratorType type, uint64_t & iterated) override
  {
    // std::cout << "Sort Data Prev" << std::endl;
    if (this->CanDecrement(type)) this->original->Prev(type, iterated);
    return *this;
  }

  virtual IQueryableData<TObj> & Add(int addend, IteratorType type) override
  {
    // std::cout << "Sort Data Add" << std::endl;
    this->original->Add(addend, type);
    return *this;
  }

  virtual IQueryableData<TObj> & Subtract(int subtrahend, IteratorType type) override
  {
    // std::cout << "Sort Data Subtract" << std::endl;
    this->original->Add(subtrahend, type);
    return *this;
  }

  virtual QueryableIterator<TObj> begin() override
  {
    // std::cout << "Sort Data begin" << std::endl;
    QueryableIterator<TObj> child = this->original->begin();
    QueryableIterator<TObj> retVal(this->Clone(), child.index, IteratorType::BeginForward);
    return retVal;
  }

  virtual QueryableIterator<TObj> end() override
  {
    // std::cout << "Sort Data end" << std::endl;
    QueryableIterator<TObj> child = this->original->end();
    QueryableIterator<TObj> retVal(this->Clone(), child.index, IteratorType::EndForward);
    return retVal;
  }

  virtual QueryableIterator<TObj> rbegin() override
  {
    QueryableIterator<TObj> child = this->original->rbegin();
    QueryableIterator<TObj> retVal(this->Clone(), child.index, IteratorType::BeginReverse);
    return retVal;
  }

  virtual QueryableIterator<TObj> rend() override
  {
    QueryableIterator<TObj> child = this->original->end();
    QueryableIterator<TObj> retVal(this->Clone(), child.index, IteratorType::EndReverse);
    return retVal;
  }

};

#endif