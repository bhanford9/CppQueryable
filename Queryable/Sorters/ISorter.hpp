#ifndef CPPQUERYABLE_SORTERS_ISORTER_H
#define CPPQUERYABLE_SORTERS_ISORTER_H

template<
  typename TObj,
  template<typename, typename ...> class TIterable,
  typename ...TArgs>
class ISorter
{
public:
  virtual ~ISorter() { }
  virtual void Sort(TIterable<TObj, TArgs...> & container) const = 0;
};

#endif
