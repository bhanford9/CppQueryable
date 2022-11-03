#ifndef CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_MAPINTERNALQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_MAPINTERNALQUERYABLE_H

#include <map>
#include "QueryableForwardDeclare.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableMapData.hpp"
#include "../QueryableData/SkipWhileQueryableData/SkipWhileQueryableMapData.hpp"
#include "../QueryableData/TakeWhileQueryableData/TakeWhileQueryableMapData.hpp"
#include "../QueryableData/WhereQueryableData/WhereQueryableMapData.hpp"
#include "../Utilities/IWhileCondition.hpp"

template <typename TKey, typename TValue, typename TLessThan, typename TAllocator>
class MapInternalQueryable final : public InternalQueryable<
        TKey, std::map, std::pair<const TKey, TValue>, TValue, TLessThan, TAllocator>
{
public:
    virtual ~MapInternalQueryable() = default;

    MapInternalQueryable(const MapInternalQueryable & other)
        : InternalQueryable<TKey, std::map, std::pair<const TKey, TValue>, TValue, TLessThan,
                            TAllocator>(other)
    {
    }

    MapInternalQueryable(MapInternalQueryable && other) noexcept
        : InternalQueryable<TKey, std::map, std::pair<const TKey, TValue>, TValue, TLessThan,
                            TAllocator>(std::move(other))
    {
    }

    explicit MapInternalQueryable(TLessThan lessThan = { }, TAllocator allocator = { })
        : InternalQueryable<TKey, std::map, std::pair<const TKey, TValue>, TValue, TLessThan,
                            TAllocator>(QueryableType::Map, lessThan, allocator)
    {
        std::map<TKey, TValue, TLessThan, TAllocator> localMap(lessThan, allocator);
        this->items = std::make_shared<QueryableMapData<TKey, TValue, TLessThan, TAllocator>>(
            localMap);
    }

    explicit MapInternalQueryable(const std::map<TKey, TValue, TLessThan, TAllocator> & map)
    {
        this->type = QueryableType::Map;
        this->items = std::make_shared<QueryableMapData<TKey, TValue, TLessThan, TAllocator>>(map);
    }

    explicit MapInternalQueryable(std::map<TKey, TValue, TLessThan, TAllocator> && map)
    {
        this->type = QueryableType::Map;
        this->items = std::make_shared<QueryableMapData<TKey, TValue, TLessThan, TAllocator>>(
            std::move(map));
    }

    explicit MapInternalQueryable(
        const InternalQueryable<TKey, std::map, std::pair<const TKey, TValue>, TValue, TLessThan,
                                TAllocator> & other)
        : InternalQueryable<TKey, std::map, std::pair<const TKey, TValue>, TValue, TLessThan,
                            TAllocator>(other, QueryableType::Map)
    {
    }

    MapInternalQueryable(
        std::shared_ptr<QueryableData<TKey, std::map, std::pair<const TKey, TValue>, TValue,
                                      TLessThan, TAllocator>> && queryableData,
        QueryableType type)
        : InternalQueryable<TKey, std::map, std::pair<const TKey, TValue>, TValue, TLessThan,
                            TAllocator>(std::move(queryableData), type)
    {
    }

    MapInternalQueryable(
        const QueryableIterator<TValue> & first,
        const QueryableIterator<TValue> & last,
        TLessThan lessThan = { },
        TAllocator allocator = { })
    {
        this->items = std::make_shared<QueryableMapData<TKey, TValue, TLessThan, TAllocator>>(
            std::map<TKey, TValue, TLessThan, TAllocator>(first, last, lessThan, allocator));
        this->type = QueryableType::Map;
    }

    MapInternalQueryable & operator=(const MapInternalQueryable & other)
    {
        if (this == &other) return *this;
        InternalQueryable<TKey, std::map, std::pair<const TKey, TValue>, TValue, TLessThan,
                          TAllocator>::operator =(other);
        return *this;
    }

    MapInternalQueryable & operator=(MapInternalQueryable && other) noexcept
    {
        if (this == &other) return *this;
        InternalQueryable<TKey, std::map, std::pair<const TKey, TValue>, TValue, TLessThan,
                          TAllocator>::operator =(std::move(other));
        return *this;
    }

    virtual void Where(
        std::function<bool(const std::pair<const TKey, TValue> &)> condition) override
    {
        this->items = std::move(
            std::make_shared<WhereQueryableMapData<TKey, TValue, TLessThan, TAllocator>>(
                std::move(this->items),
                std::move(condition)));
    }

    virtual void InternalSkipWhile(
        std::shared_ptr<IWhileCondition<std::pair<const TKey, TValue>>> && condition) override
    {
        this->items = std::move(
            std::make_shared<SkipWhileQueryableMapData<TKey, TValue, TLessThan, TAllocator>>(
                std::move(this->items),
                std::move(condition)));
    }

    virtual void InternalTakeWhile(
        std::shared_ptr<IWhileCondition<std::pair<const TKey, TValue>>> && condition) override
    {
        this->items = std::move(
            std::make_shared<TakeWhileQueryableMapData<TKey, TValue, TLessThan, TAllocator>>(
                std::move(this->items),
                std::move(condition)));
    }
};

#endif
