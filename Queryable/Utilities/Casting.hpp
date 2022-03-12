#ifndef CPPQUERYABLE_QUERYABLE_UTILITIES_CASTING_H
#define CPPQUERYABLE_QUERYABLE_UTILITIES_CASTING_H

#include <memory>

namespace FutureStd
{
  template <typename To, typename From>
  inline std::shared_ptr<To> reinterpret_pointer_cast(std::shared_ptr<From> const & ptr) noexcept
  {
    return std::shared_ptr<To>(ptr, reinterpret_cast<To *>(ptr.get()));
  }
}
#endif
