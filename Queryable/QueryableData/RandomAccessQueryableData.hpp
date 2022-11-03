#ifndef CPPQUERYABLE_QUERYABLE_RANDOMACCESSQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_RANDOMACCESSQUERYABLEDATA_H

#include <algorithm>
#include <memory>

#include "QueryableData.hpp"

template <typename T, template<typename, typename ...> class TIterable, typename TAllocator =
          std::allocator<T>, typename ...TArgs>
class RandomAccessQueryableData : public QueryableData<T, TIterable, T, TAllocator, TArgs...>
{
public:
    RandomAccessQueryableData(const RandomAccessQueryableData & other)
        : QueryableData<T, TIterable, T, TAllocator, TArgs...>(other)
    {
    }

    RandomAccessQueryableData(RandomAccessQueryableData && other) noexcept
        : QueryableData<T, TIterable, T, TAllocator, TArgs...>(std::move(other))
    {
    }

    RandomAccessQueryableData()
        : QueryableData<T, TIterable, T, TAllocator, TArgs...>()
    {
    }

    explicit RandomAccessQueryableData(const TIterable<T, TAllocator, TArgs...> & items)
        : QueryableData<T, TIterable, T, TAllocator, TArgs...>(items)
    {
    }

    explicit RandomAccessQueryableData(TIterable<T, TAllocator, TArgs...> && items)
        : QueryableData<T, TIterable, T, TAllocator, TArgs...>(std::move(items))
    {
    }

    RandomAccessQueryableData & operator=(const RandomAccessQueryableData & other)
    {
        if (this == &other) return *this;
        QueryableData<T, TIterable, T, TAllocator, TArgs...>::operator =(other);
        return *this;
    }

    RandomAccessQueryableData & operator=(RandomAccessQueryableData && other) noexcept
    {
        if (this == &other) return *this;
        QueryableData<T, TIterable, T, TAllocator, TArgs...>::operator =(std::move(other));
        return *this;
    }

    virtual ~RandomAccessQueryableData() override = default;

    virtual IQueryableData<T> & Add(int addend, const IteratorType type) override
    {
        // std::cout << "Random Access + Operator, adding: " << addend << std::endl;
        switch (type)
        {
        case IteratorType::BeginForward: this->beginIterator += addend;
            break;
        case IteratorType::EndForward: this->endIterator += addend;
            break;
        case IteratorType::BeginReverse: this->rbeginIterator += addend;
            break;
        case IteratorType::EndReverse: this->rendIterator += addend;
            break;
        }

        // std::cout << "Random Access add result: " << *this->beginIterator << std::endl;

        return *this;
    }

    virtual IQueryableData<T> & Subtract(int subtrahend, const IteratorType type) override
    {
        // std::cout << "Random Access - Operator, adding: " << subtrahend << std::endl;
        switch (type)
        {
        case IteratorType::BeginForward: this->beginIterator -= subtrahend;
            break;
        case IteratorType::EndForward: this->endIterator -= subtrahend;
            break;
        case IteratorType::BeginReverse: this->rbeginIterator -= subtrahend;
            break;
        case IteratorType::EndReverse: this->rendIterator -= subtrahend;
            break;
        }

        return *this;
    }

    virtual T & Get(const IteratorType type) override
    {
        // std::cout << "RAQ Get" << std::endl;
        switch (type)
        {
        // case IteratorType::BeginForward: { this->value = &(*this->beginIterator); return *this->value; }
        // case IteratorType::EndForward: { this->value = &(*this->endIterator); return *this->value; }
        // case IteratorType::BeginReverse: { this->value = &(*this->rbeginIterator); return *this->value; }
        // case IteratorType::EndReverse: default: { this->value = &(*this->rendIterator); return *this->value; }
        case IteratorType::BeginForward:
            {
                this->value = *this->beginIterator;
                return this->value;
            }
        case IteratorType::EndForward:
            {
                this->value = *this->endIterator;
                return this->value;
            }
        case IteratorType::BeginReverse:
            {
                this->value = *this->rbeginIterator;
                return this->value;
            }
        case IteratorType::EndReverse: default:
            {
                this->value = *this->rendIterator;
                return this->value;
            }
        }
    }

    virtual const T & ConstGet(const IteratorType type) override
    {
        // std::cout << "RAQ Const Get" << std::endl;
        switch (type)
        {
        // case IteratorType::BeginForward: { this->value = &(*this->beginIterator); return *this->value; }
        // case IteratorType::EndForward: { this->value = &(*this->endIterator); return *this->value; }
        // case IteratorType::BeginReverse: { this->value = &(*this->rbeginIterator); return *this->value; }
        // case IteratorType::EndReverse: default: { this->value = &(*this->rendIterator); return *this->value; }
        case IteratorType::BeginForward:
            {
                this->value = *this->beginIterator;
                return this->value;
            }
        case IteratorType::EndForward:
            {
                this->value = *this->endIterator;
                return this->value;
            }
        case IteratorType::BeginReverse:
            {
                this->value = *this->rbeginIterator;
                return this->value;
            }
        case IteratorType::EndReverse: default:
            {
                this->value = *this->rendIterator;
                return this->value;
            }
        }
    }

    virtual void Add(T item) override
    {
        this->items->push_back(item);
        ++this->size;
    }
};

#endif
