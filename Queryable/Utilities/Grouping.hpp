#ifndef CPPQUERYABLE_QUERYABLE_UTILITIES_GROUPING_H
#define CPPQUERYABLE_QUERYABLE_UTILITIES_GROUPING_H

#include <iostream>
#include <vector>

#include "../InternalQueryables/VectorInternalQueryable.hpp"
#include "../Iterators/QueryableIterator.hpp"

template<
    typename TKey,
    typename TValue,
    typename TValueAllocator>
class Grouping : public VectorInternalQueryable<TValue, TValueAllocator>
{
private:
  TKey key;
  std::function<bool(TKey, TKey)> keyLessThan;

public:
  Grouping() { }
  virtual ~Grouping() { }

  Grouping(
    const TKey & key,
    const TValue & value,
    std::function<bool(TKey, TKey)> lessThan = [](TKey a, TKey b) { return a < b; },
    TValueAllocator allocator = {})
    : VectorInternalQueryable<TValue, TValueAllocator>(
        std::vector<TValue, TValueAllocator>(1, value, allocator))
  {
    this->key = key;
    this->keyLessThan = [&](TKey a, TKey b) { return lessThan(a, b); };
  }

  Grouping(
    const TKey & key,
    const std::vector<TValue, TValueAllocator> & values,
    std::function<bool(TKey, TKey)> lessThan = [](TKey a, TKey b) { return a < b; },
    TValueAllocator allocator = {})
    : VectorInternalQueryable<TValue, TValueAllocator>(values)
  {
    this->key = key;
    this->keyLessThan = [&](TKey a, TKey b) { return lessThan(a, b); };
  }

  Grouping(
    const TKey & key,
    const QueryableIterator<TValue> & first,
    const QueryableIterator<TValue> & last,
    std::function<bool(TKey, TKey)> lessThan = [](TKey a, TKey b) { return a < b; },
    TValueAllocator allocator = {})
      : VectorInternalQueryable<TValue, TValueAllocator>(first, last, allocator)
  {
    this->key = key;    
    this->keyLessThan = [&](TKey a, TKey b) { return lessThan(a, b); };
  }

  Grouping(const Grouping<TKey, TValue, TValueAllocator> & other)
    : VectorInternalQueryable<TValue, TValueAllocator>(other)
  {
    this->key = other.key;    
    this->keyLessThan = other.keyLessThan;
  }

  Grouping(Grouping<TKey, TValue, TValueAllocator> && other)
    : VectorInternalQueryable<TValue, TValueAllocator>(std::move(other))
  {
    this->key = std::move(other.key);
    this->keyLessThan = std::move(other.keyLessThan);
  }

  inline TKey GetKey() const
  {
    return this->key;
  }

  inline bool operator==(const Grouping<TKey, TValue, TValueAllocator> & other) const
  {
    return this->key == other.key;
  }

  inline bool operator!=(const Grouping<TKey, TValue, TValueAllocator> & other) const
  {
    return this->key != other.key;
  }

  inline bool operator<(const Grouping<TKey, TValue, TValueAllocator> & other) const
  {
    return this->keyLessThan(this->key, other.key);
  }

  inline Grouping<TKey, TValue, TValueAllocator>& operator=(
    const Grouping<TKey, TValue, TValueAllocator> & other)
  {
    this->key = other.key;
    this->keyLessThan = other.keyLessThan;
    this->items = other.items;
    return *this;
  }

  inline Grouping<TKey, TValue, TValueAllocator>& operator=(
    Grouping<TKey, TValue, TValueAllocator> && other)
  {
    this->key = other.key;
    this->keyLessThan = other.keyLessThan;
    this->items = std::move(other.items);
    return *this;
  }

  inline size_t Count()
  {
    return this->items->Count();
  }

  std::ostream & operator<<(std::ostream & str);
  friend std::ostream & operator<<(std::ostream & str, const Grouping & v)
  {
    size_t num = 0;
    v.ForEach([&](TValue value) { str << value << "\r\n"; num++; });
    str << "Number Of Elements in Group: " << num;
    return str;
  }
};

#endif
