#ifndef CPPQUERYABLE_QUERYABLE_VOLATILEQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_VOLATILEQUERYABLEDATA_H

#include <algorithm>
#include <memory>

#include "QueryableData.hpp"

template <typename T, template<typename, typename ...> class TIterable, typename TAllocator =
          std::allocator<T>, typename ...TArgs>
class VolatileQueryableData final : public QueryableVectorData<T, TAllocator>
{
public:
    VolatileQueryableData()
        : QueryableVectorData<T, TAllocator>()
    {
    }

    VolatileQueryableData(const VolatileQueryableData & other)
        : QueryableVectorData<T, TAllocator>(other)
    {
    }

    VolatileQueryableData(VolatileQueryableData && other) noexcept
        : QueryableVectorData<T, TAllocator>(std::move(other))
    {
    }

    explicit VolatileQueryableData(const std::vector<T, TAllocator> & vector)
        : QueryableVectorData<T, TAllocator>(vector)
    {        
    }

    explicit VolatileQueryableData(std::vector<T, TAllocator> && vector) noexcept
        : QueryableVectorData<T, TAllocator>(vector)
    {        
    }
    
    VolatileQueryableData & operator=(const VolatileQueryableData & other)
    {
        if (this == &other) return *this;
        QueryableVectorData<T, TAllocator>::operator =(other);
        return *this;
    }

    VolatileQueryableData & operator=(VolatileQueryableData && other) noexcept
    {
        if (this == &other) return *this;
        QueryableVectorData<T, TAllocator>::operator =(std::move(other));
        return *this;
    }

    virtual ~VolatileQueryableData() override
    {
    }

    //
    // virtual IQueryableData<T> & Add(int addend, IteratorType type) override
    // {
    //   // std::cout << "ConstRandom Access + Operator, adding: " << addend << std::endl;
    //   switch (type)
    //   {
    //     case IteratorType::BeginForward: this->beginIterator += addend; break;
    //     case IteratorType::EndForward: this->endIterator += addend; break;
    //     case IteratorType::BeginReverse: this->rbeginIterator += addend; break;
    //     case IteratorType::EndReverse: this->rendIterator += addend; break;
    //   }
    //
    //   // std::cout << "ConstRandom Access add result: " << *this->beginIterator << std::endl;
    //
    //   return *this;
    // }
    //
    // virtual IQueryableData<T> & Subtract(int subtrahend, IteratorType type) override
    // {
    //   // std::cout << "ConstRandom Access - Operator, adding: " << subtrahend << std::endl;
    //   switch (type)
    //   {
    //     case IteratorType::BeginForward: this->beginIterator -= subtrahend; break;
    //     case IteratorType::EndForward: this->endIterator -= subtrahend; break;
    //     case IteratorType::BeginReverse: this->rbeginIterator -= subtrahend; break;
    //     case IteratorType::EndReverse: this->rendIterator -= subtrahend; break;
    //   }
    //
    //   return *this;
    // }

    virtual T & Get(const IteratorType type) override
    {
        // std::cout << "Get" << std::endl;
        switch (type)
        {
        case IteratorType::BeginForward: { return static_cast<T &>(*this->beginIterator); }
        case IteratorType::EndForward: { return static_cast<T &>(*this->endIterator); }
        case IteratorType::BeginReverse: { return static_cast<T &>(*this->rbeginIterator); }
        case IteratorType::EndReverse: default: { return static_cast<T &>(*this->rendIterator); }
        }
    }

    virtual const T & ConstGet(const IteratorType type) override
    {
        switch (type)
        {
        case IteratorType::BeginForward: { return *this->beginIterator; }
        case IteratorType::EndForward: { return *this->endIterator; }
        case IteratorType::BeginReverse: { return *this->rbeginIterator; }
        case IteratorType::EndReverse: default: { return *this->rendIterator; }
        }
    }

    // void Add(T item) override
    // {
    //   this->items->push_back(item);
    //   this->size++;
    // }
};

#endif
