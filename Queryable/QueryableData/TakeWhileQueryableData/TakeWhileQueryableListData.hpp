#ifndef CPPQUERYABLE_QUERYABLE_TAKEWHILEQUERYABLEDATA_TAKEWHILEQUERYABLELISTDATA_H
#define CPPQUERYABLE_QUERYABLE_TAKEWHILEQUERYABLEDATA_TAKEWHILEQUERYABLELISTDATA_H

#include <list>

#include "TakeWhileQueryableData.hpp"

template <typename TObj, typename TAllocator = std::allocator<TObj>>
class TakeWhileQueryableListData : public TakeWhileQueryableData<TObj, std::list, TObj, TAllocator>
{
public:
    TakeWhileQueryableListData(const TakeWhileQueryableListData & other)
        : TakeWhileQueryableData<TObj, std::list, TObj, TAllocator>(other)
    {
    }

    TakeWhileQueryableListData(TakeWhileQueryableListData && other) noexcept
        : TakeWhileQueryableData<TObj, std::list, TObj, TAllocator>(std::move(other))
    {
    }

    TakeWhileQueryableListData(
        std::shared_ptr<IQueryableData<TObj>> && data,
        std::shared_ptr<IWhileCondition<TObj>> && condition)
        : TakeWhileQueryableData<TObj, std::list, TObj, TAllocator>(
            std::move(data),
            std::move(condition))
    {
        // std::cout << "TakeWhileQueryable List Data Constructor 0" << std::endl;
    }

    TakeWhileQueryableListData(
        std::shared_ptr<QueryableData<TObj, std::list, TObj, TAllocator>> && data,
        std::shared_ptr<IWhileCondition<TObj>> && condition)
        : TakeWhileQueryableData<TObj, std::list, TObj, TAllocator>(
            std::move(data),
            std::move(condition))
    {
        // std::cout << "TakeWhileQueryable List Data Constructor 1" << std::endl;
    }

    TakeWhileQueryableListData(
        const std::shared_ptr<QueryableData<TObj, std::list, TObj, TAllocator>> & data,
        std::shared_ptr<IWhileCondition<TObj>> && condition)
        : TakeWhileQueryableData<TObj, std::list, TObj, TAllocator>(data, std::move(condition))
    {
        // std::cout << "TakeWhileQueryable List Data Constructor 3" << std::endl;
    }

    TakeWhileQueryableListData & operator=(const TakeWhileQueryableListData & other)
    {
        if (this == &other) return *this;
        TakeWhileQueryableData<TObj, std::list, TObj, TAllocator>::operator =(other);
        return *this;
    }

    TakeWhileQueryableListData & operator=(TakeWhileQueryableListData && other) noexcept
    {
        if (this == &other) return *this;
        TakeWhileQueryableData<TObj, std::list, TObj, TAllocator>::operator =(std::move(other));
        return *this;
    }

    virtual ~TakeWhileQueryableListData() override
    {
    }

    virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
    {
        return std::make_shared<TakeWhileQueryableListData<TObj, TAllocator>>(*this);
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
