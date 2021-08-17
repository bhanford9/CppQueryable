#ifndef CPPQUERYABLE_QUERYABLE_UTILITIES_SELECTION_H
#define CPPQUERYABLE_QUERYABLE_UTILITIES_SELECTION_H

#include <functional>
#include <iostream>

template<typename TObj, typename TResult>
class Selection
{
private:
  std::function<TResult(TObj)> selector;

public:
  Selection() { }
  Selection(std::function<TResult(TObj)> selector)
  {
    this->selector = selector;
  }

  void SetSelector(std::function<TResult(TObj)> selector)
  {
    this->selector = selector;
  }

  TResult Select(TObj obj)
  {
    return this->selector(obj);
  }

  TResult operator()(TObj obj)
  {
    return this->Select(obj);
  }

  operator bool() const
  {
    return this->selector ? true : false;
  }
};

#endif
