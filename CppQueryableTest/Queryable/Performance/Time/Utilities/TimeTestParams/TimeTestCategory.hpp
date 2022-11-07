#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMETESTPARAMS_TIMETESTCATEGORY_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMETESTPARAMS_TIMETESTCATEGORY_H

#include <sstream>
#include <string>

namespace TimeTestCategory
{

enum class Type
{
  BuiltIn,
  Class,
  Other
};

static std::string GetCategoryName(TimeTestCategory::Type category)
{
  switch (category)
  {
    case TimeTestCategory::Type::BuiltIn: return "BuiltIn";
    case TimeTestCategory::Type::Class: return "Class";
    case TimeTestCategory::Type::Other:
    default:
      return "Other";
  }
}
}

#endif
