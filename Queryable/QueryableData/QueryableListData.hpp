#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLELISTDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLELISTDATA_H

#include <list>

#include "QueryableData.hpp"

template <typename T, typename TAllocator = std::allocator<T>>
class QueryableListData final : public QueryableData<T, std::list, T, TAllocator>
{
public:
    QueryableListData(const QueryableListData & other)
        : QueryableData<T, std::list, T, TAllocator>(other)
    {
    }

    QueryableListData(QueryableListData && other) noexcept
        : QueryableData<T, std::list, T, TAllocator>(std::move(other))
    {
    }

    QueryableListData()
        : QueryableData<T, std::list, T, TAllocator>()
    {
    }
    
    explicit QueryableListData(const std::list<T, TAllocator> & items)
        : QueryableData<T, std::list, T, TAllocator>(items)
    {
    }

    explicit QueryableListData(std::list<T, TAllocator> && items)
        : QueryableData<T, std::list, T, TAllocator>(std::move(items))
    {
    }

    QueryableListData & operator=(const QueryableListData & other)
    {
        if (this == &other) return *this;
        QueryableData<T, std::list, T, TAllocator>::operator =(other);
        return *this;
    }

    QueryableListData & operator=(QueryableListData && other) noexcept
    {
        if (this == &other) return *this;
        QueryableData<T, std::list, T, TAllocator>::operator =(std::move(other));
        return *this;
    }

    virtual ~QueryableListData() override
    {
    }

    virtual std::shared_ptr<IQueryableData<T>> Clone() override
    {
        return std::make_shared<QueryableListData<T, TAllocator>>(*this);
    }

    virtual void Add(T item) override
    {
        this->items->push_back(item);
        ++this->size;
    }

    virtual T & Get(const IteratorType type) override
    {
        // std::cout << "Get" << std::endl;
        switch (type)
        {
        // case IteratorType::BeginForward: { this->value = &(*this->beginIterator); return *this->value; }
        // case IteratorType::EndForward: { this->value = &(*this->endIterator); return *this->value; }
        // case IteratorType::BeginReverse: { this->value = &(*this->rbeginIterator); return *this->value; }
        // case IteratorType::EndReverse: default: { this->value = &(*this->rendIterator); return *this->value; }
        case IteratorType::BeginForward:
            {
                this->value = *this->beginIterator;
                return this->value;
            }
        case IteratorType::EndForward:
            {
                this->value = *this->endIterator;
                return this->value;
            }
        case IteratorType::BeginReverse:
            {
                this->value = *this->rbeginIterator;
                return this->value;
            }
        case IteratorType::EndReverse: default:
            {
                this->value = *this->rendIterator;
                return this->value;
            }
        }
    }

    virtual const T & ConstGet(const IteratorType type) override
    {
        switch (type)
        {
        // case IteratorType::BeginForward: { this->value = &(*this->beginIterator); return *this->value; }
        // case IteratorType::EndForward: { this->value = &(*this->endIterator); return *this->value; }
        // case IteratorType::BeginReverse: { this->value = &(*this->rbeginIterator); return *this->value; }
        // case IteratorType::EndReverse: default: { this->value = &(*this->rendIterator); return *this->value; }
        case IteratorType::BeginForward:
            {
                this->value = *this->beginIterator;
                return this->value;
            }
        case IteratorType::EndForward:
            {
                this->value = *this->endIterator;
                return this->value;
            }
        case IteratorType::BeginReverse:
            {
                this->value = *this->rbeginIterator;
                return this->value;
            }
        case IteratorType::EndReverse: default:
            {
                this->value = *this->rendIterator;
                return this->value;
            }
        }
    }
};

#endif
