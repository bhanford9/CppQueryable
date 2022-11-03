#ifndef CPPQUERYABLE_QUERYABLE_UTILITIES_STATICBUILDERS_QUERYABLESTATICBUILDER_H
#define CPPQUERYABLE_QUERYABLE_UTILITIES_STATICBUILDERS_QUERYABLESTATICBUILDER_H

#include <deque>
#include <list>
#include <map>
#include <set>
#include <vector>

#include "InternalQueryableStaticBuilder.hpp"
#include "../Casting.hpp"

template <typename TStoring, template<typename, typename ...> class TIterable, typename TIterating,
          typename ...TArgs>
class Queryable;

namespace Builders
{
    template <typename TStoring, typename TAllocator = std::allocator<TStoring>>
    static Queryable<TStoring, std::deque, TStoring, TAllocator> FromInternalDeque(
        DequeInternalQueryable<TStoring, TAllocator> && other)
    {
        Queryable<TStoring, std::deque, TStoring, TAllocator> queryable(
            std::move(
                FutureStd::reinterpret_pointer_cast<InternalQueryable<
                    TStoring, std::deque, TStoring, TAllocator>>(
                    std::make_shared<DequeInternalQueryable<TStoring, TAllocator>>(other))));
        return queryable;
    }

    template <typename TStoring, typename TAllocator = std::allocator<TStoring>>
    static Queryable<TStoring, std::list, TStoring, TAllocator> FromInternalList(
        ListInternalQueryable<TStoring, TAllocator> && other)
    {
        Queryable<TStoring, std::list, TStoring, TAllocator> queryable(
            std::move(
                FutureStd::reinterpret_pointer_cast<InternalQueryable<
                    TStoring, std::list, TStoring, TAllocator>>(
                    std::make_shared<ListInternalQueryable<TStoring, TAllocator>>(other))));
        return queryable;
    }

    template <typename TStoring, typename TLessThan = std::less<TStoring>, typename TAllocator =
              std::allocator<TStoring>>
    static Queryable<TStoring, std::multiset, TStoring, TLessThan, TAllocator> FromInternalMultiSet(
        MultiSetInternalQueryable<TStoring, TLessThan, TAllocator> && other)
    {
        Queryable<TStoring, std::multiset, TStoring, TLessThan, TAllocator> queryable(
            std::move(
                FutureStd::reinterpret_pointer_cast<InternalQueryable<
                    TStoring, std::multiset, TStoring, TLessThan, TAllocator>>(
                    std::make_shared<MultiSetInternalQueryable<TStoring, TLessThan, TAllocator>>(
                        other))));
    }

    template <typename TStoring, typename TLessThan = std::less<TStoring>, typename TAllocator =
              std::allocator<TStoring>>
    static Queryable<TStoring, std::set, TStoring, TLessThan, TAllocator> FromInternalSet(
        SetInternalQueryable<TStoring, TLessThan, TAllocator> && other)
    {
        Queryable<TStoring, std::set, TStoring, TLessThan, TAllocator> queryable(
            std::move(
                FutureStd::reinterpret_pointer_cast<InternalQueryable<
                    TStoring, std::set, TStoring, TLessThan, TAllocator>>(
                    std::make_shared<SetInternalQueryable<TStoring, TLessThan, TAllocator>>(
                        other))));
        return queryable;
    }

    template <typename TStoring, typename TAllocator = std::allocator<TStoring>>
    static Queryable<TStoring, std::vector, TStoring, TAllocator> FromInternalVector(
        VectorInternalQueryable<TStoring, TAllocator> && other)
    {
        Queryable<TStoring, std::vector, TStoring, TAllocator> queryable(
            std::move(
                FutureStd::reinterpret_pointer_cast<InternalQueryable<
                    TStoring, std::vector, TStoring, TAllocator>>(
                    std::make_shared<VectorInternalQueryable<TStoring, TAllocator>>(other))));
        return queryable;
    }

    template <typename TStoring, typename TAllocator = std::allocator<TStoring>>
    static Queryable<TStoring, std::deque, TStoring, TAllocator> FromInternalDeque(
        const DequeInternalQueryable<TStoring, TAllocator> & other)
    {
        Queryable<TStoring, std::deque, TStoring, TAllocator> queryable(
            FutureStd::reinterpret_pointer_cast<InternalQueryable<
                TStoring, std::deque, TStoring, TAllocator>>(
                std::make_shared<DequeInternalQueryable<TStoring, TAllocator>>(other)));
        return queryable;
    }

    template <typename TStoring, typename TAllocator = std::allocator<TStoring>>
    static Queryable<TStoring, std::list, TStoring, TAllocator> FromInternalList(
        const ListInternalQueryable<TStoring, TAllocator> & other)
    {
        Queryable<TStoring, std::list, TStoring, TAllocator> queryable(
            FutureStd::reinterpret_pointer_cast<InternalQueryable<
                TStoring, std::list, TStoring, TAllocator>>(
                std::make_shared<ListInternalQueryable<TStoring, TAllocator>>(other)));
        return queryable;
    }

