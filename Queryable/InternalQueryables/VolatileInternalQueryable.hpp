#ifndef CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_VOLATILEINTERNALQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_VOLATILEINTERNALQUERYABLE_H

#include <memory>
#include <vector>
#include "QueryableForwardDeclare.hpp"
#include "../QueryableType.hpp"
// #include "../QueryableData/SkipWhileQueryableData/SkipWhileQueryableVolatileData.hpp"
// #include "../QueryableData/TakeWhileQueryableData/TakeWhileQueryableVolatileData.hpp"
#include "../QueryableData/WhereQueryableData/WhereQueryableVolatileData.hpp"
#include "../Utilities/IWhileCondition.hpp"

// TODO --> Template the container type
template <typename TObj, typename TAllocator>
class VolatileInternalQueryable : public InternalQueryable<TObj, std::vector, TObj, TAllocator>
{
protected:
    VolatileInternalQueryable()
    {
    }

public:
    virtual ~VolatileInternalQueryable() override = default;

    VolatileInternalQueryable(const VolatileInternalQueryable & other)
        : InternalQueryable<TObj, std::vector, TObj, TAllocator>(other)
    {
    }

    VolatileInternalQueryable(VolatileInternalQueryable && other) noexcept
        : InternalQueryable<TObj, std::vector, TObj, TAllocator>(std::move(other))
    {
    }

    explicit VolatileInternalQueryable(
        const InternalQueryable<TObj, std::vector, TObj, TAllocator> & other)
        : InternalQueryable<TObj, std::vector, TObj, TAllocator>(other)
    {
        // std::cout << "vector internal queryable copy" << std::endl;
        this->type = QueryableType::Vector;
    }

    VolatileInternalQueryable(
        std::shared_ptr<QueryableData<TObj, std::vector, TObj, TAllocator>> && queryableData,
        QueryableType type)
        : InternalQueryable<TObj, std::vector, TObj, TAllocator>(std::move(queryableData), type)
    {
    }

    VolatileInternalQueryable & operator=(const VolatileInternalQueryable & other)
    {
        if (this == &other) return *this;
        InternalQueryable<TObj, std::vector, TObj, TAllocator>::operator =(other);
        return *this;
    }

    VolatileInternalQueryable & operator=(VolatileInternalQueryable && other) noexcept
    {
        if (this == &other) return *this;
        InternalQueryable<TObj, std::vector, TObj, TAllocator>::operator =(std::move(other));
        return *this;
    }

    virtual void Where(std::function<bool(const TObj &)> condition) override
    {
        this->items = std::make_shared<WhereQueryableVolatileData<TObj, TAllocator>>(
            std::move(this->items),
            std::move(condition));
    }

    virtual void InternalSkipWhile(std::shared_ptr<IWhileCondition<TObj>> && condition) override
    {
        // this->items = std::move(
        //     std::make_shared<SkipWhileQueryableVectorData<TObj, TAllocator>>(
        //         std::move(this->items),
        //         std::move(condition)));
    }

    virtual void InternalTakeWhile(std::shared_ptr<IWhileCondition<TObj>> && condition) override
    {
        // this->items = std::move(
        //     std::make_shared<TakeWhileQueryableVectorData<TObj, TAllocator>>(
        //         std::move(this->items),
        //         std::move(condition)));
    }
};

#endif
