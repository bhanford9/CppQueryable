#ifndef CPPQUERYABLE_QUERYABLE_UTILITIES_WHILECONDITION_H
#define CPPQUERYABLE_QUERYABLE_UTILITIES_WHILECONDITION_H

#include <functional>
#include <iostream>

#include "IWhileCondition.hpp"

template<typename TValue, typename TCondition>
class WhileCondition : public IWhileCondition<TValue>
{
private:
  TCondition currentValue;
  std::function<bool(const TValue &, TCondition &)> condition;
  std::function<TCondition(TCondition)> resetCondition;

public:
  WhileCondition(
    TCondition startingValue,
    std::function<bool(const TValue &, TCondition &)> condition,
    std::function<TCondition(TCondition)> resetCondition) :
    currentValue(startingValue),
    condition(condition),
    resetCondition(resetCondition)
  {        
  }

  virtual ~WhileCondition() { }

  inline virtual bool Passes(const TValue & obj) override
  {
    bool passes = this->condition(obj, this->currentValue);
    return passes;
  }

  inline virtual bool operator()(const TValue & obj) override
  {
    return this->Passes(obj);
  }

  inline virtual void Reset() override
  {
    this->currentValue = this->resetCondition(this->currentValue);
  }
};

#endif