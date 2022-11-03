#ifndef CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_SETINTERNALQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_SETINTERNALQUERYABLE_H

#include <set>
#include "QueryableForwardDeclare.hpp"
#include "SortedInternalQueryable.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableSetData.hpp"
#include "../QueryableData/SkipWhileQueryableData/SkipWhileQueryableSetData.hpp"
#include "../QueryableData/TakeWhileQueryableData/TakeWhileQueryableSetData.hpp"
#include "../QueryableData/WhereQueryableData/WhereQueryableSetData.hpp"
#include "../Utilities/IWhileCondition.hpp"

template <typename TObj, typename TLessThan, typename TAllocator>
class SetInternalQueryable final : public SortedInternalQueryable<
        TObj, std::set, TLessThan, TAllocator>
{
public:
    SetInternalQueryable(const SetInternalQueryable & other)
        : SortedInternalQueryable<TObj, std::set, TLessThan, TAllocator>(other)
    {
    }

    SetInternalQueryable(SetInternalQueryable && other) noexcept
        : SortedInternalQueryable<TObj, std::set, TLessThan, TAllocator>(std::move(other))
    {
    }

    explicit SetInternalQueryable(TLessThan lessThan = { }, TAllocator allocator = { })
        : SortedInternalQueryable<TObj, std::set, TLessThan, TAllocator>(
            QueryableType::Set,
            lessThan,
            allocator)
    {
        std::set<TObj, TLessThan, TAllocator> localSet(lessThan, allocator);
        this->items = std::make_shared<QueryableSetData<TObj, TLessThan, TAllocator>>(localSet);
    }

    explicit SetInternalQueryable(const std::set<TObj, TLessThan, TAllocator> & set)
    {
        this->type = QueryableType::Set;
        this->items = std::make_shared<QueryableSetData<TObj, TLessThan, TAllocator>>(set);
    }

    explicit SetInternalQueryable(std::set<TObj, TLessThan, TAllocator> && set)
    {
        this->type = QueryableType::Set;
        this->items = std::make_shared<QueryableSetData<TObj, TLessThan, TAllocator>>(
            std::move(set));
    }

    explicit SetInternalQueryable(
        const InternalQueryable<TObj, std::set, TObj, TLessThan, TAllocator> & other)
        : SortedInternalQueryable<TObj, std::set, TLessThan, TAllocator>(other, QueryableType::Set)
    {
    }

    SetInternalQueryable(
        std::shared_ptr<QueryableData<TObj, std::set, TObj, TLessThan, TAllocator>> &&
        queryableData,
        QueryableType type)
        : SortedInternalQueryable<TObj, std::set, TLessThan, TAllocator>(
            std::move(queryableData),
            type)
    {
    }

    SetInternalQueryable(
        const QueryableIterator<TObj> & first,
        const QueryableIterator<TObj> & last,
        TLessThan lessThan = { },
        TAllocator allocator = { })
    {
        this->items = std::make_shared<QueryableSetData<TObj, TLessThan, TAllocator>>(
            std::set<TObj, TLessThan, TAllocator>(first, last, lessThan, allocator));
        this->type = QueryableType::Set;
    }

    SetInternalQueryable & operator=(const SetInternalQueryable & other)
    {
        if (this == &other) return *this;
        SortedInternalQueryable<TObj, std::set, TLessThan, TAllocator>::operator =(other);
        return *this;
    }

    SetInternalQueryable & operator=(SetInternalQueryable && other) noexcept
    {
        if (this == &other) return *this;
        SortedInternalQueryable<TObj, std::set, TLessThan, TAllocator>::operator
            =(std::move(other));
        return *this;
    }

    virtual ~SetInternalQueryable() override = default;

    virtual void Where(std::function<bool(const TObj &)> condition) override
    {
        this->items = std::move(
            std::make_shared<WhereQueryableSetData<TObj, TLessThan, TAllocator>>(
                std::move(this->items),
                std::move(condition)));
    }

    virtual void InternalSkipWhile(std::shared_ptr<IWhileCondition<TObj>> && condition) override
    {
        this->items = std::move(
            std::make_shared<SkipWhileQueryableSetData<TObj, TLessThan, TAllocator>>(
                std::move(this->items),
                std::move(condition)));
    }

    virtual void InternalTakeWhile(std::shared_ptr<IWhileCondition<TObj>> && condition) override
    {
        this->items = std::move(
            std::make_shared<TakeWhileQueryableSetData<TObj, TLessThan, TAllocator>>(
                std::move(this->items),
                std::move(condition)));
    }
};

#endif
