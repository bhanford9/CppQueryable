#ifndef CPPQUERYABLE_QUERYABLE_UTILITIES_IWHILECONDITION_H
#define CPPQUERYABLE_QUERYABLE_UTILITIES_IWHILECONDITION_H

template<typename TValue>
class IWhileCondition
{
public:
  virtual ~IWhileCondition() { }
  virtual void Reset() = 0;  
  virtual bool Passes(const TValue & obj) = 0;
  virtual bool operator()(const TValue & obj) = 0;
};

#endif