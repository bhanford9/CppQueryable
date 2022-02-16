#ifndef CPPQUERYABLE_QUERYABLE_ITERATORS_QUERYABLEITERATOR_H
#define CPPQUERYABLE_QUERYABLE_ITERATORS_QUERYABLEITERATOR_H

#include <iostream>

template <typename T>
class QueryableIterator
{
protected:
  int64_t index;
public:

  QueryableIterator() :
    index(0)
  {
  }

  inline bool operator==(const QueryableIterator<T>& comparison) const
  {
    // std::cout << "== index; " << this->index << std::endl;
    return this->index == comparison.index;
  }

  inline bool operator!=(const QueryableIterator<T>& comparison) const
  {
    // std::cout << "!= index; " << this->index << std::endl;
    return this->index != comparison.index;
  }

  inline int operator-(const QueryableIterator<T>& subtrahend) const
  {
    // std::cout << "-o index; " << this->index << std::endl;
    return this->index - subtrahend.index;
  }

  inline bool operator<(const QueryableIterator<T>& other) const
  {
    // std::cout << "< index; " << this->index << std::endl;
    return this->index < other.index;
  }



  // These methods are all intended to be overriden, but be inilned for speed optimization
  // Making them pure virtual would make the class abstract and would not work with the begin/end methods
  // I am hoping that I can inherit from CppQueryableData and cast itself to return a copy
  //   if this does not work, then the begin/end methods will have to be pushed all the way down to the lowest children

  inline virtual QueryableIterator<T>& operator++()
  {
    this->index++;
    return *this;
  }

  inline virtual QueryableIterator<T>& operator--()
  {
    this->index--;
    return *this;
  }

  inline virtual T& operator*()
  {
    return T();
  }

  inline virtual const T& operator*() const
  {
    return T();
  }

  inline virtual QueryableIterator<T>& operator+(int addend)
  {
    this->index += addend;
    return *this;
  }

  inline virtual QueryableIterator<T>& operator+=(int addend)
  {
    this->index += addend;
    return *this;
  }

  inline virtual QueryableIterator<T>& operator-(int subtrahend)
  {
    this->index -= subtrahend;
    return *this;
  }

  inline virtual QueryableIterator<T>& operator-=(int subtrahend)
  {
    this->index -= subtrahend;
    return *this;
  }

  inline virtual QueryableIterator<T>& operator=(const QueryableIterator<T>& value)
  {
    this->index = value.index;
    return *this;
  }
};

#endif
