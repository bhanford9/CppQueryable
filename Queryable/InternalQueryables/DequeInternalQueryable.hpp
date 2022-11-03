#ifndef CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_DEQUEINTERNALQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_DEQUEINTERNALQUERYABLE_H

#include <deque>
#include "QueryableForwardDeclare.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableDequeData.hpp"
#include "../QueryableData/SkipWhileQueryableData/SkipWhileQueryableDequeData.hpp"
#include "../QueryableData/TakeWhileQueryableData/TakeWhileQueryableDequeData.hpp"
#include "../QueryableData/WhereQueryableData/WhereQueryableDequeData.hpp"
#include "../Utilities/IWhileCondition.hpp"

template <typename TObj, typename TAllocator>
class DequeInternalQueryable final : public InternalQueryable<TObj, std::deque, TObj, TAllocator>
{
public:

    DequeInternalQueryable(const DequeInternalQueryable & other)
        : InternalQueryable<TObj, std::deque, TObj, TAllocator>(other)
    {
    }

    DequeInternalQueryable(DequeInternalQueryable && other) noexcept
        : InternalQueryable<TObj, std::deque, TObj, TAllocator>(std::move(other))
    {
    }

    explicit DequeInternalQueryable(TAllocator allocator = { })
        : InternalQueryable<TObj, std::deque, TObj, TAllocator>(QueryableType::Deque)
    {
        std::deque<TObj> localDeque(allocator);
        this->items = std::make_shared<QueryableDequeData<TObj, TAllocator>>(localDeque);
    }

    explicit DequeInternalQueryable(const std::deque<TObj, TAllocator> & deque)
    {
        this->type = QueryableType::Deque;
        this->items = std::move(std::make_shared<QueryableDequeData<TObj, TAllocator>>(deque));
    }

    explicit DequeInternalQueryable(std::deque<TObj, TAllocator> && deque)
    {
        this->type = QueryableType::Deque;
        this->items = std::move(
            std::make_shared<QueryableDequeData<TObj, TAllocator>>(std::move(deque)));
    }

    explicit DequeInternalQueryable(
        const InternalQueryable<TObj, std::deque, TObj, TAllocator> & other)
        : InternalQueryable<TObj, std::deque, TObj, TAllocator>(other)
    {
        this->type = QueryableType::Deque;
    }

    DequeInternalQueryable(
        std::shared_ptr<QueryableData<TObj, std::deque, TObj, TAllocator>> && queryableData,
        QueryableType type)
        : InternalQueryable<TObj, std::deque, TObj, TAllocator>(std::move(queryableData), type)
    {
    }

    DequeInternalQueryable(
        const QueryableIterator<TObj> & first,
        const QueryableIterator<TObj> & last,
        TAllocator allocator = { })
    {
        this->items = std::make_shared<QueryableDequeData<TObj, TAllocator>>(
            std::deque<TObj, TAllocator>(first, last, allocator));
        this->type = QueryableType::Deque;
    }

    DequeInternalQueryable & operator=(const DequeInternalQueryable & other)
    {
        if (this == &other) return *this;
        InternalQueryable<TObj, std::deque, TObj, TAllocator>::operator =(other);
        return *this;
    }

    DequeInternalQueryable & operator=(DequeInternalQueryable && other) noexcept
    {
        if (this == &other) return *this;
        InternalQueryable<TObj, std::deque, TObj, TAllocator>::operator =(std::move(other));
        return *this;
    }

    virtual ~DequeInternalQueryable() = default;
    
    virtual void Where(std::function<bool(const TObj &)> condition) override
    {
        this->items = std::move(
            std::make_shared<WhereQueryableDequeData<TObj, TAllocator>>(
                std::move(this->items),
                std::move(condition)));
    }

    virtual void InternalSkipWhile(std::shared_ptr<IWhileCondition<TObj>> && condition) override
    {
        this->items = std::move(
            std::make_shared<SkipWhileQueryableDequeData<TObj, TAllocator>>(
                std::move(this->items),
                std::move(condition)));
    }

    virtual void InternalTakeWhile(std::shared_ptr<IWhileCondition<TObj>> && condition) override
    {
        this->items = std::move(
            std::make_shared<TakeWhileQueryableDequeData<TObj, TAllocator>>(
                std::move(this->items),
                std::move(condition)));
    }
};

#endif
