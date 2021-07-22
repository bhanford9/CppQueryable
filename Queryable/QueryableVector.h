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
    this->items = std::make_shared<QueryableVectorData<T>>(local);
    this->type = QueryableType::Vector;
  }

  QueryableVector(std::vector<T> items)
  {
    this->items = std::make_shared<QueryableVectorData<T>>(items);
    this->type = QueryableType::Vector;
  }

  QueryableVector(const QueryableVector& queryable)
    : Queryable<T>(queryable)
  {
  }


  virtual ~QueryableVector() { }
};

#endif
