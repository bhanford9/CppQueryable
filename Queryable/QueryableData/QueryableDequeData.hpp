#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEDEQUEDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEDEQUEDATA_H

#include <algorithm>
#include <deque>
#include <memory>

#include "RandomAccessQueryableData.hpp"

template <typename T, typename TAllocator = std::allocator<T>>
class QueryableDequeData final : public RandomAccessQueryableData<T, std::deque, TAllocator>
{
public:
    QueryableDequeData(const QueryableDequeData & other)
        : RandomAccessQueryableData<T, std::deque, TAllocator>(other)
    {
    }

    QueryableDequeData(QueryableDequeData && other) noexcept
        : RandomAccessQueryableData<T, std::deque, TAllocator>(std::move(other))
    {
    }

    QueryableDequeData()
        : RandomAccessQueryableData<T, std::deque, TAllocator>()
    {
    }

    explicit QueryableDequeData(const std::deque<T, TAllocator> & items)
        : RandomAccessQueryableData<T, std::deque, TAllocator>(items)
    {
    }

    explicit QueryableDequeData(std::deque<T, TAllocator> && items)
        : RandomAccessQueryableData<T, std::deque, TAllocator>(std::move(items))
    {
    }

    QueryableDequeData & operator=(const QueryableDequeData & other)
    {
        if (this == &other) return *this;
        RandomAccessQueryableData<T, std::deque, TAllocator>::operator =(other);
        return *this;
    }

    QueryableDequeData & operator=(QueryableDequeData && other) noexcept
    {
        if (this == &other) return *this;
        RandomAccessQueryableData<T, std::deque, TAllocator>::operator =(std::move(other));
        return *this;
    }

    virtual ~QueryableDequeData() override
    {
    }

    virtual std::shared_ptr<IQueryableData<T>> Clone() override
    {
        // std::cout << "deque clone" << std::endl;
        return std::make_shared<QueryableDequeData<T, TAllocator>>(*this);
    }
};

#endif
