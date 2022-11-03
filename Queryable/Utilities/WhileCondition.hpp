#ifndef CPPQUERYABLE_QUERYABLE_UTILITIES_WHILECONDITION_H
#define CPPQUERYABLE_QUERYABLE_UTILITIES_WHILECONDITION_H

#include <functional>

#include "IWhileCondition.hpp"

template<typename TValue, typename TCondition>
class WhileCondition : public IWhileCondition<TValue>
{
private:
  TCondition currentValue;
  std::function<bool(const TValue &)> condition;
  std::function<bool(const TValue &, TCondition &)> paramCondition;
  std::function<TCondition(TCondition)> resetCondition;

public:
    // TODO --> these would be better left as separate children
  WhileCondition(
    TCondition startingValue,
    std::function<bool(const TValue &, TCondition &)> && condition,
    std::function<TCondition(TCondition)> && resetCondition) :
    currentValue(startingValue),
    paramCondition(std::move(condition)),
    resetCondition(std::move(resetCondition))
  {        
  }

  WhileCondition(std::function<bool(const TValue &)> condition) :
    condition(std::move(condition))
  {
  }

  virtual ~WhileCondition() { }

  // TODO --> I think this method should be able to be const
  virtual bool Passes(const TValue & obj) override
  {
    bool passes = false;
    
    if (this->paramCondition)
    {
      passes = this->paramCondition(obj, this->currentValue);
    }
    else
    {
      passes = this->condition(obj);
    }

    return passes;
  }

  virtual bool operator()(const TValue & obj) override
  {
    return this->Passes(obj);
  }

  virtual void Reset() override
  {
    if (this->resetCondition)
    {
        this->currentValue = this->resetCondition(this->currentValue);
    }
  }
};

#endif