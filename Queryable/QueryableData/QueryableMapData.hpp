#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEMAPDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEMAPDATA_H

#include <iostream>
#include <memory>
#include <map>

#include "QueryableData.hpp"

template<
  typename TKey,
  typename TValue,
  typename TCompare = std::less<TKey>,
  typename TAllocator = std::allocator<std::pair<const TKey, TValue>>>
class QueryableMapData :
  public QueryableData<
    TKey,
    std::map,
    std::pair<const TKey, TValue>,
    TValue,
    TCompare,
    TAllocator>
{
  // This whole class is overriding all parent implementations because of the weird typing infrastructure
  //   1. We want to iterate over the collection as std::pair<TKey, TValue>
  //   2. We want to suppy both a key and a value to the add method
  //   3. The inheritance assumes the first templated type is the thing within the collection
  //   4. Alternate option would be to template as <TKey, std::map, TValue, TCompare, TAllocator>
  //      4.1 The inheritance would pick this up correctly for std::map
  //      4.2 The inherited extra methods would expect TKey to be the only value within the collection
  //   5. Alternate option would be to further template into something like <TValue, TIterable, TIterating, ...TArgs>
  //      5.1 The TIterating would be a specialized type that would indicate the type returned by the iterator
  //      5.2 It would probably suffice for it to also indicate the type to be supplied when adding to the collection
  //      5.3 This would be a new required parameter in front of the variable template arguments, so it would change every child template inheritance
  //      5.4 I think this would be the best impl, but I want to see if I can get it into a stable state without changing everything first
  //
  // To get this to work, templated inheritance for map works as the following:
  //   TStoring: TKey
  //   TIterable: std::map
  //   TIterating: std::pair<TKey, TValue>
  //   TArgs: TValue, TCompare, TAllocator
  //
  //   This allows us to inherit IQueryableData with TIterating as its template
  //   This allows QueryableData to create its iterators as TIterable<TKey, TArgs...>::iterator
  //     which then properly rolls out to std::map<TKey, TValue, TCompare, TAllocator>
  //
  // Additionally, the underlying map will be stored as TIterable<TStoring, TArgs...>
  //   which then properly rolls out to std::map<TKey, TValue, TCompare, TAllocator>

  typedef typename std::vector<std::pair<const TKey, TValue>>::iterator TVectorIterator;
protected:
  // std::pair<const TKey, TValue> mapValue;
  // std::shared_ptr<std::map<TKey, TValue, TCompare, TAllocator>> items;
  
  // using TForwardIterator = typename std::map<TKey, TValue, TCompare, TAllocator>::iterator;
  // using TReverseIterator = typename std::map<TKey, TValue, TCompare, TAllocator>::reverse_iterator;
  // TForwardIterator mapBeginIterator;
  // TForwardIterator mapEndIterator;
  // TReverseIterator mapRBeginIterator;
  // TReverseIterator mapREndIterator;

public:
  QueryableMapData(TCompare comparator = {}, TAllocator allocator = {})
    : QueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue, TCompare, TAllocator>()
    {
      this->items = std::make_shared<std::map<TKey, TValue, TCompare, TAllocator>>(comparator, allocator);
      // this->DefaultInitialize();
    }

  QueryableMapData(const std::map<TKey, TValue, TCompare, TAllocator> & items)
    : QueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue, TCompare, TAllocator>(items)
  {
    // this->items = std::make_shared<std::map<TKey, TValue, TCompare, TAllocator>>(items);
    // this->DefaultInitialize();
    // this->size = items->size();
  }

  QueryableMapData(std::map<TKey, TValue, TCompare, TAllocator> && items)
    : QueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue, TCompare, TAllocator>(std::move(items))
  {
    // this->items = std::make_shared<std::map<TKey, TValue, TCompare, TAllocator>>(items);
    // this->DefaultInitialize();
    // this->size = items->size();
  }

  QueryableMapData(const QueryableMapData<TKey, TValue, TCompare, TAllocator> & data)
    : QueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue, TCompare, TAllocator>(data)
  {
    // std::cout << "queryable map data copy" << std::endl;
    // this->size = data.size;
    // this->items = data.items;
    // this->mapBeginIterator = data.mapBeginIterator;
    // this->mapRBeginIterator = data.mapRBeginIterator;
    // this->mapEndIterator = data.mapEndIterator;
    // this->mapREndIterator = data.mapREndIterator;
  }

  QueryableMapData(
    TVectorIterator first,
    TVectorIterator last,
    TCompare comparator = {})
    : QueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue, TCompare, TAllocator>(first, last, comparator) { }

  virtual ~QueryableMapData() { }

  virtual std::shared_ptr<IQueryableData<std::pair<const TKey, TValue>>> Clone() override
  {
    // std::cout << "queryable map data clone" << std::endl;
    return std::make_shared<QueryableMapData<TKey, TValue, TCompare, TAllocator>>(*this);
  }  

  // void DefaultInitialize()
  // {
  //   this->mapBeginIterator = this->items->begin();
  //   this->mapEndIterator = this->items->end();
  //   this->mapRBeginIterator = this->items->rbegin();
  //   this->mapREndIterator = this->items->rend();
  //   this->size = 0;
  // }

  void Add(std::pair<const TKey, TValue> item) override
  {
    (*this->items)[item.first] = item.second;

    // because its a map, the item may not have actually been added. Insert
    // returns true/false whether the item was added, but the size method is
    // also a constant time action, so its cleaner to use it
    this->size = this->items->size();
  }

  virtual std::pair<const TKey, TValue> & Get(IteratorType type) override
  {
      // std::cout << "Map Get" << std::endl;
    switch (type)
    {
    //   case IteratorType::BeginForward: { *this->value = *this->beginIterator; return *this->value; }
    //   case IteratorType::EndForward: { *this->value = *this->endIterator; return *this->value; }
    //   case IteratorType::BeginReverse: { *this->value = *this->rbeginIterator; return *this->value; }
    //   case IteratorType::EndReverse: default: { *this->value = *this->rendIterator; return *this->value; }
      case IteratorType::BeginForward: { return *this->beginIterator; }
      case IteratorType::EndForward: { return *this->endIterator; }
      case IteratorType::BeginReverse: { return *this->rbeginIterator; }
      case IteratorType::EndReverse: default: { return *this->rendIterator; }
    }

    return this->value;
    // std::cout << "Map Get: " << *this->value << std::endl;
  }

  virtual const std::pair<const TKey, TValue> & ConstGet(IteratorType type) override
  {
    switch (type)
    {
      // case IteratorType::BeginForward: { *this->value = *this->beginIterator; return *this->value; }
      // case IteratorType::EndForward: { *this->value = *this->endIterator; return *this->value; }
      // case IteratorType::BeginReverse: { *this->value = *this->rbeginIterator; return *this->value; }
      // case IteratorType::EndReverse: default: { *this->value = *this->rendIterator; return *this->value; }
      case IteratorType::BeginForward: { return *this->beginIterator; }
      case IteratorType::EndForward: { return *this->endIterator; }
      case IteratorType::BeginReverse: { return *this->rbeginIterator; }
      case IteratorType::EndReverse: default: { return *this->rendIterator; }
    }

    return this->value;
  }

//   virtual bool CanIncrement(IteratorType type) override
//   {
//     switch (type)
//     {
//       case IteratorType::BeginForward: return this->mapBeginIterator != this->mapEndIterator;
//       case IteratorType::BeginReverse: return this->mapRBeginIterator != this->mapREndIterator;
//       case IteratorType::EndForward:
//       case IteratorType::EndReverse:
//       default:
//         return true;
//     }

//     return false;
//   }

//   virtual bool CanDecrement(IteratorType type) override
//   {
//     switch (type)
//     {
//       case IteratorType::EndForward: return this->mapBeginIterator != this->mapEndIterator;
//       case IteratorType::EndReverse: return this->mapRBeginIterator != this->mapREndIterator;
//       case IteratorType::BeginForward:
//       case IteratorType::BeginReverse:
//       default:
//         return true;
//     }

//     return false;
//   }

// // pass a boolean by reference and return true/false whether force to end has been set
//   virtual IQueryableData<std::pair<const TKey, TValue>> & Next(IteratorType type, size_t & iterated, bool & isForcingToEnd) override
//   {
//     // std::cout << "[NEXT] underlying begin value before" << std::endl;

//     if (this->forceToEnd)
//     {
//       iterated = this->size;
//       isForcingToEnd = true;
//       return *this;
//     }

//     switch (type)
//     {
//       case IteratorType::BeginForward: ++this->mapBeginIterator; break;
//       case IteratorType::EndForward: ++this->mapEndIterator; break;
//       case IteratorType::BeginReverse: ++this->mapRBeginIterator; break;
//       case IteratorType::EndReverse: ++this->mapREndIterator; break;
//     }
//     // std::cout << "[NEXT] underlying begin value after: " << *this->mapBeginIterator << std::endl;

//     iterated = 1;
//     return *this;
//   }

//   virtual IQueryableData<std::pair<const TKey, TValue>> & Prev(IteratorType type, size_t & iterated) override
//   {
//     // std::cout << "[PREV] underlying begin value before: " << std::endl;

//     switch (type)
//     {
//       case IteratorType::BeginForward: --this->mapBeginIterator; break;
//       case IteratorType::EndForward: --this->mapEndIterator; break;
//       case IteratorType::BeginReverse: --this->mapRBeginIterator; break;
//       case IteratorType::EndReverse: --this->mapREndIterator; break;
//     }
//       // std::cout << "[PREV] underlying begin value after: " << std::endl;
//     iterated = 1;
//     return *this;
//   }

//   virtual IQueryableData<std::pair<const TKey, TValue>> & Add(int addend, IteratorType type) override
//   {
//     // std::cout << "\nBAD" << std::endl;
//     // this is the worse possible way to implement this and should be overriden for random access iterators
//     switch (type)
//     {
//       case IteratorType::BeginForward: while (addend--) ++this->mapBeginIterator; break;
//       case IteratorType::EndForward: while (addend--) ++this->mapEndIterator; break;
//       case IteratorType::BeginReverse: while (addend--) ++this->mapRBeginIterator; break;
//       case IteratorType::EndReverse: while (addend--) ++this->mapREndIterator; break;
//     }

//     return *this;
//   }

//   virtual IQueryableData<std::pair<const TKey, TValue>> & Subtract(int subtrahend, IteratorType type) override
//   {
//     // this is the worse possible way to implement this and should be overriden for random access iterators
//     switch (type)
//     {
//       case IteratorType::BeginForward: while (subtrahend--) --this->mapBeginIterator; break;
//       case IteratorType::EndForward: while (subtrahend--) --this->mapEndIterator; break;
//       case IteratorType::BeginReverse: while (subtrahend--) --this->mapRBeginIterator; break;
//       case IteratorType::EndReverse: while (subtrahend--) --this->mapREndIterator; break;
//     }

//     return *this;
//   }

//   virtual void Clear() override
//   {
//     this->items->clear();
//     this->size = 0;
//   }

//   virtual QueryableIterator<std::pair<const TKey, TValue>> begin() override
//   {
//     // std::cout << "Map Queryable begin" << std::endl;
//     this->mapBeginIterator = this->items->begin();
//     this->forceToBegin = false;
//     this->forceToEnd = false;
//     QueryableIterator<std::pair<const TKey, TValue>> retVal(this->Clone(), 0, IteratorType::BeginForward);
//     return retVal;
//   }

//   virtual QueryableIterator<std::pair<const TKey, TValue>> end() override
//   {
//     // std::cout << "Map Queryable end" << std::endl;
//     this->mapEndIterator = this->items->end();
//     this->forceToBegin = false;
//     this->forceToEnd = false;
//     QueryableIterator<std::pair<const TKey, TValue>> retVal(this->Clone(), this->size, IteratorType::EndForward);

//     return retVal;
//   }

//   virtual QueryableIterator<std::pair<const TKey, TValue>> rbegin() override
//   {
//     this->mapRBeginIterator = this->items->rbegin();
//     this->forceToBegin = false;
//     this->forceToEnd = false;
//     QueryableIterator<std::pair<const TKey, TValue>> retVal(this->Clone(), 0, IteratorType::BeginReverse);
//     return retVal;
//   }

//   virtual QueryableIterator<std::pair<const TKey, TValue>> rend() override
//   {
//     this->mapREndIterator = this->items->rend();
//     this->forceToBegin = false;
//     this->forceToEnd = false;
//     QueryableIterator<std::pair<const TKey, TValue>> retVal(this->Clone(), this->size, IteratorType::EndReverse);
//     return retVal;
//   }

//   virtual void ForceEnd(IteratorType type) override
//   {
//     // TODO --> I think WhereQueryable might need two different sizes
//     //   1. theoretical size when skipping elements
//     //   2. true size

//     // std::cout << "force to end by size: " << this->size << std::endl;
//     this->forceToEnd = true;

//     switch(type)
//     {
//       case IteratorType::BeginForward:
//         this->mapBeginIterator = this->items->end();
//         break;
//       case IteratorType::EndForward:
//         this->mapEndIterator = this->items->end();
//         break;
//       case IteratorType::BeginReverse:
//         this->mapREndIterator = this->items->rend();
//         break;
//       case IteratorType::EndReverse:
//         this->mapREndIterator = this->items->rend();
//         break;
//     }
//   }

//   virtual void ForceBegin(IteratorType type) override
//   {
//     this->forceToBegin = true;

//     switch(type)
//     {
//       case IteratorType::BeginForward:
//         this->mapBeginIterator = this->items->begin();
//         break;
//       case IteratorType::EndForward:
//         this->mapEndIterator = this->items->begin();
//         break;
//       case IteratorType::BeginReverse:
//         this->mapREndIterator = this->items->rbegin();
//         break;
//       case IteratorType::EndReverse:
//         this->mapREndIterator = this->items->rbegin();
//         break;
//     }
//   }
};

#endif
