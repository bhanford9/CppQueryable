#ifndef CPPQUERYABLE_QUERYABLE_UTILITIES_GROUPING_H
#define CPPQUERYABLE_QUERYABLE_UTILITIES_GROUPING_H

#include <iostream>
#include <vector>

#include "../InternalQueryables/VectorInternalQueryable.hpp"
#include "../Iterators/QueryableIterator.hpp"
#include "../QueryableData/VolatileQueryableData.hpp"

// map gets tripped up here because it cannot return a copy of std::pair when iterating
// to get around this, will need Grouping to be its own Internal Queryable which contains
// a vector Internal Queryable within it (similar to how Select works) so the internal
// thing can still behave as needed while the wrapper can adjust as needed...
//   but hen why does map.ToVector().ForEach work? or does it?
//   ... it does not :(
//   
//   My only potential idea right now would be to try making the QueryableData's 'value' field a pointer
template <typename TKey, typename TValue, typename TValueAllocator>
class Grouping final : public VectorInternalQueryable<TValue, TValueAllocator>
{
private:
    TKey key;
    std::function<bool(TKey, TKey)> keyLessThan;

public:
    Grouping()
        : key(), keyLessThan()
    {
    }

    virtual ~Grouping() override
    {
    }

    Grouping(
        const TKey & key,
        const TValue & value,
        std::function<bool(TKey, TKey)> lessThan = [](TKey a, TKey b) { return a < b; },
        TValueAllocator allocator = { })
        : VectorInternalQueryable<TValue, TValueAllocator>(
            std::make_shared<VolatileQueryableData<TValue, std::vector, TValueAllocator>>(
                std::vector<TValue, TValueAllocator>(1, value, allocator)),
            QueryableType::Vector)
    {
        this->key = key;
        this->keyLessThan = [&](TKey a, TKey b) { return lessThan(a, b); };
    }

    Grouping(
        const TKey & key,
        const std::vector<TValue, TValueAllocator> & values,
        std::function<bool(TKey, TKey)> lessThan = [](TKey a, TKey b) { return a < b; },
        TValueAllocator allocator = { })
        : VectorInternalQueryable<TValue, TValueAllocator>(
            std::make_shared<VolatileQueryableData<TValue, std::vector, TValueAllocator>>(values),
            QueryableType::Vector)
    {
        this->key = key;
        this->keyLessThan = [&](TKey a, TKey b) { return lessThan(a, b); };
    }

    Grouping(
        const TKey & key,
        const QueryableIterator<TValue> & first,
        const QueryableIterator<TValue> & last,
        std::function<bool(TKey, TKey)> lessThan = [](TKey a, TKey b) { return a < b; },
        TValueAllocator allocator = { })
        : VectorInternalQueryable<TValue, TValueAllocator>(first, last, allocator)
    {
        this->key = key;
        this->keyLessThan = [&](TKey a, TKey b) { return lessThan(a, b); };
    }

    Grouping(const Grouping<TKey, TValue, TValueAllocator> & other)
        : VectorInternalQueryable<TValue, TValueAllocator>(other)
    {
        this->key = other.key;
        this->keyLessThan = other.keyLessThan;
    }

    Grouping(Grouping<TKey, TValue, TValueAllocator> && other) noexcept
        : VectorInternalQueryable<TValue, TValueAllocator>(std::move(other))
    {
        this->key = std::move(other.key);
        this->keyLessThan = std::move(other.keyLessThan);
    }

    TKey GetKey() const
    {
        return this->key;
    }

    bool operator==(const Grouping<TKey, TValue, TValueAllocator> & other) const
    {
        return this->key == other.key;
    }

    bool operator!=(const Grouping<TKey, TValue, TValueAllocator> & other) const
    {
        return this->key != other.key;
    }

    bool operator<(const Grouping<TKey, TValue, TValueAllocator> & other) const
    {
        return this->keyLessThan(this->key, other.key);
    }

    Grouping<TKey, TValue, TValueAllocator> & operator=(
        const Grouping<TKey, TValue, TValueAllocator> & other)
    {
        this->key = other.key;
        this->keyLessThan = other.keyLessThan;
        this->items = other.items;
        return *this;
    }

    Grouping<TKey, TValue, TValueAllocator> & operator=(
        Grouping<TKey, TValue, TValueAllocator> && other) noexcept
    {
        this->key = other.key;
        this->keyLessThan = other.keyLessThan;
        this->items = std::move(other.items);
        return *this;
    }

    size_t Count()
    {
        return this->items->Count();
    }

    std::ostream & operator<<(std::ostream & str);

    friend std::ostream & operator<<(std::ostream & str, const Grouping & v)
    {
        size_t num = 0;
        v.ForEach(
            [&](TValue value)
            {
                str << value << "\r\n";
                num++;
            });
        str << "Number Of Elements in Group: " << num;
        return str;
    }
};

#endif
