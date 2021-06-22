#ifndef FIRST_QUERYABLE_GROUPING_H
#define FIRST_QUERYABLE_GROUPING_H

#include <vector>

#include "Queryable.h"

template <typename TKey, typename TObj>
class Grouping : public Queryable<TObj, std::vector>
{
// private:
//   TKey key;
//
// public:
//   TKey GetKey()
//   {
//     return this->key;
//   }
//
//   void Add(TKey key, TObj value)
//   {
//     this->key = key;
//     this->items.push_back(value);
//   }
//
//   void Add(TObj value)
//   {
//     this->items.push_back(value);
//   }
};

#endif
