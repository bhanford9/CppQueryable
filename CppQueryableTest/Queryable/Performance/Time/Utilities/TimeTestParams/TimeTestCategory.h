#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMETESTPARAMS_TIMETESTCATEGORY_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMETESTPARAMS_TIMETESTCATEGORY_H

#include <string>

enum class TimeTestCategory
{
  BuiltInLowLoad,
  BuiltInHeavyLoad,
  ClassLowLoad,
  ClassHeavyLoad,
  Other
};

static std::string GetCategoryName(TimeTestCategory category)
{
  switch (category)
  {
    case TimeTestCategory::BuiltInLowLoad: return "Built-In Type with Low Load";
    case TimeTestCategory::BuiltInHeavyLoad: return "Built-In Type with Heavy Load";
    case TimeTestCategory::ClassLowLoad: return "Class Type with Low Load";
    case TimeTestCategory::ClassHeavyLoad: return "Class Type with Heavy Load";
    case TimeTestCategory::Other:
    default:
      return "Other";
  }
}

#endif
