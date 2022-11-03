#ifndef CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_MULTISETINTERNALQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_MULTISETINTERNALQUERYABLE_H

#include <set>
#include "QueryableForwardDeclare.hpp"
#include "SortedInternalQueryable.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableMultiSetData.hpp"
#include "../QueryableData/SkipWhileQueryableData/SkipWhileQueryableMultiSetData.hpp"
#include "../QueryableData/TakeWhileQueryableData/TakeWhileQueryableMultiSetData.hpp"
#include "../QueryableData/WhereQueryableData/WhereQueryableMultiSetData.hpp"
#include "../Utilities/IWhileCondition.hpp"

template <typename TObj, typename TLessThan, typename TAllocator>
class MultiSetInternalQueryable final : public SortedInternalQueryable<
        TObj, std::multiset, TLessThan, TAllocator>
{
public:
    MultiSetInternalQueryable(const MultiSetInternalQueryable & other)
        : SortedInternalQueryable<TObj, std::multiset, TLessThan, TAllocator>(other)
    {
    }

    MultiSetInternalQueryable(MultiSetInternalQueryable && other) noexcept
        : SortedInternalQueryable<TObj, std::multiset, TLessThan, TAllocator>(std::move(other))
    {
    }

    explicit MultiSetInternalQueryable(TLessThan lessThan = { }, TAllocator allocator = { })
        : SortedInternalQueryable<TObj, std::multiset, TLessThan, TAllocator>(
            QueryableType::MultiSet,
            lessThan,
            allocator)
    {
        std::multiset<TObj, TLessThan, TAllocator> localMultiSet(lessThan, allocator);
        this->items = std::make_shared<QueryableMultiSetData<TObj, TLessThan, TAllocator>>(
            localMultiSet);
    }

    explicit MultiSetInternalQueryable(const std::multiset<TObj, TLessThan, TAllocator> & multiset)
    {
        this->type = QueryableType::MultiSet;
        this->items = std::move(
            std::make_shared<QueryableMultiSetData<TObj, TLessThan, TAllocator>>(multiset));
    }

    explicit MultiSetInternalQueryable(
        const InternalQueryable<TObj, std::multiset, TObj, TLessThan, TAllocator> & other)
        : SortedInternalQueryable<TObj, std::multiset, TLessThan, TAllocator>(
            other,
            QueryableType::MultiSet)
    {
    }

    MultiSetInternalQueryable(
        std::shared_ptr<QueryableData<TObj, std::multiset, TObj, TLessThan, TAllocator>> &&
        queryableData,
        QueryableType type)
        : SortedInternalQueryable<TObj, std::multiset, TLessThan, TAllocator>(
            std::move(queryableData),
            type)
    {
    }

    MultiSetInternalQueryable(
        const QueryableIterator<TObj> & first,
        const QueryableIterator<TObj> & last,
        TLessThan lessThan = { },
        TAllocator allocator = { })
    {
        this->items = std::make_shared<QueryableMultiSetData<TObj, TLessThan, TAllocator>>(
            std::multiset<TObj, TLessThan, TAllocator>(first, last, lessThan, allocator));
        this->type = QueryableType::MultiSet;
    }

    virtual ~MultiSetInternalQueryable() override = default;

    MultiSetInternalQueryable & operator=(const MultiSetInternalQueryable & other)
    {
        if (this == &other) return *this;
        SortedInternalQueryable<TObj, std::multiset, TLessThan, TAllocator>::operator =(other);
        return *this;
    }

    MultiSetInternalQueryable & operator=(MultiSetInternalQueryable && other) noexcept
    {
        if (this == &other) return *this;
        SortedInternalQueryable<TObj, std::multiset, TLessThan, TAllocator>::operator =(
            std::move(other));
        return *this;
    }

    virtual void Where(std::function<bool(const TObj &)> condition) override
    {
        this->items = std::move(
            std::make_shared<WhereQueryableMultiSetData<TObj, TLessThan, TAllocator>>(
                std::move(this->items),
                std::move(condition)));
    }

    virtual void InternalSkipWhile(std::shared_ptr<IWhileCondition<TObj>> && condition) override
    {
        this->items = std::move(
            std::make_shared<SkipWhileQueryableMultiSetData<TObj, TLessThan, TAllocator>>(
                std::move(this->items),
                std::move(condition)));
    }

    virtual void InternalTakeWhile(std::shared_ptr<IWhileCondition<TObj>> && condition) override
    {
        this->items = std::move(
            std::make_shared<TakeWhileQueryableMultiSetData<TObj, TLessThan, TAllocator>>(
                std::move(this->items),
                std::move(condition)));
    }
};

#endif
