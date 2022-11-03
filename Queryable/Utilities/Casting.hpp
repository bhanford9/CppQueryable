#ifndef CPPQUERYABLE_QUERYABLE_UTILITIES_CASTING_H
#define CPPQUERYABLE_QUERYABLE_UTILITIES_CASTING_H

#include <memory>

namespace FutureStd
{
  template <typename To, typename From>
  std::shared_ptr<To> reinterpret_pointer_cast(std::shared_ptr<From> const & ptr) noexcept
  {
    return std::shared_ptr<To>(ptr, reinterpret_cast<To *>(ptr.get()));
  }

  // template<typename To, typename From> 
  // std::shared_ptr<To> static_pointer_cast( const std::shared_ptr<From>& r ) noexcept
  // {
  //     auto p = static_cast<typename std::shared_ptr<To>::element_type*>(r.get());
  //     return std::shared_ptr<To>{r, p};
  // }
}
#endif
