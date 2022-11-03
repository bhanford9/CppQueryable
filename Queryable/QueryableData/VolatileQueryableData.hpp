#ifndef CPPQUERYABLE_QUERYABLE_VOLATILEQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_VOLATILEQUERYABLEDATA_H

#include <algorithm>
#include <memory>

#include "QueryableData.hpp"

template <typename TStoring, template<typename, typename ...> class TIterable, typename TIterating,
          typename ...TArgs>
class VolatileQueryableData : public QueryableData<TStoring, TIterable, TIterating, TArgs...>
{
public:
    VolatileQueryableData()
        : QueryableData<TStoring, TIterable, TIterating, TArgs...>()
    {
    }

    VolatileQueryableData(const VolatileQueryableData & other)
        : QueryableData<TStoring, TIterable, TIterating, TArgs...>(other)
    {
    }

    VolatileQueryableData(VolatileQueryableData && other) noexcept
        : QueryableData<TStoring, TIterable, TIterating, TArgs...>(std::move(other))
    {
    }

    explicit VolatileQueryableData(const TIterable<TStoring, TArgs...> & iterable)
        : QueryableData<TStoring, TIterable, TIterating, TArgs...>(iterable)
    {
    }

    explicit VolatileQueryableData(TIterable<TStoring, TArgs...> && iterable) noexcept
        : QueryableData<TStoring, TIterable, TIterating, TArgs...>(iterable)
    {
    }

    VolatileQueryableData & operator=(const VolatileQueryableData & other)
    {
        if (this == &other) return *this;
        QueryableData<TStoring, TIterable, TIterating, TArgs...>::operator =(other);
        return *this;
    }

    VolatileQueryableData & operator=(VolatileQueryableData && other) noexcept
    {
        if (this == &other) return *this;
        QueryableData<TStoring, TIterable, TIterating, TArgs...>::operator =(std::move(other));
        return *this;
    }

    virtual ~VolatileQueryableData() override
    {
    }

    virtual std::shared_ptr<IQueryableData<TIterating>> Clone() override
    {
        return std::make_shared<VolatileQueryableData<TStoring, TIterable, TIterating, TArgs...>>(*this);
    }

    virtual IQueryableData<TIterating> & Add(int addend, const IteratorType type) override
    {
        // std::cout << "ConstRandom Access + Operator, adding: " << addend << std::endl;
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

        // std::cout << "ConstRandom Access add result: " << *this->beginIterator << std::endl;

        return *this;
    }

    virtual IQueryableData<TIterating> & Subtract(int subtrahend, const IteratorType type) override
    {
        // std::cout << "ConstRandom Access - Operator, adding: " << subtrahend << std::endl;
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

    virtual TIterating & Get(const IteratorType type) override
    {
        // std::cout << "Get" << std::endl;
        switch (type)
        {
        case IteratorType::BeginForward: { return static_cast<TIterating &>(*this->beginIterator); }
        case IteratorType::EndForward: { return static_cast<TIterating &>(*this->endIterator); }
        case IteratorType::BeginReverse: { return static_cast<TIterating &>(*this->rbeginIterator); }
        case IteratorType::EndReverse: default: { return static_cast<TIterating &>(*this->rendIterator); }
        }
    }

    virtual const TIterating & ConstGet(const IteratorType type) override
    {
        switch (type)
        {
        case IteratorType::BeginForward: { return *this->beginIterator; }
        case IteratorType::EndForward: { return *this->endIterator; }
        case IteratorType::BeginReverse: { return *this->rbeginIterator; }
        case IteratorType::EndReverse: default: { return *this->rendIterator; }
        }
    }

    virtual void Add(TIterating item) override
    {
        this->items->push_back(item);
        ++this->size;
    }
};

#endif
