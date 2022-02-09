#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMETESTPARAMS_TIMETESTCATEGORY_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMETESTPARAMS_TIMETESTCATEGORY_H

#include <string>

enum class TimeTestCategory
{
  BuiltIn,
  Class,
  Other
};

static std::string GetCategoryName(TimeTestCategory category)
{
  switch (category)
  {
    case TimeTestCategory::BuiltIn: return "BuiltIn";
    case TimeTestCategory::Class: return "Class";
    case TimeTestCategory::Other:
    default:
      return "Other";
  }
}

#endif
