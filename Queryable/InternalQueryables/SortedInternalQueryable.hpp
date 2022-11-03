#ifndef CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_SORTEDINTERNALQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_SORTEDINTERNALQUERYABLE_H

#include "QueryableForwardDeclare.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableSetData.hpp"

template <typename TObj, template<typename, typename ...> class TIterable, typename TLessThan,
          typename TAllocator>
class SortedInternalQueryable : public InternalQueryable<
        TObj, TIterable, TObj, TLessThan, TAllocator>
{
protected:
    SortedInternalQueryable() = default;

public:
    SortedInternalQueryable(const SortedInternalQueryable & other)
        : InternalQueryable<TObj, TIterable, TObj, TLessThan, TAllocator>(other)
    {
    }

    SortedInternalQueryable(SortedInternalQueryable && other) noexcept
        : InternalQueryable<TObj, TIterable, TObj, TLessThan, TAllocator>(std::move(other))
    {
    }

    virtual ~SortedInternalQueryable() = default;

    explicit SortedInternalQueryable(
        QueryableType type,
        TLessThan lessThan = { },
        TAllocator allocator = { })
        : InternalQueryable<TObj, TIterable, TObj, TLessThan, TAllocator>(type)
    {
    }

    SortedInternalQueryable(
        const InternalQueryable<TObj, TIterable, TObj, TLessThan, TAllocator> & other,
        QueryableType type)
        : InternalQueryable<TObj, TIterable, TObj, TLessThan, TAllocator>(other)
    {
        this->type = type;
    }

    SortedInternalQueryable(
        std::shared_ptr<QueryableData<TObj, TIterable, TObj, TLessThan, TAllocator>> &&
        queryableData,
        QueryableType type)
        : InternalQueryable<TObj, TIterable, TObj, TLessThan, TAllocator>(
            std::move(queryableData),
            type)
    {
    }

    SortedInternalQueryable(
        std::shared_ptr<QueryableSetData<TObj, TLessThan, TAllocator>> && queryableData,
        QueryableType type)
        : InternalQueryable<TObj, TIterable, TObj, TLessThan, TAllocator>(
            std::move(queryableData),
            type)
    {
        // std::cout << "Sorted Move Constructor" << std::endl;
    }

    SortedInternalQueryable & operator=(const SortedInternalQueryable & other)
    {
        if (this == &other) return *this;
        InternalQueryable<TObj, TIterable, TObj, TLessThan, TAllocator>::operator =(other);
        return *this;
    }

    SortedInternalQueryable & operator=(SortedInternalQueryable && other) noexcept
    {
        if (this == &other) return *this;
        InternalQueryable<TObj, TIterable, TObj, TLessThan, TAllocator>::operator =(
            std::move(other));
        return *this;
    }
};

#endif
