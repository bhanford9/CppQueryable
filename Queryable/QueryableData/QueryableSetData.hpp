#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLESETDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLESETDATA_H

#include <memory>
#include <set>

#include "SortedQueryableData.hpp"

template <typename T, typename TCompare = std::less<T>, typename TAllocator = std::allocator<T>>
class QueryableSetData final : public SortedQueryableData<T, std::set, TCompare, TAllocator>
{
public:
    QueryableSetData(const QueryableSetData & other)
        : SortedQueryableData<T, std::set, TCompare, TAllocator>(other)
    {
    }

    QueryableSetData(QueryableSetData && other) noexcept
        : SortedQueryableData<T, std::set, TCompare, TAllocator>(std::move(other))
    {
    }

    explicit QueryableSetData(TCompare comparator = { })
        : SortedQueryableData<T, std::set, TCompare, TAllocator>()
    {
    }

    explicit QueryableSetData(const std::set<T, TCompare, TAllocator> & items)
        : SortedQueryableData<T, std::set, TCompare, TAllocator>(items)
    {
    }

    explicit QueryableSetData(std::set<T, TCompare, TAllocator> && items)
        : SortedQueryableData<T, std::set, TCompare, TAllocator>(std::move(items))
    {
    }

    QueryableSetData & operator=(const QueryableSetData & other)
    {
        if (this == &other) return *this;
        SortedQueryableData<T, std::set, TCompare, TAllocator>::operator =(other);
        return *this;
    }

    QueryableSetData & operator=(QueryableSetData && other) noexcept
    {
        if (this == &other) return *this;
        SortedQueryableData<T, std::set, TCompare, TAllocator>::operator =(std::move(other));
        return *this;
    }

    virtual ~QueryableSetData() override
    {
    }

    virtual std::shared_ptr<IQueryableData<T>> Clone() override
    {
        return std::make_shared<QueryableSetData<T, TCompare, TAllocator>>(*this);
    }

    virtual void Add(T item) override
    {
        this->items->insert(item);

        // because its a set, the item may not have actually been added. Insert
        // returns true/false whether the item was added, but the size method is
        // also a constant time action, so its cleaner to use it
        this->size = this->items->size();
    }
};

#endif
