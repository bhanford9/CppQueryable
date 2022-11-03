#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEMULTISETDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEMULTISETDATA_H

#include <memory>
#include <set>

#include "SortedQueryableData.hpp"

template <typename T, typename TCompare = std::less<T>, typename TAllocator = std::allocator<T>>
class QueryableMultiSetData final : public SortedQueryableData<
        T, std::multiset, TCompare, TAllocator>
{
public:
    QueryableMultiSetData(const QueryableMultiSetData & other)
        : SortedQueryableData<T, std::multiset, TCompare, TAllocator>(other)
    {
    }

    QueryableMultiSetData(QueryableMultiSetData && other) noexcept
        : SortedQueryableData<T, std::multiset, TCompare, TAllocator>(std::move(other))
    {
    }

    explicit QueryableMultiSetData(TCompare comparator = { })
        : SortedQueryableData<T, std::multiset, TCompare, TAllocator>()
    {
    }

    explicit QueryableMultiSetData(const std::multiset<T, TCompare, TAllocator> & items)
        : SortedQueryableData<T, std::multiset, TCompare, TAllocator>(items)
    {
    }

    explicit QueryableMultiSetData(std::multiset<T, TCompare, TAllocator> && items)
        : SortedQueryableData<T, std::multiset, TCompare, TAllocator>(std::move(items))
    {
    }

    QueryableMultiSetData & operator=(const QueryableMultiSetData & other)
    {
        if (this == &other) return *this;
        SortedQueryableData<T, std::multiset, TCompare, TAllocator>::operator =(other);
        return *this;
    }

    QueryableMultiSetData & operator=(QueryableMultiSetData && other) noexcept
    {
        if (this == &other) return *this;
        SortedQueryableData<T, std::multiset, TCompare, TAllocator>::operator =(std::move(other));
        return *this;
    }

    virtual ~QueryableMultiSetData() override = default;

    virtual std::shared_ptr<IQueryableData<T>> Clone() override
    {
        return std::make_shared<QueryableMultiSetData<T, TCompare, TAllocator>>(*this);
    }

    virtual void Add(T item) override
    {
        this->items->insert(item);
        ++this->size;
    }
};

#endif
