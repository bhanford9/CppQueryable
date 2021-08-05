#ifndef CPPQUERYABLE_QUERYABLE_UTILITIES_PERSISTENTCONTAINER_H
#define CPPQUERYABLE_QUERYABLE_UTILITIES_PERSISTENTCONTAINER_H

#include <iostream>
#include <memory>

class PersistentContainer
{
private:
  std::shared_ptr<void> data;

public:
  void Set(const std::shared_ptr<void> & data)
  {
    this->data = data;
  }

  std::shared_ptr<void> Get()
  {
    return this->data;
  }

  template <typename T>
  std::shared_ptr<T> GetAs()
  {
    return std::static_pointer_cast<T>(this->data);
  }
};

#endif
