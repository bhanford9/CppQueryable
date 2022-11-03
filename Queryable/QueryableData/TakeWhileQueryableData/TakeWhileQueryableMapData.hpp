#ifndef CPPQUERYABLE_QUERYABLE_TAKEWHILEQUERYABLEDATA_TAKEWHILEQUERYABLEMAPDATA_H
#define CPPQUERYABLE_QUERYABLE_TAKEWHILEQUERYABLEDATA_TAKEWHILEQUERYABLEMAPDATA_H

#include <map>

#include "TakeWhileQueryableData.hpp"

template <typename TKey, typename TValue, typename TCompare = std::less<TKey>, typename TAllocator =
          std::allocator<std::pair<const TKey, TValue>>>
class TakeWhileQueryableMapData final : public TakeWhileQueryableData<
        TKey, std::map, std::pair<const TKey, TValue>, TValue, TCompare, TAllocator>
{
public:
    TakeWhileQueryableMapData(const TakeWhileQueryableMapData & other)
        : TakeWhileQueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue, TCompare,
                                 TAllocator>(other)
    {
    }

    TakeWhileQueryableMapData(TakeWhileQueryableMapData && other) noexcept
        : TakeWhileQueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue, TCompare,
                                 TAllocator>(std::move(other))
    {
    }

    TakeWhileQueryableMapData(
        std::shared_ptr<IQueryableData<std::pair<const TKey, TValue>>> data,
        std::shared_ptr<IWhileCondition<std::pair<const TKey, TValue>>> && condition)
        : TakeWhileQueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue, TCompare,
                                 TAllocator>(std::move(data), std::move(condition))
    {
    }

    TakeWhileQueryableMapData(
        std::shared_ptr<QueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue,
                                      TCompare, TAllocator>> && data,
        std::shared_ptr<IWhileCondition<std::pair<const TKey, TValue>>> && condition)
        : TakeWhileQueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue, TCompare,
                                 TAllocator>(std::move(data), std::move(condition))
    {
    }

    TakeWhileQueryableMapData & operator=(const TakeWhileQueryableMapData & other)
    {
        if (this == &other) return *this;
        TakeWhileQueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue, TCompare,
                               TAllocator>::operator =(other);
        return *this;
    }

    TakeWhileQueryableMapData & operator=(TakeWhileQueryableMapData && other) noexcept
    {
        if (this == &other) return *this;
        TakeWhileQueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue, TCompare,
                               TAllocator>::operator =(std::move(other));
        return *this;
    }

    virtual ~TakeWhileQueryableMapData() override
    {
    }

    virtual std::shared_ptr<IQueryableData<std::pair<const TKey, TValue>>> Clone() override
    {
        return std::make_shared<TakeWhileQueryableMapData<TKey, TValue, TCompare, TAllocator>>(
            *this);
    }

    virtual void InternalAdd(std::pair<const TKey, TValue> item) override
    {
        (*this->items)[item.first] = item.second;
    }

    virtual std::shared_ptr<IQueryableData<std::pair<const TKey, TValue>>>
    GetRealizedQueryableData() override
    {
        // If all QueryableData's have a constructor that takes begin, end, Args... then this method can be a one liner

        std::map<TKey, TValue, TCompare, TAllocator> data(
            this->items->key_comp(),
            this->items->get_allocator());

        for (const std::pair<const TKey, TValue> & value : *this)
        {
            data[value.first] = value.second;
        }

        return std::make_shared<QueryableMapData<TKey, TValue, TCompare, TAllocator>>(
            std::move(data));
    }
};

#endif