    template <typename TStoring, typename TLessThan = std::less<TStoring>, typename TAllocator =
              std::allocator<TStoring>>
    static Queryable<TStoring, std::multiset, TStoring, TLessThan, TAllocator> FromInternalMultiSet(
        const MultiSetInternalQueryable<TStoring, TLessThan, TAllocator> & other)
    {
        Queryable<TStoring, std::multiset, TStoring, TLessThan, TAllocator> queryable(
            FutureStd::reinterpret_pointer_cast<InternalQueryable<
                TStoring, std::multiset, TStoring, TLessThan, TAllocator>>(
                std::make_shared<MultiSetInternalQueryable<TStoring, TLessThan, TAllocator>>(
                    other)));
        return queryable;
    }

    template <typename TStoring, typename TLessThan = std::less<TStoring>, typename TAllocator =
              std::allocator<TStoring>>
    static Queryable<TStoring, std::set, TStoring, TLessThan, TAllocator> FromInternalSet(
        const SetInternalQueryable<TStoring, TLessThan, TAllocator> & other)
    {
        Queryable<TStoring, std::set, TStoring, TLessThan, TAllocator> queryable(
            FutureStd::reinterpret_pointer_cast<InternalQueryable<
                TStoring, std::set, TStoring, TLessThan, TAllocator>>(
                std::make_shared<SetInternalQueryable<TStoring, TLessThan, TAllocator>>(other)));
        return queryable;
    }

    template <typename TStoring, typename TAllocator = std::allocator<TStoring>>
    static Queryable<TStoring, std::vector, TStoring, TAllocator> FromInternalVector(
        const VectorInternalQueryable<TStoring, TAllocator> & other)
    {
        Queryable<TStoring, std::vector, TStoring, TAllocator> queryable(
            FutureStd::reinterpret_pointer_cast<InternalQueryable<
                TStoring, std::vector, TStoring, TAllocator>>(
                std::make_shared<VectorInternalQueryable<TStoring, TAllocator>>(other)));
        return queryable;
    }

    template <typename TStoring, typename TAllocator = std::allocator<TStoring>>
    static Queryable<TStoring, std::deque, TStoring, TAllocator> FromDeque(
        const std::deque<TStoring, TAllocator> & iterable)
    {
        return Queryable<TStoring, std::deque, TStoring, TAllocator>(
            InternalBuilders::FromDeque<TStoring, TAllocator>(iterable));
    }

    template <typename TStoring, typename TAllocator = std::allocator<TStoring>>
    static Queryable<TStoring, std::list, TStoring, TAllocator> FromList(
        const std::list<TStoring, TAllocator> & iterable)
    {
        return Queryable<TStoring, std::list, TStoring, TAllocator>(
            InternalBuilders::FromList<TStoring, TAllocator>(iterable));
    }

    template <typename TKey, typename TValue, typename TLessThan = std::less<TKey>, typename
              TAllocator = std::allocator<std::pair<const TKey, TValue>>>
    static Queryable<TKey, std::map, std::pair<const TKey, TValue>, TValue, TLessThan, TAllocator>
    FromMap(const std::map<TKey, TValue, TLessThan, TAllocator> & iterable)
    {
        return Queryable<TKey, std::map, std::pair<const TKey, TValue>, TValue, TLessThan,
                         TAllocator>(
            InternalBuilders::FromMap<TKey, TValue, TLessThan, TAllocator>(iterable));
    }

    template <typename TStoring, typename TLessThan = std::less<TStoring>, typename TAllocator =
              std::allocator<TStoring>>
    static Queryable<TStoring, std::multiset, TStoring, TLessThan, TAllocator> FromMultiSet(
        const std::multiset<TStoring, TLessThan, TAllocator> & iterable)
    {
        return Queryable<TStoring, std::multiset, TStoring, TLessThan, TAllocator>(
            InternalBuilders::FromMultiSet<TStoring, TLessThan, TAllocator>(iterable));
    }

    template <typename TStoring, typename TLessThan = std::less<TStoring>, typename TAllocator =
              std::allocator<TStoring>>
    static Queryable<TStoring, std::set, TStoring, TLessThan, TAllocator> FromSet(
        const std::set<TStoring, TLessThan, TAllocator> & iterable)
    {
        return Queryable<TStoring, std::set, TStoring, TLessThan, TAllocator>(
            InternalBuilders::FromSet<TStoring, TLessThan, TAllocator>(iterable));
    }

    template <typename TStoring, typename TAllocator = std::allocator<TStoring>>
    static Queryable<TStoring, std::vector, TStoring, TAllocator> FromVector(
        const std::vector<TStoring, TAllocator> & iterable)
    {
        return Queryable<TStoring, std::vector, TStoring, TAllocator>(
            InternalBuilders::FromVector<TStoring, TAllocator>(iterable));
    }
}

#endif
