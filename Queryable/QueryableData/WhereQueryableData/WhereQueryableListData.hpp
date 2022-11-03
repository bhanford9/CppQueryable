#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLELISTDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLELISTDATA_H

#include <list>

#include "WhereQueryableData.hpp"
#include "../QueryableListData.hpp"

template <typename TObj, typename TAllocator = std::allocator<TObj>>
class WhereQueryableListData final : public WhereQueryableData<TObj, std::list, TObj, TAllocator>
{
public:
    WhereQueryableListData(const WhereQueryableListData & other)
        : WhereQueryableData<TObj, std::list, TObj, TAllocator>(other)
    {
    }

    WhereQueryableListData(WhereQueryableListData && other) noexcept
        : WhereQueryableData<TObj, std::list, TObj, TAllocator>(std::move(other))
    {
    }

    WhereQueryableListData(
        std::shared_ptr<IQueryableData<TObj>> data,
        std::function<bool(TObj)> condition)
        : WhereQueryableData<TObj, std::list, TObj, TAllocator>(
            std::move(data),
            std::move(condition))
    {
    }

    WhereQueryableListData(
        std::shared_ptr<QueryableData<TObj, std::list, TObj, TAllocator>> && data,
        std::function<bool(TObj)> && condition)
        : WhereQueryableData<TObj, std::list, TObj, TAllocator>(
            std::move(data),
            std::move(condition))
    {
    }

    WhereQueryableListData & operator=(const WhereQueryableListData & other)
    {
        if (this == &other) return *this;
        WhereQueryableData<TObj, std::list, TObj, TAllocator>::operator =(other);
        return *this;
    }

    WhereQueryableListData & operator=(WhereQueryableListData && other) noexcept
    {
        if (this == &other) return *this;
        WhereQueryableData<TObj, std::list, TObj, TAllocator>::operator =(std::move(other));
        return *this;
    }

    virtual ~WhereQueryableListData() override
    {
    }

    virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
    {
        return std::make_shared<WhereQueryableListData<TObj, TAllocator>>(*this);
    }

    virtual void InternalAdd(TObj item) override
    {
        this->items->push_back(item);
    }

    virtual std::shared_ptr<IQueryableData<TObj>> GetRealizedQueryableData() override
    {
        // If all QueryableData's have a constructor that takes begin, end, Args... then this method can be a one liner
        std::list<TObj, TAllocator> data(this->items->get_allocator());

        for (const TObj & value : *this)
        {
            data.push_back(value);
        }

        return std::make_shared<QueryableListData<TObj, TAllocator>>(std::move(data));
    }
};

#endif
