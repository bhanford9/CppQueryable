#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEVECTOR_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEVECTOR_H

#include <memory>
#include <vector>

#include "Queryable.h"
#include "QueryableData/QueryableVectorData.h"

template<typename T>
class QueryableVector : public Queryable<T>
{
public:
  QueryableVector()
  {
    std::vector<T> local;
    this->items = std::make_unique<QueryableVectorData<T>>(local);
    this->type = QueryableType::Vector;
  }

  QueryableVector(std::vector<T> items)
  {
    this->items = std::make_unique<QueryableVectorData<T>>(items);
    this->type = QueryableType::Vector;
  }
};

#endif
