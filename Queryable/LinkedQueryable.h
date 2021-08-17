#ifndef CPPQUERYABLE_QUERYABLE_LINKEDQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_LINKEDQUERYABLE_H

#include <algorithm>
#include <deque>
#include <exception>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <vector>

#include "Utilities/Condition.h"
#include "Utilities/Group.h"
#include "Utilities/IGroup.h"
#include "Utilities/PersistentContainer.h"
#include "Utilities/Selection.h"
#include "QueryableData/IQueryableData.h"
#include "QueryableData/QueryableDequeData.h"
#include "QueryableData/QueryableListData.h"
#include "QueryableData/QueryableMultiSetData.h"
#include "QueryableData/QueryableSetData.h"
#include "QueryableData/QueryableVectorData.h"
#include "QueryableType.h"
#include "TypeConstraintUtil.h"

template<typename TObj, typename TCompare = std::less<TObj>>
class Queryable;

template<
  typename TSelfObj,
  typename TLinkObj,
  typename TSelfCompare = std::less<TSelfObj>,
  typename TLinkCompare = std::less<TLinkObj>>
class LinkedQueryable : public Queryable<TSelfObj, TSelfCompare>
{
protected:
  Queryable<TLinkObj, TLinkCompare> * link;
  Selection<TLinkObj, TSelfObj> selection;

  virtual bool IsLinked() override
  {
    return true;
  }

public:
  LinkedQueryable(
    Queryable<TLinkObj, TLinkCompare> link,
    std::function<TSelfObj(TLinkObj)> selector,
    QueryableType type = QueryableType::Vector,
    TSelfCompare compare = TSelfCompare())
    : Queryable<TSelfObj, TSelfCompare>(type, compare)
  {
    this->link = link;
    this->selection.SetSelector(selector);
  }

  virtual ~LinkedQueryable() { }

  Queryable<TLinkObj, TLinkCompare> * AppliedLink()
  {
    if (this->link->IsLinked())
    {
      return this->link->AppliedLink();
    }

    return this->link->Applied();
  }

  Queryable<TSelfObj, TSelfCompare> * AppliedSelf()
  {
    this->items.get()->Clear();

    this->AppliedLink()->ForEach([&](TLinkObj item)
    {
      this->items.get()->Add(this->selection(item));
    });

    return this;
  }
};

#endif
