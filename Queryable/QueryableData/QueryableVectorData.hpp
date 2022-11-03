#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEVECTORDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEVECTORDATA_H

#include <vector>

#include "RandomAccessQueryableData.hpp"

template <typename T, typename TAllocator = std::allocator<T>>
class QueryableVectorData : public RandomAccessQueryableData<T, std::vector, TAllocator>
{
public:
    QueryableVectorData(const QueryableVectorData & other)
        : RandomAccessQueryableData<T, std::vector, TAllocator>(other)
    {
    }

    QueryableVectorData(QueryableVectorData && other) noexcept
        : RandomAccessQueryableData<T, std::vector, TAllocator>(std::move(other))
    {
    }

    QueryableVectorData()
        : RandomAccessQueryableData<T, std::vector, TAllocator>()
    {
    }

    explicit QueryableVectorData(const std::vector<T, TAllocator> & items)
        : RandomAccessQueryableData<T, std::vector, TAllocator>(items)
    {
    }

    explicit QueryableVectorData(std::vector<T, TAllocator> && items)
        : RandomAccessQueryableData<T, std::vector, TAllocator>(std::move(items))
    {
    }

    QueryableVectorData & operator=(const QueryableVectorData & other)
    {
        if (this == &other) return *this;
        RandomAccessQueryableData<T, std::vector, TAllocator>::operator =(other);
        return *this;
    }

    QueryableVectorData & operator=(QueryableVectorData && other) noexcept
    {
        if (this == &other) return *this;
        RandomAccessQueryableData<T, std::vector, TAllocator>::operator =(std::move(other));
        return *this;
    }

    virtual ~QueryableVectorData() override = default;

    virtual std::shared_ptr<IQueryableData<T>> Clone() override
    {
        return std::make_shared<QueryableVectorData<T, TAllocator>>(*this);
    }
};

#endif
