#ifndef CPPQUERYABLE_QUERYABLE_SKIPWHILEQUERYABLEDATA_SKIPWHILEQUERYABLELISTDATA_H
#define CPPQUERYABLE_QUERYABLE_SKIPWHILEQUERYABLEDATA_SKIPWHILEQUERYABLELISTDATA_H

#include <list>

#include "SkipWhileQueryableData.hpp"

template <typename TObj, typename TAllocator = std::allocator<TObj>>
class SkipWhileQueryableListData final : public SkipWhileQueryableData<TObj, std::list, TObj, TAllocator>
{
public:
    SkipWhileQueryableListData(const SkipWhileQueryableListData & other)
        : SkipWhileQueryableData<TObj, std::list, TObj, TAllocator>(other)
    {
    }

    SkipWhileQueryableListData(SkipWhileQueryableListData && other) noexcept
        : SkipWhileQueryableData<TObj, std::list, TObj, TAllocator>(std::move(other))
    {
    }

    SkipWhileQueryableListData(
        std::shared_ptr<IQueryableData<TObj>> && data,
        std::shared_ptr<IWhileCondition<TObj>> && condition)
        : SkipWhileQueryableData<TObj, std::list, TObj, TAllocator>(
            std::move(data),
            std::move(condition))
    {
        // std::cout << "SkipWhileQueryable List Data Constructor 0" << std::endl;
    }

    SkipWhileQueryableListData(
        std::shared_ptr<QueryableData<TObj, std::list, TObj, TAllocator>> && data,
        std::shared_ptr<IWhileCondition<TObj>> && condition)
        : SkipWhileQueryableData<TObj, std::list, TObj, TAllocator>(
            std::move(data),
            std::move(condition))
    {
        // std::cout << "SkipWhileQueryable List Data Constructor 1" << std::endl;
    }

    SkipWhileQueryableListData(
        const std::shared_ptr<QueryableData<TObj, std::list, TObj, TAllocator>> & data,
        std::shared_ptr<IWhileCondition<TObj>> && condition)
        : SkipWhileQueryableData<TObj, std::list, TObj, TAllocator>(data, std::move(condition))
    {
        // std::cout << "SkipWhileQueryable List Data Constructor 3" << std::endl;
    }

    SkipWhileQueryableListData & operator=(const SkipWhileQueryableListData & other)
    {
        if (this == &other) return *this;
        SkipWhileQueryableData<TObj, std::list, TObj, TAllocator>::operator =(other);
        return *this;
    }

    SkipWhileQueryableListData & operator=(SkipWhileQueryableListData && other) noexcept
    {
        if (this == &other) return *this;
        SkipWhileQueryableData<TObj, std::list, TObj, TAllocator>::operator =(std::move(other));
        return *this;
    }

    virtual ~SkipWhileQueryableListData() override
    {
    }

    virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
    {
        return std::make_shared<SkipWhileQueryableListData<TObj, TAllocator>>(*this);
    }

    virtual void InternalAdd(TObj item) override
    {
        this->items->push_back(item);
    }

    virtual std::shared_ptr<IQueryableData<TObj>> GetRealizedQueryableData() override
    {
        // If all QueryableData's have a constructor that skips begin, end, Args... then this method can be a one liner
        std::list<TObj, TAllocator> data(this->items->get_allocator());

        for (const TObj & value : *this)
        {
            data.push_back(value);
        }

        return std::make_shared<QueryableListData<TObj, TAllocator>>(std::move(data));
    }
};

#endif
