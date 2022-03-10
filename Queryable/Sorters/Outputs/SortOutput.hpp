#ifndef CPPQUERYABLE_SORTERS_SORTOUTPUT_H
#define CPPQUERYABLE_SORTERS_SORTOUTPUT_H

#include <iostream>

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class SortOutput
{
private:
  TIterable<TObj, TArgs...> output;

public:
  SortOutput(const SortOutput<TObj, TIterable, TArgs...> & sortOutput)
    : output(sortOutput.output)
  {
  }
  SortOutput(SortOutput<TObj, TIterable, TArgs...> && sortOutput)
    : output(std::move(sortOutput.output))
  {
  }

  SortOutput(const TIterable<TObj, TArgs...> & iterable)
  : output(iterable)
  {
  }
  SortOutput(TIterable<TObj, TArgs...> && iterable)
    : output(std::move(iterable))
  {
  }

  TIterable<TObj, TArgs...> Get()
  {
    return this->output;
  }
};

#endif
