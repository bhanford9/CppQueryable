#ifndef CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_VECTORINTERNALQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_VECTORINTERNALQUERYABLE_H

#include <memory>
#include <vector>
#include "QueryableForwardDeclare.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/SkipWhileQueryableData/SkipWhileQueryableVectorData.hpp"
#include "../QueryableData/TakeWhileQueryableData/TakeWhileQueryableVectorData.hpp"
#include "../QueryableData/WhereQueryableData/WhereQueryableVectorData.hpp"
#include "../Utilities/IWhileCondition.hpp"

template <typename TObj, typename TAllocator>
class VectorInternalQueryable : public InternalQueryable<TObj, std::vector, TObj, TAllocator>
{
protected:
    VectorInternalQueryable()
    {
    }

public:
    virtual ~VectorInternalQueryable() override = default;

    VectorInternalQueryable(const VectorInternalQueryable & other)
        : InternalQueryable<TObj, std::vector, TObj, TAllocator>(other)
    {
    }

    VectorInternalQueryable(VectorInternalQueryable && other) noexcept
        : InternalQueryable<TObj, std::vector, TObj, TAllocator>(std::move(other))
    {
    }

    // explicit VectorInternalQueryable(TAllocator allocator = {}) :
    //   InternalQueryable<TObj, std::vector, TObj, TAllocator>(QueryableType::Vector)
    // {
    //   std::vector<TObj> localVector(allocator);
    //   this->items = std::make_shared<QueryableVectorData<TObj, TAllocator>>(localVector);
    // }

    // explicit VectorInternalQueryable(const std::vector<TObj, TAllocator> & vector)
    // {
    //   this->type = QueryableType::Vector;
    //   this->items = std::make_shared<QueryableVectorData<TObj, TAllocator>>(vector);
    // }

    explicit VectorInternalQueryable(
        const InternalQueryable<TObj, std::vector, TObj, TAllocator> & other)
        : InternalQueryable<TObj, std::vector, TObj, TAllocator>(other)
    {
        // std::cout << "vector internal queryable copy" << std::endl;
        this->type = QueryableType::Vector;
    }

    VectorInternalQueryable(
        std::shared_ptr<QueryableData<TObj, std::vector, TObj, TAllocator>> && queryableData,
        QueryableType type)
        : InternalQueryable<TObj, std::vector, TObj, TAllocator>(std::move(queryableData), type)
    {
    }

    // VectorInternalQueryable(const QueryableIterator<TObj> & first, const QueryableIterator<TObj> & last, TAllocator allocator = {})
    // {
    //   this->items = std::make_shared<QueryableVectorData<TObj, TAllocator>>(std::vector<TObj, TAllocator>(first, last, allocator));
    //   this->type = QueryableType::Vector;
    // }

    VectorInternalQueryable & operator=(const VectorInternalQueryable & other)
    {
        if (this == &other) return *this;
        InternalQueryable<TObj, std::vector, TObj, TAllocator>::operator =(other);
        return *this;
    }

    VectorInternalQueryable & operator=(VectorInternalQueryable && other) noexcept
    {
        if (this == &other) return *this;
        InternalQueryable<TObj, std::vector, TObj, TAllocator>::operator =(std::move(other));
        return *this;
    }

    virtual void Where(std::function<bool(const TObj &)> condition) override
    {
        this->items = std::make_shared<WhereQueryableVectorData<TObj, TAllocator>>(
            std::move(this->items),
            std::move(condition));
    }

    virtual void InternalSkipWhile(std::shared_ptr<IWhileCondition<TObj>> && condition) override
    {
        this->items = std::move(
            std::make_shared<SkipWhileQueryableVectorData<TObj, TAllocator>>(
                std::move(this->items),
                std::move(condition)));
    }

    virtual void InternalTakeWhile(std::shared_ptr<IWhileCondition<TObj>> && condition) override
    {
        this->items = std::move(
            std::make_shared<TakeWhileQueryableVectorData<TObj, TAllocator>>(
                std::move(this->items),
                std::move(condition)));
    }
};

#endif
