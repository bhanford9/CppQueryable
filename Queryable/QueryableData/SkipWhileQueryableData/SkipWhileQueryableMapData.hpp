#ifndef CPPQUERYABLE_QUERYABLE_SKIPWHILEQUERYABLEDATA_SKIPWHILEQUERYABLEMAPDATA_H
#define CPPQUERYABLE_QUERYABLE_SKIPWHILEQUERYABLEDATA_SKIPWHILEQUERYABLEMAPDATA_H

#include <map>

#include "SkipWhileQueryableData.hpp"

template <typename TKey, typename TValue, typename TCompare = std::less<TKey>, typename TAllocator =
          std::allocator<std::pair<const TKey, TValue>>>
class SkipWhileQueryableMapData final : public SkipWhileQueryableData<
        TKey, std::map, std::pair<const TKey, TValue>, TValue, TCompare, TAllocator>
{
public:
    SkipWhileQueryableMapData(const SkipWhileQueryableMapData & other)
        : SkipWhileQueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue, TCompare,
                                 TAllocator>(other)
    {
    }

    SkipWhileQueryableMapData(SkipWhileQueryableMapData && other) noexcept
        : SkipWhileQueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue, TCompare,
                                 TAllocator>(std::move(other))
    {
    }

    SkipWhileQueryableMapData(
        std::shared_ptr<IQueryableData<std::pair<const TKey, TValue>>> data,
        std::shared_ptr<IWhileCondition<std::pair<const TKey, TValue>>> && condition)
        : SkipWhileQueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue, TCompare,
                                 TAllocator>(std::move(data), std::move(condition))
    {
    }

    SkipWhileQueryableMapData(
        std::shared_ptr<QueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue,
                                      TCompare, TAllocator>> && data,
        std::shared_ptr<IWhileCondition<std::pair<const TKey, TValue>>> && condition)
        : SkipWhileQueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue, TCompare,
                                 TAllocator>(std::move(data), std::move(condition))
    {
    }

    SkipWhileQueryableMapData & operator=(const SkipWhileQueryableMapData & other)
    {
        if (this == &other) return *this;
        SkipWhileQueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue, TCompare,
                               TAllocator>::operator =(other);
        return *this;
    }

    SkipWhileQueryableMapData & operator=(SkipWhileQueryableMapData && other) noexcept
    {
        if (this == &other) return *this;
        SkipWhileQueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue, TCompare,
                               TAllocator>::operator =(std::move(other));
        return *this;
    }

    virtual ~SkipWhileQueryableMapData() override
    {
    }

    virtual std::shared_ptr<IQueryableData<std::pair<const TKey, TValue>>> Clone() override
    {
        return std::make_shared<SkipWhileQueryableMapData<TKey, TValue, TCompare, TAllocator>>(
            *this);
    }

    virtual void InternalAdd(std::pair<const TKey, TValue> item) override
    {
        (*this->items)[item.first] = item.second;
    }

    virtual std::shared_ptr<IQueryableData<std::pair<const TKey, TValue>>>
    GetRealizedQueryableData() override
    {
        // If all QueryableData's have a constructor that skips begin, end, Args... then this method can be a one liner

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
