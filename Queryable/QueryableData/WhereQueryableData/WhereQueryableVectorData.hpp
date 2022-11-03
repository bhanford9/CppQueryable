#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEVECTORDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEVECTORDATA_H

#include <vector>

#include "WhereQueryableData.hpp"
#include "../QueryableVectorData.hpp"

template <typename TObj, typename TAllocator = std::allocator<TObj>>
class WhereQueryableVectorData final : public WhereQueryableData<TObj, std::vector, TObj, TAllocator>
{
public:
    WhereQueryableVectorData(const WhereQueryableVectorData & other)
        : WhereQueryableData<TObj, std::vector, TObj, TAllocator>(other)
    {
    }

    WhereQueryableVectorData(WhereQueryableVectorData && other) noexcept
        : WhereQueryableData<TObj, std::vector, TObj, TAllocator>(std::move(other))
    {
    }

    WhereQueryableVectorData(
        std::shared_ptr<IQueryableData<TObj>> && data,
        std::function<bool(TObj)> && condition)
        : WhereQueryableData<TObj, std::vector, TObj, TAllocator>(
            std::move(data),
            std::move(condition))
    {
        // std::cout << "WhereQueryable Vector Data Constructor 0" << std::endl;
    }

    WhereQueryableVectorData(
        std::shared_ptr<QueryableData<TObj, std::vector, TObj, TAllocator>> && data,
        std::function<bool(TObj)> && condition)
        : WhereQueryableData<TObj, std::vector, TObj, TAllocator>(
            std::move(data),
            std::move(condition))
    {
        // std::cout << "WhereQueryable Vector Data Constructor 1" << std::endl;
    }

    WhereQueryableVectorData & operator=(const WhereQueryableVectorData & other)
    {
        if (this == &other) return *this;
        WhereQueryableData<TObj, std::vector, TObj, TAllocator>::operator =(other);
        return *this;
    }

    WhereQueryableVectorData & operator=(WhereQueryableVectorData && other) noexcept
    {
        if (this == &other) return *this;
        WhereQueryableData<TObj, std::vector, TObj, TAllocator>::operator =(std::move(other));
        return *this;
    }

    WhereQueryableVectorData(
        const std::shared_ptr<QueryableData<TObj, std::vector, TObj, TAllocator>> & data,
        std::function<bool(TObj)> && condition)
        : WhereQueryableData<TObj, std::vector, TObj, TAllocator>(data, std::move(condition))
    {
        // std::cout << "WhereQueryable Vector Data Constructor 3" << std::endl;
    }

    virtual ~WhereQueryableVectorData() override = default;

    virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
    {
        return std::make_shared<WhereQueryableVectorData<TObj, TAllocator>>(*this);
    }

    virtual IQueryableData<TObj> & Add(int addend, const IteratorType type) override
    {
        // std::cout << "[VectorWhere+]" << std::endl;
        switch (type)
        {
        case IteratorType::BeginForward: this->beginIterator += addend;
            break;
        case IteratorType::EndForward: this->endIterator += addend;
            break;
        case IteratorType::BeginReverse: this->rbeginIterator += addend;
            break;
        case IteratorType::EndReverse: this->rendIterator += addend;
            break;
        }

        return *this;
    }

    virtual IQueryableData<TObj> & Subtract(int subtrahend, const IteratorType type) override
    {
        switch (type)
        {
        case IteratorType::BeginForward: this->beginIterator -= subtrahend;
            break;
        case IteratorType::EndForward: this->endIterator -= subtrahend;
            break;
        case IteratorType::BeginReverse: this->rbeginIterator -= subtrahend;
            break;
        case IteratorType::EndReverse: this->rendIterator -= subtrahend;
            break;
        }

        return *this;
    }

    virtual void InternalAdd(TObj item) override
    {
        this->items->push_back(item);
    }

    virtual std::shared_ptr<IQueryableData<TObj>> GetRealizedQueryableData() override
    {
        // If all QueryableData's have a constructor that takes begin, end, Args... then this method can be a one liner
        std::vector<TObj, TAllocator> data(this->items->get_allocator());

        for (const TObj & value : *this)
        {
            data.push_back(value);
        }

        return std::make_shared<QueryableVectorData<TObj, TAllocator>>(std::move(data));
    }
};

#endif
